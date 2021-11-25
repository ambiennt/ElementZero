#pragma once

#include "../Core/BinaryStream.h"
#include "../Core/Packet.h"
#include "../Math/NetworkBlockPosition.h"
#include "../Math/BlockPos.h"
#include "../dll.h"

class UpdateBlockPacket : public Packet {
public:
	BlockPos pos;
	uint32_t runtimeId;
	uint8_t flags;
	uint32_t dataLayerId;

	inline ~UpdateBlockPacket() {}

	MCAPI UpdateBlockPacket(void);
	MCAPI UpdateBlockPacket(BlockPos const &pos, unsigned int dataLayerId, class Block const &block, unsigned char flags);

	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};