#pragma once

#include "Actor.h"
#include "../Math/BlockPos.h"
#include <modutils.h>

class FishingHook : public Actor {
public:
	CLASS_FIELD(SHOOT_SPEED, 0x620, const float);
	CLASS_FIELD(SHOOT_POWER, 0x624, const float);
	CLASS_FIELD(NUM_PERCENTAGE_STEPS, 0x628, const int32_t);
	CLASS_FIELD(mInGround, 0x62C, bool);
	CLASS_FIELD(mBlockPos, 0x630, class BlockPos);
	CLASS_FIELD(mFishAngle, 0x63C, float);
	CLASS_FIELD(mLife, 0x640, int32_t);
	CLASS_FIELD(mFlightTime, 0x644, int32_t);
	CLASS_FIELD(mTimeUntilHooked, 0x648, int32_t);
	CLASS_FIELD(mTimeUntilLured, 0x64C, int32_t);
	CLASS_FIELD(mTimeUntilNibble, 0x650, int32_t);
	CLASS_FIELD(mFishingSpeed, 0x654, int32_t);
	CLASS_FIELD(mLerpSteps, 0x658, int32_t);
	CLASS_FIELD(mLerpPos, 0x65C, int32_t);
	CLASS_FIELD(mLerpRotX, 0x668, float);
	CLASS_FIELD(mLerpRotY, 0x66C, float);
	CLASS_FIELD(mBobTimer, 0x670, float);

};