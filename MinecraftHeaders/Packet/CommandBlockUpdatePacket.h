#pragma once

#include "../Core/Packet.h"
#include "../Actor/ActorRuntimeID.h"
#include "../Math/BlockPos.h"
#include "../dll.h"

enum class CommandBlockMode : int16_t {
	Normal = 0,
	Repeating = 1,
	Chain = 2,
};

class CommandBlockUpdatePacket : public Packet {
public:
    BlockPos mBlockPos; // 0x28
    CommandBlockMode mMode; // 0x34
    bool mRedstoneMode, mIsConditional; // 0x36
    ActorRuntimeID mEntityId; // 0x37
    std::string mCommand, mLastOutput, mName; // 0x40, 0x60, 0x80
    int32_t mTickDelay; // 0xA0
    bool mTrackOutput, mExecuteOnFirstTick, mIsBlock; // 0xA4, 0xA5, 0xA6

	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(sizeof(CommandBlockUpdatePacket) == 0xA8);