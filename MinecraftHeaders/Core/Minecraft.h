#pragma once

#include "../dll.h"
#include "Core.h"

#include <modutils.h>
#include <memory>
#include <chrono>

class Level;
class ServerNetworkHandler;
class MinecraftCommands;

class Minecraft {
public:

	class GameCallbacks *mGameCallbacks; // 0x8
	class IMinecraftEventing *mEventing; // 0x10
	std::unique_ptr<class ResourcePackManager> mResourceLoader; // 0x18
	std::unique_ptr<class StructureManager> mStructureManager; // 0x20
	std::shared_ptr<class GameModuleServer> mGameModuleServer; // 0x28
	class Whitelist *mWhitelist; // 0x38
	class PermissionsFile *mPermissionsFile; // 0x40
	std::unique_ptr<class PrivateKeyManager> mServerKeys; // 0x48
	const std::string mSaveGamePath; // 0x50
	class Core::FilePathManager *mFilePathManager; // 0x70
	class ServerMetrics *mServerMetrics; // 0x78
	bool mLevelIsCorrupted; // 0x80
	long double mFrameDuration; // 0x88
	long double mLastFrameStart; // 0x90
	std::chrono::duration<int64_t, std::ratio<1, 1>> mMaxPlayerIdleTime; // 0x98
	std::unique_ptr<class MinecraftCommands> mCommands; // 0xA0
	std::unique_ptr<class GameSession> mGameSession; // 0xA8
	class Timer *mSimTimer; // 0xB0
	class Timer *mRealTimer; // 0xB8
	class NetworkHandler *mNetworkHandler; // 0xC0
	class PacketSender *mPacketSender; // 0xC8
	class IMinecraftApp *mApp; // 0xD0
	uint8_t mClientSubId; // 0xD8
	std::shared_ptr<class EntityRegistryOwned> mEntityRegistry; // OwnerPtrT<EntityRegistryRefTraits>; - 0xE0

	virtual std::shared_ptr<class EntityRegistryOwned> getEntityRegistry(void);
	virtual ~Minecraft();

	MCAPI Level *getLevel() const;
	MCAPI ServerNetworkHandler *getServerNetworkHandler();
	BASEAPI MinecraftCommands *getCommands();
};

static_assert(offsetof(Minecraft, mGameModuleServer) == 0x28);
static_assert(offsetof(Minecraft, mCommands) == 0xA0);
static_assert(offsetof(Minecraft, mNetworkHandler) == 0xC0);
static_assert(sizeof(Minecraft) == 0xF0);