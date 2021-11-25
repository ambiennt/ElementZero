#pragma once

#include <modutils.h>
#include "Actor.h"
#include "../Core/NBT.h"

#include <memory.h>

class FallingBlock : public Actor {
public:

	enum class State { Falling, WaitRemoval };

	BUILD_ACCESS_MUT(bool, mCreative, 0x620);
	BUILD_ACCESS_MUT(enum State, mState, 0x624);
	BUILD_ACCESS_MUT(int32_t, mWaitTicks, 0x628);
	BUILD_ACCESS_MUT(int32_t, mTime, 0x62C);
	BUILD_ACCESS_MUT(bool, mCancelDrop, 0x630);
	BUILD_ACCESS_MUT(bool, mHurtEntities, 0x631);
	BUILD_ACCESS_MUT(int32_t, mFallDamageMax, 0x634);
	BUILD_ACCESS_MUT(int32_t, mFallDamageAmount, 0x638);
	BUILD_ACCESS_MUT(std::unique_ptr<class CompoundTag>, mFallingBlockSerId, 0x640);
	BUILD_ACCESS_MUT(class NewBlockID, mFallingBlockId, 0x648);
	BUILD_ACCESS_MUT(uint16_t, mFallingBlockData, 0x64A);
};

