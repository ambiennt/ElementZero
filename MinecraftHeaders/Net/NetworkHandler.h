#pragma once

#include "NetworkPeer.h"
#include "NetworkIdentifier.h"
#include "../dll.h"

#include <chrono>
#include <bitset>
#include <queue>

class PacketObserver;
class Scheduler;
class NetworkPacketRecoder;
class EncryptedNetworkPeer;
class BatchedNetworkPeer;
class Player;

class NetworkHandler {
public:
	class Connection {
	public:

		enum class Type : int32_t {
			Remote = 0x0,
			Local  = 0x1,
		};

		NetworkIdentifier mId;
		Type mType;
		std::weak_ptr<NetworkPacketRecoder> mNetworkPacketRecorder;
		std::weak_ptr<EncryptedNetworkPeer> mEncryptedPeer;
		std::weak_ptr<BatchedNetworkPeer> mBatchedPeer;
		std::shared_ptr<NetworkPeer> mPeer;
		std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<int64_t, std::ratio<1, 1000000000>>> mLastPacketTime, mClosedTime;
		bool mShouldCloseConnection, mDisconnected;
		std::bitset<2> mPausedChannels;
		std::queue<std::string> mResumedPackets;
		std::array<std::vector<std::string>, 2> mPausedPackets;

		MCAPI Connection(
			NetworkIdentifier const &id, std::shared_ptr<NetworkPeer> peer,
			std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<int64_t, std::ratio<1, 1000000000>>> lastPacketTime,
			bool isSafeAndFast, PacketObserver *packetObserver, Scheduler &mainThread);
		MCAPI NetworkPeer::DataStatus receivePacket(std::string &);
		inline bool isChannelPaused(uint32_t channelId) { return this->mPausedChannels.test(channelId); }
	};
	
private:
	MCAPI NetworkHandler::Connection* _getConnectionFromId(NetworkIdentifier const &id) const;
public:
	MCAPI void disconnect();
	MCAPI void runEvents();
	MCAPI NetworkPeer *getPeerForUser(NetworkIdentifier const &);
	inline NetworkHandler::Connection* getConnectionFromId(NetworkIdentifier const &id) const {
		return this->_getConnectionFromId(id);
	}
};

static_assert(offsetof(NetworkHandler::Connection, mNetworkPacketRecorder) == 0xA0);