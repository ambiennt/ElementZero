#pragma once

#include <Windows.h>

#ifdef Base_EXPORTS
#  define BASEAPI __declspec(dllexport)
#else
#  define BASEAPI __declspec(dllimport)
#endif

class DedicatedServer;
class ServerInstance;
class Minecraft;
class MinecraftCommands;
class CommandRegistry;
class AppPlatform;
class ServerNetworkHandler;
class NetworkHandler;
class Level;
class LoopbackPacketSender;
class MinecraftServerScriptEngine;
namespace RakNet {
class RakPeer;
}
namespace mce {
class UUID;
}

BASEAPI HMODULE getLoadedMod(char const *name);

BASEAPI mce::UUID const &getSessionUUID();

// can only be used to get instances of the above types
template <typename T> T *LocateService();

template <> BASEAPI DedicatedServer *LocateService<DedicatedServer>();
template <> BASEAPI ServerInstance *LocateService<ServerInstance>();
template <> BASEAPI Minecraft *LocateService<Minecraft>();
template <> BASEAPI MinecraftCommands *LocateService<MinecraftCommands>();
template <> BASEAPI CommandRegistry *LocateService<CommandRegistry>();
template <> BASEAPI ServerNetworkHandler *LocateService<ServerNetworkHandler>();
template <> BASEAPI NetworkHandler *LocateService<NetworkHandler>();
template <> BASEAPI Level *LocateService<Level>();
template <> BASEAPI AppPlatform *LocateService<AppPlatform>();
template <> BASEAPI RakNet::RakPeer *LocateService<RakNet::RakPeer>();
template <> BASEAPI LoopbackPacketSender *LocateService<LoopbackPacketSender>();
template <> BASEAPI MinecraftServerScriptEngine *LocateService<MinecraftServerScriptEngine>();