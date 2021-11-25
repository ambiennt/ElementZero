#pragma once

#include <cstdint>
#include <string>

enum class PacketPriority {
	IMMEDIATE_PRIORITY    = 0,
	HIGH_PRIORITY         = 1,
	MEDIUM_PRIORITY       = 2,
	LOW_PRIORITY          = 3,
	NUMBER_OF_PRIORITIES  = 4
};

enum class Compressibility {
	Compressible    = 0,
	Incompressible  = 1
};

enum class MinecraftPacketIds;
enum class StreamReadResult;
enum class ExtendedStreamReadResult;
enum class MinecraftPacketIds;
class BinaryStream;
class ReadOnlyBinaryStream;

class Packet {
public:
	PacketPriority mPriority = PacketPriority::MEDIUM_PRIORITY;
	int32_t mReliability     = 1; // NetworkPeer::Reliability
	uint8_t mClientSubId     = 0;
	int64_t mHandler         = 0;
	int32_t mCompressType    = 0; // Compressibility::Compressible

	inline Packet(uint32_t compress) : mCompressType(!compress) {}
	inline Packet() {}
	inline virtual ~Packet() {}
	virtual MinecraftPacketIds getId() const              = 0;
	virtual std::string getName() const                   = 0;
	virtual void write(BinaryStream &) const              = 0;
	virtual StreamReadResult read(ReadOnlyBinaryStream &) = 0;
	inline virtual ExtendedStreamReadResult readExtended(ReadOnlyBinaryStream &stream) {
		return (ExtendedStreamReadResult) read(stream);
	}
	inline virtual bool disallowBatching() const { return false; }
};

static_assert(offsetof(Packet, mPriority) == 0x8);
static_assert(offsetof(Packet, mReliability) == 0xC);
static_assert(offsetof(Packet, mClientSubId) == 0x10);
static_assert(offsetof(Packet, mHandler) == 0x18);
static_assert(offsetof(Packet, mCompressType) == 0x20);
static_assert(sizeof(Packet) == 0x28);