#include <dllentry.h>
#include <Net/NetworkHandler.h>
#include <Net/NetworkIdentifier.h>
#include <Actor/Player.h>
#include <base/base.h>
#include <base/playerdb.h>
#include <base/log.h>
#include <mods/CommandSupport.h>
#include <mods/ScriptSupport/scriptapi.h>

DEF_LOGGER("NetworkStatus");

void dllenter() {}
void dllexit() {}

struct NetworkStatus : Command {

	void execute(CommandOrigin const& origin, CommandOutput &output) override {

		output.type = CommandOutputType::Normal;

		if (origin.getOriginType() != CommandOriginType::Player) {
			return output.error("This command can only be executed by players");
		}

		const auto& executor = *reinterpret_cast<Player*>(origin.getEntity());
		const auto& netId = executor.mNetworkIdentifier;
		const auto peer = LocateService<NetworkHandler>()->getPeerForUser(netId);
		
		if (peer) {	
			auto status = peer->getNetworkStatus();
			if (std::isnan(status.mCurrentPacketLoss)) { status.mCurrentPacketLoss = 0.f; }
			if (std::isnan(status.mAveragePacketLoss)) { status.mAveragePacketLoss = 0.f; }

			return output.success("commands.netstat.result",
				{status.mCurrentPing, status.mAveragePing, status.mCurrentPacketLoss, status.mAveragePacketLoss});
		}

		output.error("Failed to retrieve network statistics!");
	}

	static void setup(CommandRegistry *registry) {
		std::string cmdName("netstat");

		registry->registerCommand(cmdName, "commands.netstat.description",
			CommandPermissionLevel::Any, CommandFlagUsage, CommandFlagNone);
		registry->registerAlias(cmdName, "ping");
		registry->registerOverload<NetworkStatus>(cmdName);
	}
};

void PreInit() {
	Mod::CommandSupport::GetInstance().AddListener(SIG("loaded"), &NetworkStatus::setup);
}

using namespace Mod::Scripting;
static ModuleRegister reg("ez:network-stats", [](JsObjectWrapper native) -> std::string {
	native["getNetworkStats"] = +[](Mod::PlayerEntry const &player) {
		auto peer   = LocateService<NetworkHandler>()->getPeerForUser(player.netid);
		auto status = peer->getNetworkStatus();
		JsObjectWrapper ret;
		ret["ping"]          = status.mCurrentPing;
		ret["avgping"]       = status.mAveragePing;
		ret["packetloss"]    = status.mCurrentPacketLoss;
		ret["avgpacketloss"] = status.mAveragePacketLoss;
		return *ret;
	};
	return "export const getNetworkStats = import.meta.native.getNetworkStats;";
});