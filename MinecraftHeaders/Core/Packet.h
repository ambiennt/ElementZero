#pragma once

#include "../Net/NetworkPeer.h"
#include <cstdint>
#include <string>

enum class PacketPriority : int32_t {
	IMMEDIATE_PRIORITY    = 0,
	HIGH_PRIORITY         = 1,
	MEDIUM_PRIORITY       = 2,
	LOW_PRIORITY          = 3,
	NUMBER_OF_PRIORITIES  = 4,
};

enum class Compressibility : int32_t {
	Compressible    = 0,
	Incompressible  = 1,
};

enum class StreamReadResult : int32_t {
	Malformed = 0,
	Valid     = 1,
};

enum class MinecraftPacketIds : int32_t;
class BinaryStream;
class ReadOnlyBinaryStream;
class IPacketHandlerDispatcher;

struct ExtendedStreamReadResult {
	StreamReadResult mResult; // 0x0
	std::string mResultContext; // 0x8

	ExtendedStreamReadResult() : mResult(StreamReadResult::Malformed) {}
	ExtendedStreamReadResult(StreamReadResult result, std::string const& ctx)
		: mResult(result), mResultContext(ctx) {}
};

class Packet {
public:
	PacketPriority mPriority              = PacketPriority::MEDIUM_PRIORITY; // 0x8
	NetworkPeer::Reliability mReliability = NetworkPeer::Reliability::ReliableOrdered; // 0xC
	uint8_t mClientSubId                  = 0; // 0x10
	IPacketHandlerDispatcher *mHandler    = nullptr; // 0x18 - const
	Compressibility mCompressType         = Compressibility::Compressible; // 0x20 - mCompressible

	inline Packet()  {}
	inline Packet(Compressibility compressType) : mCompressType(compressType) {}
	virtual ~Packet() {}
	virtual MinecraftPacketIds getId() const              = 0;
	virtual std::string getName() const                   = 0;
	virtual void write(BinaryStream &) const              = 0;
	virtual StreamReadResult read(ReadOnlyBinaryStream &) = 0;
	inline virtual ExtendedStreamReadResult readExtended(ReadOnlyBinaryStream &stream) {
		return ExtendedStreamReadResult();
	}
	inline virtual bool disallowBatching() const {
		return false;
	}
};

static_assert(offsetof(Packet, mPriority) == 0x8);
static_assert(offsetof(Packet, mReliability) == 0xC);
static_assert(offsetof(Packet, mClientSubId) == 0x10);
static_assert(offsetof(Packet, mHandler) == 0x18);
static_assert(offsetof(Packet, mCompressType) == 0x20);
static_assert(sizeof(Packet) == 0x28);