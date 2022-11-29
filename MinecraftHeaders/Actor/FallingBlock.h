#pragma once

#include <modutils.h>
#include "Actor.h"
#include "../Core/NBT.h"
#include "../dll.h"
#include <memory.h>

class FallingBlock : public Actor {
public:

	enum class State {
		Falling = 0,
		WaitRemoval = 1
	};

	CLASS_FIELD(mCreative, 0x620, bool);
	CLASS_FIELD(mState, 0x624, enum State);
	CLASS_FIELD(mWaitTicks, 0x628, int32_t);
	CLASS_FIELD(mTime, 0x62C, int32_t);
	CLASS_FIELD(mCancelDrop, 0x630, bool);
	CLASS_FIELD(mHurtEntities, 0x631, bool);
	CLASS_FIELD(mFallDamageMax, 0x634, int32_t);
	CLASS_FIELD(mFallDamageAmount, 0x638, int32_t);
	CLASS_FIELD(mFallingBlockSerId, 0x640, std::unique_ptr<class CompoundTag>);
	CLASS_FIELD(mFallingBlockId, 0x648, uint16_t); // class NewBlockID
	CLASS_FIELD(mFallingBlockAux, 0x64A, uint16_t); // mFallingBlockData
};