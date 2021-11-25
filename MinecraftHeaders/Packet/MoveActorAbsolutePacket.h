#pragma once

#include "../Core/Packet.h"
#include "../Math/Vec3.h"
#include "../Actor/ActorRuntimeID.h"
#include "../dll.h"

enum class Flags : uint8_t { 
	GROUND     = 0x1,
	TELEPORT   = 0x2,
	FORCE_MOVE = 0x4
};

class MoveActorAbsolutePacket : public Packet {
public:

	ActorRuntimeID mRuntimeId;
	uint8_t mFlags = 0x1; // Flags::GROUND, mHeader - MoveActorAbsoluteData::Header
	Vec3 mPos;
	uint8_t mRotX = 0, mRotY = 0, mRotYHead = 0;

	inline ~MoveActorAbsolutePacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};