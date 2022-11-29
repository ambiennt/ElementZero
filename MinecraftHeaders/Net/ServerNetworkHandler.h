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
	MCAPI ServerPlayer* _getServerPlayer(NetworkIdentifier const& netId, uint8_t subId);
	MCAPI int32_t _getActiveAndInProgressPlayerCount(mce::UUID excludePlayer) const;

	// do not call directly, use forceDisconnectClient instead
	// ServerNetworkHandler::onDisconnect cleans up and saves all player data on the server and closes the connection
	// however it doesnt have an interface for customizing the disconnect screen message
	inline void onDisconnect(const NetworkIdentifier& netId, bool skipPlayerLeftChatMsg) {
		return CallServerClassMethod<void>(
			"?onDisconnect@ServerNetworkHandler@@UEAAXAEBVNetworkIdentifier@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@_N1@Z",
			this,
			netId,
			/*const std::string& disconnectMsg*/ std::string{}, // unused param
			skipPlayerLeftChatMsg, // whether or not to show the "%s has left the game" in chat
			/*std::string const& telemetryOverride*/ std::string{} // unused param
		);
	}
public:
	class Client;

	MCAPI void updateServerAnnouncement();

	inline ServerPlayer* getServerPlayer(NetworkIdentifier const& netId, uint8_t subId) {
		return this->_getServerPlayer(netId, subId);
	}

	inline int32_t getActiveAndInProgressPlayerCount(mce::UUID const& excludePlayer = mce::UUID::EMPTY) const {
		return this->_getActiveAndInProgressPlayerCount(excludePlayer);
	}

	inline void setMOTD(const std::string &str) {
		this->mServerName = str;
	}

	// - if disconnectMsg.empty(), the client will default to disconnectionScreen.disconnected
	// - skipPlayerLeftChatMsg set to true will prevent the "%s left the game" message from outputting in the in-game chat
	BASEAPI void forceDisconnectClient(const NetworkIdentifier& netId, uint8_t subId,
		 bool skipPlayerLeftChatMsg, const std::string& disconnectMsg = std::string{});
	BASEAPI void forceDisconnectClient(const Player& player,
		bool skipPlayerLeftChatMsg, const std::string& disconnectMsg = std::string{});

	CLASS_FIELD(mGameCallbacks, 0x30, class GameCallbacks *);
	CLASS_FIELD(mLevel, 0x38, class Level *);
	CLASS_FIELD(mNetworkHandler, 0x40, class NetworkHandler *);
	CLASS_FIELD(mServerKeys, 0x48, class PrivateKeyManager *);
	CLASS_FIELD(mServerLocator, 0x50, class ServerLocator * );
	CLASS_FIELD(mPacketSender, 0x58, class PacketSender *);
	CLASS_FIELD(mUseWhitelist, 0x60, bool);
	CLASS_FIELD(mWhitelist, 0x68, class Whitelist *);
	CLASS_FIELD(mPermissionsFile, 0x70, class PermissionsFile *);
	CLASS_FIELD(mServerBlackList, 0x78, class BlackList); // not a pointer
	CLASS_FIELD(mRequireTrustedAuthentication, 0xE0, bool);
	CLASS_FIELD(mHasDisplayedPackErrors, 0xE1, bool);
	CLASS_FIELD(mMyId, 0xE8, class NetworkIdentifier); // localplayer NetworkIdentifier?
	CLASS_FIELD(mMaxChunkRadius, 0x180, const int32_t);
	CLASS_FIELD(mMinecraftCommands, 0x188, class MinecraftCommands *);
	CLASS_FIELD(mApp, 0x190, class IMinecraftApp *);
	CLASS_FIELD(mTextFilteringProcessor, 0x198, class TextFilteringProcessor *);
	//CLASS_FIELD(mClientCacheManager, 0x1A0, std::unique_ptr<class ClientBlobCache::Server::ActiveTransfersManager>);
	CLASS_FIELD(mCompanionHandler,  0x1A8, std::unique_ptr<class ClassroomModeNetworkHandler>);
	CLASS_FIELD(mTenantId, 0x1B0, std::string);
	CLASS_FIELD(mShareableIdentityToken, 0x1D0, std::string);
	CLASS_FIELD(mValidatePlayerMutex, 0x1F0, std::mutex);
	CLASS_FIELD(mAllowIncoming, 0x240, bool);
	CLASS_FIELD(mHostPlayerId, 0x248, class mce::UUID);
	CLASS_FIELD(mServerName, 0x258, std::string); // the MOTD shown in the client server screen
	CLASS_FIELD(mServerType, 0x278, std::string); // defaults to "normal", can also be "realms"
	CLASS_FIELD(mMultiplayerCorrelationId, 0x298, std::string);
	CLASS_FIELD(mTrustedKeys, 0x2B8, std::vector<std::string>);
	CLASS_FIELD(mMaxNumPlayers, 0x2D0, int32_t);
	CLASS_FIELD(mKnownEmotePieceIdLookup, 0x2D8, std::unordered_set<class mce::UUID>);
	CLASS_FIELD(mKnownEmotePieceIds, 0x318, std::vector<class mce::UUID>);
	CLASS_FIELD(mClients, 0x330, std::unordered_map<class NetworkIdentifier, std::unique_ptr<class ServerNetworkHandler::Client>>);
	CLASS_FIELD(mIsTrial, 0x370, bool);
	CLASS_FIELD(mPackIdToContentKey, 0x378, std::unordered_map<struct PackIdVersion, std::string>);
	CLASS_FIELD(mGameSpecificNetEventCallback, 0x3B8, std::unique_ptr<class GameSpecificNetEventCallback>);
};