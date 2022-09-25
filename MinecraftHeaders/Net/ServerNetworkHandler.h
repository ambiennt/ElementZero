#pragma once

#include <hook.h>
#include <modutils.h>
#include "../Actor/ServerPlayer.h"
#include "../Core/PackIdVersion.h"
#include "NetworkIdentifier.h"
#include "../Core/mce.h"
#include "../dll.h"
#include <mutex>

class Player;
class NetworkIdentifier;

class ServerNetworkHandler /*: public NetEventCallback, public LevelListener, public Social::MultiplayerServiceObserver, public Social::XboxLiveUserObserver*/ {
	//MCAPI void _onPlayerLeft(ServerPlayer *player, bool useDefaultDisconnectMsg);
	MCAPI ServerPlayer* _getServerPlayer(NetworkIdentifier const& netId, uint8_t subId);
	MCAPI int32_t _getActiveAndInProgressPlayerCount(mce::UUID excludePlayer) const;
	inline void onDisconnect(const NetworkIdentifier& netId, const std::string& disconnectMsg, bool skipPlayerLeftChatMsg) { // do not use, use forceDisconnectClient instead
		return CallServerClassMethod<void>(
			"?onDisconnect@ServerNetworkHandler@@UEAAXAEBVNetworkIdentifier@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N1@Z",
			this, netId, disconnectMsg, skipPlayerLeftChatMsg, std::string{} /*std::string const& telemetryOverride*/);
	}
public:
	class Client;

	// do not use, use forceDisconnectClient instead
	// useDefaultDisconnectMsg set to true overrides the contents of disconnectMsg
	MCAPI void disconnectClient(NetworkIdentifier const& netId, uint8_t subId, std::string const &disconnectMsg, bool useDefaultDisconnectMsg);
	MCAPI void updateServerAnnouncement();

	inline ServerPlayer* getServerPlayer(NetworkIdentifier const& netId, uint8_t subId) {
		return this->_getServerPlayer(netId, subId);
	}

	inline int32_t getActiveAndInProgressPlayerCount(mce::UUID const& excludePlayer = mce::UUID::EMPTY) const {
		return this->_getActiveAndInProgressPlayerCount(excludePlayer);
	}

	inline std::string const& getMOTD() const {
		return this->mServerName;
	}

	inline void setMOTD(std::string const& motd) {
		this->mServerName = motd;
	}

	// - if disconnectMsg.empty(), the client will default to disconnectionScreen.disconnected
	// - skipPlayerLeftChatMsg set to true will prevent the "%s left the game" message from outputting in the in-game chat
	BASEAPI void forceDisconnectClient(const NetworkIdentifier& netId, uint8_t subId,
		 bool skipPlayerLeftChatMsg, const std::string& disconnectMsg = std::string{});
	BASEAPI void forceDisconnectClient(const Player& player,
		bool skipPlayerLeftChatMsg, const std::string& disconnectMsg = std::string{});

	BUILD_ACCESS_MUT(class GameCallbacks *, mGameCallbacks, 0x30);
	BUILD_ACCESS_MUT(class Level *, mLevel, 0x38);
	BUILD_ACCESS_MUT(class NetworkHandler *, mNetworkHandler, 0x40);
	BUILD_ACCESS_MUT(class PrivateKeyManager *, mServerKeys, 0x48);
	BUILD_ACCESS_MUT(class ServerLocator * , mServerLocator, 0x50);
	BUILD_ACCESS_MUT(class PacketSender *, mPacketSender, 0x58);
	BUILD_ACCESS_MUT(bool, mUseWhitelist, 0x60);
	BUILD_ACCESS_MUT(class Whitelist *, mWhitelist, 0x68);
	BUILD_ACCESS_MUT(class PermissionsFile *, mPermissionsFile, 0x70);
	BUILD_ACCESS_MUT(class BlackList, mServerBlackList, 0x78); // not a pointer
	BUILD_ACCESS_MUT(bool, mRequireTrustedAuthentication, 0xE0);
	BUILD_ACCESS_MUT(bool, mHasDisplayedPackErrors, 0xE1);
	BUILD_ACCESS_MUT(class NetworkIdentifier, mMyId, 0xE8); // localplayer NetworkIdentifier?
	BUILD_ACCESS_MUT(const int32_t, mMaxChunkRadius, 0x180);
	BUILD_ACCESS_MUT(class MinecraftCommands *, mMinecraftCommands, 0x188);
	BUILD_ACCESS_MUT(class IMinecraftApp *, mApp, 0x190);
	BUILD_ACCESS_MUT(class TextFilteringProcessor *, mTextFilteringProcessor, 0x198);

	//using clientManagerPtr = std::unique_ptr<class ClientBlobCache::Server::ActiveTransfersManager>;
	//BUILD_ACCESS_MUT(clientManagerPtr, mClientCacheManager, 0x1A0);

	BUILD_ACCESS_MUT(std::unique_ptr<class ClassroomModeNetworkHandler>, mCompanionHandler,  0x1A8);
	BUILD_ACCESS_MUT(std::string, mTenantId, 0x1B0);
	BUILD_ACCESS_MUT(std::string, mShareableIdentityToken, 0x1D0);
	BUILD_ACCESS_MUT(std::mutex, mValidatePlayerMutex, 0x1F0);
	BUILD_ACCESS_MUT(bool, mAllowIncoming, 0x240);
	BUILD_ACCESS_MUT(class mce::UUID, mHostPlayerId, 0x248);
	BUILD_ACCESS_MUT(std::string, mServerName, 0x258);
	BUILD_ACCESS_MUT(std::string, mServerType, 0x278); // defaults to "normal", can also be "realms"
	BUILD_ACCESS_MUT(std::string, mMultiplayerCorrelationId, 0x298);
	BUILD_ACCESS_MUT(std::vector<std::string>, mTrustedKeys, 0x2B8);
	BUILD_ACCESS_MUT(int32_t, mMaxNumPlayers, 0x2D0);
	BUILD_ACCESS_MUT(std::unordered_set<class mce::UUID>, mKnownEmotePieceIdLookup, 0x2D8);
	BUILD_ACCESS_MUT(std::vector<class mce::UUID>, mKnownEmotePieceIds, 0x318);

	using clientMap = std::unordered_map<class NetworkIdentifier, std::unique_ptr<class ServerNetworkHandler::Client>>;
	BUILD_ACCESS_MUT(clientMap, mClients, 0x330);

	BUILD_ACCESS_MUT(bool, mIsTrial, 0x370);

	using packIdKeyMap = std::unordered_map<struct PackIdVersion, std::string>;
	BUILD_ACCESS_MUT(packIdKeyMap, mPackIdToContentKey, 0x378);

	BUILD_ACCESS_MUT(std::unique_ptr<class GameSpecificNetEventCallback>, mGameSpecificNetEventCallback, 0x3B8);
};