#pragma once

#include <cstdint>
#include <string>
#include <boost/scope_exit.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

#include <base/playerdb.h>
#include <Net/ServerNetworkHandler.h>

#include <mods/CommandSupport.h>
#include <mods/Blacklist.h>

#define PLAYER_DB Mod::PlayerDatabase::GetInstance()
#define BLACKLIST Mod::Blacklist::GetInstance()








class BanCommand : public Command {
  CommandSelector<Player> selector;
  std::string reason;

public:
  	BanCommand() {
		this->selector.setIncludeDeadPlayers(true);
	}

  	virtual void execute(CommandOrigin const &origin, CommandOutput &output);
  	static void setup(CommandRegistry *registry);
};

class BanNameCommand : public Command {
  std::string target;
  std::string reason;

public:
  	virtual void execute(CommandOrigin const &origin, CommandOutput &output);
  	static void setup(CommandRegistry *registry);
};

class UnbanCommand : public Command {
  std::string target;

public:
  	bool removeXUID(uint64_t xuid, CommandOutput &output);
  	bool removeUUID(mce::UUID const &uuid, CommandOutput &output);
  	bool removeNAME(std::string const &name, CommandOutput &output);
  	void removeEntry(Mod::OfflinePlayerEntry const &entry, CommandOutput &output);

  	virtual void execute(CommandOrigin const &origin, CommandOutput &output);
  	static void setup(CommandRegistry *registry);
};

class ForceKickCommand : public Command {
  	CommandSelector<Player> selector;
	bool useDefaultDisconnectMsg;
	std::string reason;
	bool skipPlayerLeftChatMsg;

public:
  	ForceKickCommand() : useDefaultDisconnectMsg(true), skipPlayerLeftChatMsg(false) {
		this->selector.setIncludeDeadPlayers(true);
	}

  	virtual void execute(CommandOrigin const &origin, CommandOutput &output);
  	static void setup(CommandRegistry *registry);
};