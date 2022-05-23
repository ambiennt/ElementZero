#pragma once

#include "../Core/Packet.h"
#include "../Math/Vec3.h"
#include "../dll.h"

class SpawnExperienceOrbPacket : public Packet {
public:
	Vec3 mPos; // 0x28
	int32_t mCount; // 0x34

	SpawnExperienceOrbPacket(Vec3 const& pos, int32_t count) : mPos(pos), mCount(count) {}
	inline ~SpawnExperienceOrbPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(SpawnExperienceOrbPacket, mPos) == 0x28);
static_assert(offsetof(SpawnExperienceOrbPacket, mCount) == 0x34);