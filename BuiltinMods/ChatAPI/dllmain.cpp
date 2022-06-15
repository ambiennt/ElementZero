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

} // namespace Mod

static void logChat(Mod::PlayerEntry const &entry, std::string const &content) {
	if (!database) return;

	DEF_LOGGER("CHAT");
	LOGI("[%s] %s") % entry.name % content;

	static SQLite::Statement stmt{*database, "INSERT INTO chat (uuid, name, content) VALUES (?, ?, ?)"};
	BOOST_SCOPE_EXIT_ALL() {
		stmt.reset();
		stmt.clearBindings();
	};
	stmt.bindNoCopy(1, entry.uuid, sizeof entry.uuid);
	stmt.bindNoCopy(2, entry.name);
	stmt.bindNoCopy(3, content);
	stmt.exec();
}

TClasslessInstanceHook(void,
	"?_displayGameMessage@ServerNetworkHandler@@AEAAXAEBVPlayer@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z",
	Player *player, std::string &content) try {

	auto it = Mod::PlayerDatabase::GetInstance().Find(player);
	if (!it) return;

	std::string displayName(it->name);
	Mod::CallbackToken<std::string> token;
	(Mod::Chat::GetInstance().*emitter)(SIG("chat"), *it, displayName, content, token);

	logChat(*it, content);

	if (token) return;

	auto chatTxtPkt = TextPacket::createTextPacket<TextPacketType::SystemMessage>(
		displayName, settings.namePrefix + displayName + settings.nameSuffix + " " + content);

	LocateService<Level>()->forEachPlayer([&](Player const &p) -> bool {
		p.sendNetworkPacket(chatTxtPkt);
		return true;
	});

} catch (...) {}