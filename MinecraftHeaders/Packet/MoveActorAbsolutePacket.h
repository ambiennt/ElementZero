#pragma once

#include "../Core/Packet.h"
#include "../Math/Vec3.h"
#include "../Actor/ActorRuntimeID.h"
#include "../Actor/Actor.h"
#include "../dll.h"

struct MoveActorAbsoluteData {
	struct Header {
		union {
			struct {
				uint8_t mIsOnGround : 1;
				uint8_t mTeleported : 1;
				uint8_t mForceMoveLocalEntity : 1;
			};
			uint8_t mRaw = 0x0;
		};
	};
	ActorRuntimeID mRuntimeId;
	MoveActorAbsoluteData::Header mFlags; // mHeader
	Vec3 mPos = Vec3::ZERO;
	uint8_t mRotX = 0, mRotY = 0, mRotYHead = 0;

	MoveActorAbsoluteData() {}
	MCAPI MoveActorAbsoluteData(Actor const &);
	inline ~MoveActorAbsoluteData() {}
};

class MoveActorAbsolutePacket : public Packet {
public:

	MoveActorAbsoluteData mMoveData;

	MoveActorAbsolutePacket() {}
	inline ~MoveActorAbsolutePacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(MoveActorAbsoluteData, mFlags) == 0x8);
static_assert(sizeof(MoveActorAbsolutePacket) == 0x48);