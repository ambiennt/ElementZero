#pragma once

#include "../Core/BinaryStream.h"
#include "../Core/Packet.h"
#include "../Math/NetworkBlockPosition.h"
#include "../Math/BlockPos.h"
#include "../dll.h"

class UpdateBlockPacket : public Packet {
public:
	BlockPos mPos;
	uint32_t mRuntimeId;
	uint8_t mUpdateFlags;
	uint32_t mDataLayerId;

	inline ~UpdateBlockPacket() {}

	MCAPI UpdateBlockPacket(void);
	MCAPI UpdateBlockPacket(BlockPos const &pos, uint32_t dataLayerId, class Block const &block, uint8_t flags);

	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};