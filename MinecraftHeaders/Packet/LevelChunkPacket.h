#pragma once

#include "../Core/Packet.h"
#include "../Math/ChunkPos.h"
#include "../dll.h"

class LevelChunkPacket : public Packet {
public:

	struct SubChunkMetadata {
		uint64_t mBlobId;
	};

	bool mCacheEnabled; // 0x28
	char wtf[0x7];
	ChunkPos mPos; // 0x30
	std::string mSerializedChunk; // 0x38
	uint64_t mSubChunksCount; // 0x58
	std::vector<SubChunkMetadata> mCacheMetadata; // 0x60

	inline ~LevelChunkPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(LevelChunkPacket, mCacheEnabled) == 0x28);
static_assert(offsetof(LevelChunkPacket, mPos) == 0x30);
static_assert(offsetof(LevelChunkPacket, mSerializedChunk) == 0x38);
static_assert(offsetof(LevelChunkPacket, mSubChunksCount) == 0x58);
static_assert(offsetof(LevelChunkPacket, mCacheMetadata) == 0x60);
static_assert(sizeof(LevelChunkPacket) == 0x78);