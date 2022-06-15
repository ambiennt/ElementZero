#pragma once

#include "../Core/Packet.h"
#include "../Math/Vec3.h"
#include "../dll.h"

enum class LevelSoundEvent : int32_t;

class LevelSoundEventPacket : public Packet {
public:
	LevelSoundEvent mEventId;
	Vec3 mPos;
	int32_t mData;
	std::string mEntityIdentifier; // usually left blank
	bool mIsBabyMob;               // if true the sound will be pitched up
	bool mIsGlobal;                // can be heard throughout the entire dimension?

	LevelSoundEventPacket() {}
	LevelSoundEventPacket(LevelSoundEvent id, Vec3 const& pos, int32_t data, std::string const& entityIdentifier, bool isBabyMob, bool isGlobal)
		: mEventId(id), mPos(pos), mData(data), mEntityIdentifier(entityIdentifier), mIsBabyMob(isBabyMob), mIsGlobal(isGlobal) {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(LevelSoundEventPacket, mEventId) == 0x28);
static_assert(offsetof(LevelSoundEventPacket, mPos) == 0x2C);
static_assert(offsetof(LevelSoundEventPacket, mData) == 0x38);
static_assert(offsetof(LevelSoundEventPacket, mEntityIdentifier) == 0x40);
static_assert(offsetof(LevelSoundEventPacket, mIsBabyMob) == 0x60);
static_assert(offsetof(LevelSoundEventPacket, mIsGlobal) == 0x61);