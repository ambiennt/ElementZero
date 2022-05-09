#pragma once

#include "../Core/Packet.h"
#include "../Actor/ActorUniqueID.h"
#include "../Math/Vec3.h"
#include "../dll.h"

class SpawnParticleEffectPacket : public Packet {
public:
	uint8_t mVanillaDimensionId; // 0x28
	ActorUniqueID mActorId; // 0x30
	Vec3 mPos; // 0x38
	std::string mEffectName; // 0x48

	SpawnParticleEffectPacket() {}
	SpawnParticleEffectPacket(uint8_t dimId, ActorUniqueID uid, Vec3 const& pos, std::string const& effect) :
		mVanillaDimensionId(dimId), mActorId(uid), mPos(pos), mEffectName(effect) {}
	inline ~SpawnParticleEffectPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(SpawnParticleEffectPacket, mVanillaDimensionId) == 0x28);
static_assert(offsetof(SpawnParticleEffectPacket, mActorId) == 0x30);
static_assert(offsetof(SpawnParticleEffectPacket, mPos) == 0x38);
static_assert(offsetof(SpawnParticleEffectPacket, mEffectName) == 0x48);