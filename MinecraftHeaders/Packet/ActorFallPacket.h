#pragma once

#include "../Core/Packet.h"
#include "../Actor/ActorRuntimeID.h"
#include "../dll.h"

class ActorFallPacket : public Packet {
public:
	ActorRuntimeID mRuntimeId;
	float mFallDistance = 0.f;
	bool mInVoid        = false;

	inline ~ActorFallPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};