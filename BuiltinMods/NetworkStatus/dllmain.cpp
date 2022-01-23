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

		if (origin.getOriginType() != CommandOriginType::Player) {
			return output.error("commands.generic.error.invalidPlayer", {"/net-stat"});
		}

		auto player = (Player*)(origin.getEntity());
		auto &netid = player->getNetworkIdentifier();
		auto peer   = LocateService<NetworkHandler>()->getPeerForUser(netid);
		auto status = peer->getNetworkStatus();

		output.type = CommandOutputType::Normal;
		output.success("commands.net-stat.result", {status.ping, status.avgping, status.packetloss, status.avgpacketloss});
	}

	static void setup(CommandRegistry *reg) {
		reg->registerCommand(
				"net-stat", "commands.net-stat.description", CommandPermissionLevel::Any, CommandFlagUsage, CommandFlagCheat);
		reg->registerOverload<NetworkStatus>("net-stat");
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
		ret["ping"]          = status.ping;
		ret["avgping"]       = status.avgping;
		ret["packetloss"]    = status.packetloss;
		ret["avgpacketloss"] = status.avgpacketloss;
		return *ret;
	};
	return "export const getNetworkStats = import.meta.native.getNetworkStats;";
});