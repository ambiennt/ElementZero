#pragma once

#include "../Core/Packet.h"
#include "../Actor/ActorRuntimeID.h"
#include "../dll.h"

class AnimatePacket : public Packet {
public:

	enum class Action {
		NoAction         = 0,
		Swing            = 1,
		WakeUp           = 3,
		CriticalHit      = 4,
		MagicCriticalHit = 5,
		RowRight         = 128,
		RowLeft          = 129
	};

	ActorRuntimeID mRuntimeId;
	Action mAction;
	float mData; // boat rowing time

	inline ~AnimatePacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(AnimatePacket, mRuntimeId) == 0x28);
static_assert(offsetof(AnimatePacket, mAction) == 0x30);
static_assert(offsetof(AnimatePacket, mData) == 0x34);