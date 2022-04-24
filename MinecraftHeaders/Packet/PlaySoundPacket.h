#pragma once

#include "../Core/Packet.h"
#include "../Math/Vec3.h"
#include "../Actor/Actor.h"
#include "../dll.h"

class PlaySoundPacket : public Packet {
public:
	std::string mName; // same as in /playsound
	BlockPos mPos; // NetworkBlockPosition
	float mVolume = 1.f, mPitch = 1.f;

	inline ~PlaySoundPacket() {}
	PlaySoundPacket() {}
	PlaySoundPacket(const std::string &name, const BlockPos &pos, float volume = 1.f, float pitch = 1.f) {
		this->mName = name;
		this->mPos = pos * 8; // for some reason it needs this conversion idk
		this->mVolume = volume;
		this->mPitch = pitch;
	}
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