#pragma once

#include "Actor.h"
#include "../Math/BlockPos.h"
#include <modutils.h>

class FishingHook : public Actor {
public:
	BUILD_ACCESS_MUT(const float, SHOOT_SPEED, 0x620);
	BUILD_ACCESS_MUT(const float, SHOOT_POWER, 0x624);
	BUILD_ACCESS_MUT(const int32_t, NUM_PERCENTAGE_STEPS, 0x628);
	BUILD_ACCESS_MUT(bool, mInGround, 0x62C);
	BUILD_ACCESS_MUT(class BlockPos, mBlockPos, 0x630);
	BUILD_ACCESS_MUT(float, mFishAngle, 0x63C);
	BUILD_ACCESS_MUT(int32_t, mLife, 0x640);
	BUILD_ACCESS_MUT(int32_t, mFlightTime, 0x644);
	BUILD_ACCESS_MUT(int32_t, mTimeUntilHooked, 0x648);
	BUILD_ACCESS_MUT(int32_t, mTimeUntilLured, 0x64C);
	BUILD_ACCESS_MUT(int32_t, mTimeUntilNibble, 0x650);
	BUILD_ACCESS_MUT(int32_t, mFishingSpeed, 0x654);
	BUILD_ACCESS_MUT(int32_t, mLerpSteps, 0x658);
	BUILD_ACCESS_MUT(int32_t, mLerpPos, 0x65C);
	BUILD_ACCESS_MUT(float, mLerpRotX, 0x668);
	BUILD_ACCESS_MUT(float, mLerpRotY, 0x66C);
	BUILD_ACCESS_MUT(float, mBobTimer, 0x670);
};