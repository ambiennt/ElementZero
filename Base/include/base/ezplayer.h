#pragma once

#include "base.h"
#include <Math/Vec3.h>
#include <cstdint>

// add custom player fields, constants, and methods here
// methods should only be if you don't want them inlined or they have a niche purpose (otherwise just put them in Player.h)
// prefix non-inlined functions with BASEAPI and have an definition in compat.cpp)
// player fields will, for the most part, only be updated/return non-default values if the custom mod that uses them is enabled

class EZPlayer {
public:
	uint64_t mLastUHCHeadEatTimestamp; // the tick when the player last ate a head/golden head
	uint64_t mBucketCooldownTimestamp; // the tick when the player last placed a bucket of liquid
	bool mShouldCancelBucketPickup; // whether or not the player can pick up liquid with a bucket, used to fix MCPE-100598
	uint64_t mLastAttackedActorTimestamp; // the tick when the player last melee attacked an actor
	bool mHasResetSprint; // if true, player should administer bonus knockback to other players
	Vec3 mRawPos; // use this value for more accuracy of current pos (sometimes BDS pos zeroes out)
	Vec3 mRawPosOld; // use this value for more accuracy of pos from last tick
	int32_t mHealthOld; // heatlh value from the previous tick
	int32_t mAbsorptionOld; // absorption value from the previous tick
	uint64_t mLastSharpnessParticleInvokeTimestamp; // the tick when the player last invoked a sharpness particle on another actor
	uint64_t mLastWhisperMessagerXuid; // the xuid of the most recent player who sent this a whisper message

	EZPlayer() : mLastUHCHeadEatTimestamp(0), mBucketCooldownTimestamp(0), mShouldCancelBucketPickup(false),
		mLastAttackedActorTimestamp(0), mHasResetSprint(false), mRawPos(Vec3::ZERO), mRawPosOld(Vec3::ZERO),
		mHealthOld(0), mAbsorptionOld(0), mLastSharpnessParticleInvokeTimestamp(0), mLastWhisperMessagerXuid(0) {}
};