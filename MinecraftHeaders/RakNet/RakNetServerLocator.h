#pragma once

#include <mutex>
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <unordered_map>
#include <queue>

#include "../dll.h"
#include "../Net/AsynchronousIPResolver.h"
#include "../Net/PingedCompatibleServer.h"
#include "RakPeer.h"

class RakNetInstance;

enum class GameType : int32_t;

class ServerLocator {
public:
	virtual ~ServerLocator();
	virtual void announceServer(const std::string &playerName, const std::string &worldName,
		GameType, int32_t numPlayers, int32_t maxNumPlayers, bool isJoinableThroughServerScreen) = 0;
	virtual void stopAnnouncingServer() = 0;
	virtual void findServers(int32_t port, int32_t portv6) = 0;
	virtual void addCustomServer(const std::string &address, int32_t port) = 0;
	virtual void addCustomServer(const AsynchronousIPResolver &futureIP, int32_t port) = 0;
	virtual void stopFindingServers() = 0;
	virtual std::vector<PingedCompatibleServer> getServerList() const = 0;
	virtual void clearServerList() = 0;
	virtual bool isIPv4Supported() = 0;
	virtual bool isIPv6Supported() = 0;
	virtual void setHostGUID(std::function<RakNet::RakNetGUID __cdecl()> func) = 0;
	virtual float getPingTimeForGUID(const std::string &guid) = 0;
	virtual void checkCanConnectToCustomServerAsync(std::string hostIpAddress,
		int32_t port, std::function<void __cdecl(bool)> callback) = 0;
};

class RakNetServerLocator : public ServerLocator {
public:

	class PingRateRecorder {
	public:
		std::vector<uint64_t> mPingTimes; // 0x0
		uint32_t mAveragingWindowSize; // 0x18
		float mAverageTime; // 0x1C
		float mLastPingTime; // 0x20
		uint32_t mStartTime; // 0x24
		uint32_t mPingTimesIndex; // 0x28
		int32_t mIpVersion; // 0x2C
		bool mPingStarted; // 0x30
		bool mAveraging; // 0x31
	};

	std::unordered_map<std::string, std::string> mOriginalAddresses; // 0x8
	std::unordered_map<std::string, RakNetServerLocator::PingRateRecorder> mPingTimeRecorders; // 0x48
	std::unordered_map<std::string, std::string> mGuidCache; // 0x88
	std::function<RakNet::RakNetGUID __cdecl()> mGetHostGUID; // 0xC8
	RakNetInstance *mRaknetInstance; // 0x108
	std::unique_ptr<RakNet::RakPeerInterface, void (__cdecl*)(RakNet::RakPeerInterface *)> mFinderPeer; // 0x110
	RakPeerHelper mFinderPeerHelper; // 0x120
	std::vector<PingedCompatibleServer> mAvailableServers; // 0x138
	bool mIsPingingForServers; // 0x150
	bool mIsServer; // const - 0x151
	int32_t mPingPort; // 0x154
	int32_t mPingPortv6; // 0x158
	uint32_t mLastPingTime; // 0x15C
	std::vector<std::string> mBroadcastAddresses; // 0x160
	std::vector<std::string> mMulticastAddressesV6; // 0x178
	std::queue<std::pair<AsynchronousIPResolver, int32_t>> mPingQueue; // 0x190
	std::function<void __cdecl(bool)> mServerValidationCallback; // 0x1B8
	std::string mServerWaitingToValidate; // 0x1F8
	uint32_t mLastPingToServerWaitingToValidateTime; // 0x218
	std::recursive_mutex mServerListLock; // 0x220

	inline RakNet::RakPeer* getRakPeer() const {
		return (RakNet::RakPeer*)(this->mFinderPeer.get());
	}
};

static_assert(offsetof(RakNetServerLocator, mFinderPeer) == 0x110);
static_assert(sizeof(RakNetServerLocator) == 0x270);