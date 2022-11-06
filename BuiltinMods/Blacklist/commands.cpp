#include "commands.h"
#include "settings.h"
#include "global.h"

void BanCommand::execute(CommandOrigin const &origin, CommandOutput &output) {
	auto op      = origin.getName();
	auto results = selector.results(origin);
	switch (results.count()) {
	case 0: output.error("commands.generic.selector.empty"); break;
	case 1: {
		auto it = *results.begin();
		auto opt = PLAYER_DB.Find(it);
		if (opt) {
			LocateService<ServerNetworkHandler>()->forceDisconnectClient(*opt->player, false, reason);
			if (opt->xuid == 0) {
				BLACKLIST.Add(Mod::Blacklist::UUID{opt->uuid, opt->name}, reason, op);
				auto uuid = opt->uuid.asString();
				output.success("commands.ban.success.uuid", {opt->name, uuid});
			} else {
				BLACKLIST.Add(Mod::Blacklist::XUID{opt->xuid, opt->name}, reason, op);
				output.success("commands.ban.success.xuid", {opt->name, opt->xuid});
			}
		} else {
			output.error("commands.ban.error.unexpected");
		}
	} break;
	default: output.error("commands.generic.selector.tooManyTargets"); break;
	}
}

void BanCommand::setup(CommandRegistry *registry) {
	using namespace commands;
	registry->registerOverload<BanCommand>(
		"ban", mandatory(&BanCommand::selector, "target"), optional(&BanCommand::reason, "reason"));
}


void BanNameCommand::execute(CommandOrigin const &origin, CommandOutput &output) {
	auto op = origin.getName();
	if (target.size() == 0) {
		output.error("commands.ban.error.no.empty");
		return;
	}

	auto opt = PLAYER_DB.FindOffline(target);
	if (opt) {
		auto online = PLAYER_DB.Find(opt->uuid);
		if (online) {
			LocateService<ServerNetworkHandler>()->forceDisconnectClient(*online->player, false, reason);
		}

		if (opt->xuid == 0) {
			BLACKLIST.Add(Mod::Blacklist::UUID{opt->uuid, opt->name}, reason, op);
			auto uuid = opt->uuid.asString();
			output.success("commands.ban.success.uuid", {opt->name, uuid});
		} else {
			BLACKLIST.Add(Mod::Blacklist::XUID{opt->xuid, opt->name}, reason, op);
			output.success("commands.ban.success.xuid", {opt->name, opt->xuid});
		}
	} else {
		BLACKLIST.Add(Mod::Blacklist::NAME{target}, reason, op);
		output.success("commands.ban.success.name", {target});
	}
}

void BanNameCommand::setup(CommandRegistry *registry) {
	using namespace commands;
	registry->registerOverload<BanNameCommand>(
		"ban", mandatory(&BanNameCommand::target, "name"), optional(&BanNameCommand::reason, "reason"));
}


 bool UnbanCommand::removeXUID(uint64_t xuid, CommandOutput &output) {
	if (BLACKLIST.Remove(Mod::Blacklist::XUID{xuid})) {
		output.success("commands.unban.success.xuid", {xuid});
		return true;
	}
	return false;
}

bool UnbanCommand::removeUUID(mce::UUID const &uuid, CommandOutput &output) {
	if (BLACKLIST.Remove(Mod::Blacklist::UUID{uuid})) {
		output.success("commands.unban.success.uuid", {uuid.asString()});
		return true;
	}
	return false;
}

bool UnbanCommand::removeNAME(std::string const &name, CommandOutput &output) {
	if (BLACKLIST.Remove(Mod::Blacklist::NAME{name})) {
		output.success("commands.unban.success.name", {name});
		return true;
	}
	return false;
}

void UnbanCommand::removeEntry(Mod::OfflinePlayerEntry const &entry, CommandOutput &output) {
	bool flag = false;
	flag |= this->removeXUID(entry.xuid, output);
	flag |= this->removeUUID(entry.uuid, output);
	flag |= this->removeNAME(entry.name, output);
	if (!flag) output.error("commands.unban.error.not.found", {entry.name});
}

void UnbanCommand::execute(CommandOrigin const &origin, CommandOutput &output) {
	if (target.size() == 0) {
		output.error("commands.unban.error.no.empty");
		return;
	}

	// pre check for uuid
	if (target.size() == 36) {
		auto uuid = mce::UUID::fromString(target);
		if (!uuid.empty()) {
			if (auto opt = PLAYER_DB.FindOffline(uuid); opt) {
				this->removeEntry(*opt, output);
			} else {
				if (!this->removeUUID(opt->uuid, output)) {
					output.error("commands.unban.error.not.found.uuid", {uuid.asString()});
				}
			}
			return;
		}
	}
	// XUID
	try {
		auto xuid = boost::lexical_cast<uint64_t>(target);
		if (auto opt = PLAYER_DB.FindOffline(xuid); opt) {
			this->removeEntry(*opt, output);
		} else {
			if (!this->removeXUID(xuid, output)) { output.error("commands.unban.error.not.found.xuid", {xuid}); }
		}
		return;
	} catch (boost::bad_lexical_cast const &bad) {}
	// NAME
	if (auto opt = PLAYER_DB.FindOffline(target); opt) {
		this->removeEntry(*opt, output);
	} else if (!this->removeNAME(target, output)) {
		output.error("commands.unban.error.not.found.name", {target});
	}
	return;
}

void UnbanCommand::setup(CommandRegistry *registry) {
	using namespace commands;
	registry->registerCommand(
		"unban", "commands.unban.description", CommandPermissionLevel::GameMasters, CommandFlagCheat, CommandFlagNone);
	registry->registerOverload<UnbanCommand>("unban", mandatory(&UnbanCommand::target, "target"));
}


void ForceKickCommand::execute(CommandOrigin const &origin, CommandOutput &output) {

	auto results = this->selector.results(origin);
	if (results.empty()) {
		output.error("No targets matched selector");
		return;
	}

	auto& snh = *LocateService<ServerNetworkHandler>();
	for (auto it : results) {
		snh.forceDisconnectClient(*it, this->skipPlayerLeftChatMsg, this->reason);
	}

	int32_t resultCount = results.count();
	output.success("Successfully force-kicked " + std::to_string(resultCount) + ((resultCount == 1) ? " player" : " players"));
}

void ForceKickCommand::setup(CommandRegistry *registry) {
	using namespace commands;

	registry->registerCommand("forcekick", "Force-kick a player.",
		CommandPermissionLevel::GameMasters, CommandFlagUsage, CommandFlagNone);

	registry->registerOverload<ForceKickCommand>("forcekick",
		mandatory(&ForceKickCommand::selector, "target"),
		optional(&ForceKickCommand::skipPlayerLeftChatMsg, "skipPlayerLeftChatMsg"),
		optional(&ForceKickCommand::reason, "reason")
	);
}









void registerBlacklistCommands(CommandRegistry *registry) {
	registry->registerCommand(
		"ban", "commands.ban.description", CommandPermissionLevel::GameMasters, CommandFlagCheat, CommandFlagNone);
	BanCommand::setup(registry);
	BanNameCommand::setup(registry);
	UnbanCommand::setup(registry);
	ForceKickCommand::setup(registry);
}