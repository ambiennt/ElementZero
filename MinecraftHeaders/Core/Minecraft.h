#pragma once

#include "../dll.h"
#include "Core.h"

#include <memory>
#include <chrono>

class Level;
class ServerNetworkHandler;
class MinecraftCommands;
class GameCallbacks;
class ResourcePackManager;
class StructureManager;
class GameModuleServer;
class IMinecraftEventing;
class Whitelist;
class PermissionsFile;
class EntityRegistryOwned;
class Timer;
class IMinecraftApp;
class PacketSender;
class NetworkHandler;
class GameSession;
class ServerMetrics;
class PrivateKeyManager;

// this class is very intertwined with the client so some fields might be nullptr/invalid
class Minecraft {
public:

	GameCallbacks *mGameCallbacks; // 0x8
	IMinecraftEventing *mEventing; // 0x10
	std::unique_ptr<ResourcePackManager> mResourceLoader; // 0x18
	std::unique_ptr<StructureManager> mStructureManager; // 0x20
	std::shared_ptr<GameModuleServer> mGameModuleServer; // 0x28
	Whitelist *mWhitelist; // 0x38
	PermissionsFile *mPermissionsFile; // 0x40
	std::unique_ptr<PrivateKeyManager> mServerKeys; // 0x48
	std::string mSaveGamePath; // 0x50 - const
	Core::FilePathManager *mFilePathManager; // 0x70
	ServerMetrics *mServerMetrics; // 0x78
	bool mLevelIsCorrupted; // 0x80
	long double mFrameDuration; // 0x88
	long double mLastFrameStart; // 0x90
	std::chrono::duration<int64_t, std::ratio<1, 1>> mMaxPlayerIdleTime; // 0x98
	std::unique_ptr<MinecraftCommands> mCommands; // 0xA0
	std::unique_ptr<GameSession> mGameSession; // 0xA8
	Timer *mSimTimer; // 0xB0
	Timer *mRealTimer; // 0xB8
	NetworkHandler *mNetworkHandler; // 0xC0
	PacketSender *mPacketSender; // 0xC8
	IMinecraftApp *mApp; // 0xD0
	uint8_t mClientSubId; // 0xD8
	std::shared_ptr<EntityRegistryOwned> mEntityRegistry; // OwnerPtrT<EntityRegistryRefTraits>; - 0xE0

	virtual std::shared_ptr<EntityRegistryOwned> getEntityRegistry();
	virtual ~Minecraft();

	MCAPI Level *getLevel() const;
	MCAPI ServerNetworkHandler *getServerNetworkHandler();
};

static_assert(offsetof(Minecraft, mGameModuleServer) == 0x28);
static_assert(offsetof(Minecraft, mCommands) == 0xA0);
static_assert(offsetof(Minecraft, mNetworkHandler) == 0xC0);
static_assert(sizeof(Minecraft) == 0xF0);