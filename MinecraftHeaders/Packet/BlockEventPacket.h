#pragma once

#include "../Core/Packet.h"
#include "../Math/BlockPos.h"
#include "../dll.h"

class BlockEventPacket : public Packet {
public:
	BlockPos mPos;
	int32_t mB0 = 0, mB1 = 0; // I have no clue what these are

	inline ~BlockEventPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};