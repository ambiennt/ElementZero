#include "pch.h"

#include "global.h"

class TransferCommand : public Command {
public:
	CommandSelector<Player> selector;
	std::string hostname = "127.0.0.1";
	int32_t port         = 19132;

	TransferCommand() {
		selector.setIncludeDeadPlayers(true);
	}

	void execute(CommandOrigin const &origin, CommandOutput &output) {

		if ((this->port <= 0) || (this->port > 65535)) {
			return output.error("commands.transferserver.invalid.port");
		}

		auto results = selector.results(origin);
		for (auto player : results) {
			TransferPacket pkt{hostname, port};
			player->sendNetworkPacket(pkt);
		}

		output.success("commands.transferserver.successful");
	}
};

void registerTransferServer(CommandRegistry *registry) {
	using namespace commands;

	registry->registerCommand(
		"transferserver", "commands.transferserver.description", CommandPermissionLevel::GameMasters, CommandFlagCheat, CommandFlagNone);
		
	registry->registerOverload<TransferCommand>("transferserver",
		mandatory(&TransferCommand::selector, "target"), mandatory(&TransferCommand::hostname, "hostname"),
		optional(&TransferCommand::port, "port"));
}
