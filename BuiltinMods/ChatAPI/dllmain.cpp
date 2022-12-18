#include <string>
#include <memory>

#include <boost/scope_exit.hpp>

#include <sqlite3.h>
#include <SQLiteCpp/SQLiteCpp.h>

#include <Packet/TextPacket.h>
#include <Actor/Player.h>
#include <Level/Level.h>

#include <hook.h>
#include <dllentry.h>

#include <base/playerdb.h>
#include <base/log.h>
#include <mods/ChatAPI.h>

void dllenter() {}
void dllexit() {}




static std::unique_ptr<SQLite::Database> database;

static void (Mod::Chat::*emitter)(
	sigt<"chat"_sig>, Mod::PlayerEntry const &, std::string &, std::string &, Mod::CallbackToken<std::string> &);




static struct Settings {
	std::string database   = "chat.db";
	std::string namePrefix = "<";
	std::string nameSuffix = ">";

	template <typename IO> static inline bool io(IO f, Settings &settings, YAML::Node &node) {
		return f(settings.database, node["database"]) &&
				f(settings.namePrefix, node["namePrefix"]) &&
				f(settings.nameSuffix, node["nameSuffix"]);
	}
} settings;

DEFAULT_SETTINGS(settings);




void PreInit() {
	database = std::make_unique<SQLite::Database>(settings.database, SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);
	database->exec("PRAGMA journal_mode = WAL");
	database->exec("PRAGMA synchronous = NORMAL");
	database->exec(
		"CREATE TABLE IF NOT EXISTS chat ("
		"uuid BLOB NOT NULL, "
		"name TEXT, "
		"content TEXT, "
		"time INTEGER DEFAULT(STRFTIME('%Y-%m-%d %H:%M:%f', 'now')))"
	);
}




namespace Mod {

Chat::Chat() { emitter = &Chat::Emit; }

Chat &Chat::GetInstance() {
	static Chat instance;
	return instance;
}

void Chat::SendBroadcast(const std::string &name, const std::string &content) {
	auto packet = TextPacket::createTextPacket<TextPacketType::Chat>(name, content);
	LocateService<Level>()->forEachPlayer([&](Player const &p) -> bool {
		p.sendNetworkPacket(packet);
		return true;
	});
}

void Chat::SendAnnounce(const std::string &content) {
	auto packet = TextPacket::createTextPacket<TextPacketType::Announcement>(content);
	LocateService<Level>()->forEachPlayer([&](Player const &p) -> bool {
		p.sendNetworkPacket(packet);
		return true;
	});
}

void Chat::SendAnnounce(const std::string &content, std::initializer_list<std::string> args) {
	auto packet = TextPacket::createTranslatedMessageWithParams(content, args);
	LocateService<Level>()->forEachPlayer([&](Player const &p) -> bool {
		p.sendNetworkPacket(packet);
		return true;
	});
}

void Chat::Send(const Mod::PlayerEntry &entry, const std::string &content) {
	auto packet = TextPacket::createTextPacket<TextPacketType::Announcement>(content);
	entry.player->sendNetworkPacket(packet);
}

void Chat::Send(const Mod::PlayerEntry &entry, const std::string &content, std::initializer_list<std::string> args) {
	auto packet = TextPacket::createTranslatedMessageWithParams(content, args);
	entry.player->sendNetworkPacket(packet);
}

void Chat::logChat(Mod::PlayerEntry const &sender, std::string const &content, std::string const* recipient) {
	if (!database) return;

	DEF_LOGGER("CHAT");

	if (recipient) {
		LOGI("[%s -> %s] %s") % sender.name % *recipient % content;
	}
	else {
		LOGI("[%s] %s") % sender.name % content;
	}

	static SQLite::Statement stmt{*database, "INSERT INTO chat (uuid, name, content) VALUES (?, ?, ?)"};
	BOOST_SCOPE_EXIT_ALL() {
		stmt.reset();
		stmt.clearBindings();
	};
	stmt.bindNoCopy(1, sender.uuid, sizeof(sender.uuid));
	stmt.bindNoCopy(2, sender.name);
	stmt.bindNoCopy(3, content);
	stmt.exec();
}

} // namespace Mod

TClasslessInstanceHook(void,
	"?_displayGameMessage@ServerNetworkHandler@@AEAAXAEBVPlayer@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z",
	Player const& player, std::string& content) {

	auto it = Mod::PlayerDatabase::GetInstance().Find((Player*)&player);
	if (!it) return;

	try {
		Mod::CallbackToken<std::string> token;
		(Mod::Chat::GetInstance().*emitter)(SIG("chat"), *it, it->name, content, token);

		// if chat is cancelled lets just not log it in the database
		// this is purely an impl preference so maybe change this later?
		if (token) return;
		Mod::Chat::logChat(*it, content);
	}
	catch (...) {}

	auto chatTxtPkt = TextPacket::createTextPacket<TextPacketType::SystemMessage>(
		it->name, settings.namePrefix + it->name + settings.nameSuffix + " " + content);

	LocateService<Level>()->forEachPlayer([&chatTxtPkt](Player const &p) -> bool {
		p.sendNetworkPacket(chatTxtPkt);
		return true;
	});

}