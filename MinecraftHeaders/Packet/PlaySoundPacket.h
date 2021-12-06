#pragma once

#include "../Core/Packet.h"
#include "../Math/Vec3.h"
#include "../Actor/Actor.h"
#include "../dll.h"

class PlaySoundPacket : public Packet {
public:
	std::string mName; // same as in /playsound
	Vec3 mPos;
	float mVolume = 1.0f;
	float mPitch  = 1.0f;

	inline ~PlaySoundPacket() {}
	MCAPI PlaySoundPacket(void);
	MCAPI PlaySoundPacket(std::string name, const Vec3& pos, float volume, float pitch);
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(PlaySoundPacket, mName) == 0x28);
static_assert(offsetof(PlaySoundPacket, mPos) == 0x48);
static_assert(offsetof(PlaySoundPacket, mVolume) == 0x54);
static_assert(offsetof(PlaySoundPacket, mPitch) == 0x58);
static_assert(sizeof(PlaySoundPacket) == 0x60);