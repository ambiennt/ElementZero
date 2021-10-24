#include <dllentry.h>
#include <Net/NetworkHandler.h>
#include <Net/NetworkIdentifier.h>
#include <Actor/Player.h>
#include <base/base.h>
#include <base/playerdb.h>
#include <base/log.h>
#include <mods/CommandSupport.h>
#include <mods/ScriptSupport/scriptapi.h>
#include <Packet/TextPacket.h>

DEF_LOGGER("NetworkStatus");

void dllenter() {}
void dllexit() {}

struct NetworkStatus : Command {
  void execute(const CommandOrigin &orig, CommandOutput &outp) override {
    if (orig.getOriginType() != CommandOriginType::Player) {
      return outp.error("commands.generic.error.invalidPlayer", {"/net-stat"});
    }
    auto ent    = (Player *) orig.getEntity();
    auto &netid = ent->getNetworkIdentifier();
    auto peer   = LocateService<NetworkHandler>()->getPeerForUser(netid);
    auto status = peer->getNetworkStatus();

    auto netStatResult = TextPacket::createTextPacket<TextPacketType::SystemMessage>(
      "ping: " + std::to_string(status.ping) + " average: " + std::to_string(status.avgping) + " packet loss: " + std::to_string(status.packetloss) + " average: " + std::to_string(status.avgpacketloss));
    ent->sendNetworkPacket(netStatResult);
    //outp.success("commands.net-stat.result", {status.ping, status.avgping, status.packetloss, status.avgpacketloss});
  }

  static void setup(CommandRegistry *reg) {
    reg->registerCommand(
        "net-stat", "commands.net-stat.description", CommandPermissionLevel::Any, CommandFlagCheat, CommandFlagNone);
    reg->registerOverload<NetworkStatus>("net-stat");
  }
};

void PreInit() { Mod::CommandSupport::GetInstance().AddListener(SIG("loaded"), &NetworkStatus::setup); }

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