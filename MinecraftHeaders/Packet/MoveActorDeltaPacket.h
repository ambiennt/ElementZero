#pragma once

#include "../Core/Packet.h"
#include "../Actor/ActorRuntimeID.h"
#include "../dll.h"

struct MoveActorDeltaData {

	enum struct Flags : int16_t {
		FLAG_HAS_X = 0x1,
		FLAG_HAS_Y = 0x2,
		FLAG_HAS_Z = 0x4,
		FLAG_HAS_PITCH = 0x8,
		FLAG_HAS_YAW = 0x10,
		FLAG_HAS_HEAD_YAW = 0x20,
		FLAG_GROUND = 0x40,
		FLAG_TELEPORT = 0x80,
		FORCE_MOVE = 0x100
	};

	ActorRuntimeID mRuntimeId; // 0x0
	int16_t mFlags; // 0x8 - MoveActorDeltaData::Flags (actually a MoveActorAbsoluteData::Header in BDS)
	int32_t mDeltaPositionX; // 0xC
	int32_t mDeltaPositionY; // 0x10
	int32_t mDeltaPositionZ; // 0x14
	int8_t mRotX; // 0x18
	int8_t mRotY; // 0x19
	int8_t mRotYHead; // 0x1A
	MoveActorAbsoluteData mPreviousData; // 0x20
};

class MoveActorDeltaPacket : public Packet {
public:

	MoveActorDeltaData mMoveData; // 0x28

	inline ~MoveActorDeltaPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(sizeof(MoveActorDeltaData) == 0x40);
static_assert(sizeof(MoveActorDeltaPacket) == 0x68);