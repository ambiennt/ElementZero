#pragma once

#include "../Core/Packet.h"
#include "../Math/BlockPos.h"
#include "../dll.h"

class PlaySoundPacket : public Packet {
public:
	std::string mName; // same as in /playsound
	BlockPos mPos; // NetworkBlockPosition
	float mVolume = 1.f, mPitch = 1.f;

	PlaySoundPacket() {}

	// not sure why it needs the * 8 conversion, must be an fmod thing on the client
	PlaySoundPacket(const std::string &name, const BlockPos &pos, float volume = 1.f, float pitch = 1.f)
		: mName(name), mPos(pos * 8), mVolume(volume), mPitch(pitch) {}

	inline ~PlaySoundPacket() {}
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