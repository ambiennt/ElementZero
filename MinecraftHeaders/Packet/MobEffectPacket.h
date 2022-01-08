#pragma once

#include "../Core/Packet.h"
#include "../Actor/ActorRuntimeID.h"
#include "../dll.h"

class MobEffectPacket : public Packet {
public:

	enum class Event : uint8_t {
		Add = 1,
		Update = 2,
		Remove = 3
	};

	ActorRuntimeID mRuntimeId;
	int32_t mEffectDurationTicks;
	Event mEventId;
	int32_t mEffectId;
	int32_t mEffectAmplifier;
	bool mShowParticles;

	inline ~MobEffectPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(sizeof(MobEffectPacket) == 0x48);