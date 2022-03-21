#pragma once

#include "../Core/Packet.h"
#include "../Math/Vec3.h"
#include "../Actor/ActorRuntimeID.h"
#include "../dll.h"

class SetActorMotionPacket : public Packet {
public:
	ActorRuntimeID mRuntimeId; // 0x28
	Vec3 mMotion = Vec3::ZERO; // 0x30

	SetActorMotionPacket() {};
	SetActorMotionPacket(ActorRuntimeID rid, Vec3 motion) : mRuntimeId(rid), mMotion(motion) {}
	inline ~SetActorMotionPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(SetActorMotionPacket, mRuntimeId) == 0x28);
static_assert(offsetof(SetActorMotionPacket, mMotion) == 0x30);