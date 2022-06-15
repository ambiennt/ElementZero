#pragma once

#include <cstdint>
#include <string>
#include <functional>
#include <memory>

#include "../dll.h"

enum class Compressibility : int32_t;

class NetworkPeer {
public:

	enum class Reliability : int32_t {
		Reliable            = 0x0,
		ReliableOrdered     = 0x1,
		Unreliable          = 0x2,
		UnreliableSequenced = 0x3,
	};

	enum class DataStatus : int32_t {
		HasData    = 0x0,
		NoData     = 0x1,
		BrokenData = 0x2,
	};

	enum class NetworkLoad : int32_t {
		Unrestricted = 0x0,
		Low          = 0x1,
		Medium       = 0x2,
		High         = 0x3,
	};

	struct NetworkStatus {
		NetworkLoad mLoad;
		int32_t mCurrentPing, mAveragePing, mApproximateMaxBps;
		float mCurrentPacketLoss, mAveragePacketLoss;
		uint64_t mTotalBytesReceived, mTotalBytesSent;
	};

	std::shared_ptr<NetworkPeer> mPeer;

	virtual ~NetworkPeer();
	virtual void sendPacket(std::string const &data, Reliability reliability,
		int32_t orderingChannel, uint16_t compressionThreshold, Compressibility compressible) = 0;
	virtual DataStatus receivePacket(std::string &outData) = 0;
	virtual NetworkStatus getNetworkStatus() = 0;
	virtual void update();
	virtual void flush(std::function<void()> &&callback);
};

static_assert(sizeof(NetworkPeer) == 0x18);