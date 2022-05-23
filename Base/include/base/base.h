#pragma once

#include <Windows.h>

#include <modutils.h>

class DedicatedServer;
class ServerInstance;
class Minecraft;
class MinecraftCommands;
class CommandRegistry;
class AppPlatform;
class ServerNetworkHandler;
class NetworkHandler;
class Level;
namespace RakNet {
class RakPeer;
}
namespace mce {
class UUID;
}

BASEAPI HMODULE GetLoadedMod(char const *name);

BASEAPI mce::UUID const &SessionUUID();

// Can only be used to get instances of the above types
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