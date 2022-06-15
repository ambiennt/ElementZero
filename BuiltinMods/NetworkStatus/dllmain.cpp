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
			return output.error("commands.generic.error.invalidPlayer", {"/net-stat"});
		}

		auto& executor = *(Player*)(origin.getEntity());
		auto& netId = executor.getNetworkIdentifier();
		auto peer = LocateService<NetworkHandler>()->getPeerForUser(netId);
		
		if (peer) {
			auto status = peer->getNetworkStatus();
			return output.success("commands.net-stat.result",
				{status.mCurrentPing, status.mAveragePing, status.mCurrentPacketLoss, status.mAveragePacketLoss});
		}

		output.error("Failed to retrieve network statistics!");
	}

	static void setup(CommandRegistry *registry) {
		registry->registerCommand("net-stat", "commands.net-stat.description",
			CommandPermissionLevel::Any, CommandFlagUsage, CommandFlagCheat);
		registry->registerOverload<NetworkStatus>("net-stat");
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