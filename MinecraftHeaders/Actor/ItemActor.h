#pragma once

#include "../Item/ItemStack.h"
#include "Actor.h"
#include <modutils.h>

class ItemActor : public Actor {
public:
	CLASS_FIELD(mItem, 0x620, class ItemStack);
	CLASS_FIELD(mAge, 0x6B0, int32_t);
	CLASS_FIELD(mPickupDelay, 0x6B4, int32_t);
	CLASS_FIELD(mThrowTime, 0x6B8, int32_t);
	CLASS_FIELD(mBobOffs, 0x6BC, float);
	CLASS_FIELD(mHealth, 0x6C0, int32_t);
	CLASS_FIELD(mLifeTime, 0x6C4, int32_t);
	CLASS_FIELD(mIsInItemFrame, 0x6C8, bool);
	CLASS_FIELD(mIsFromFishing, 0x6C9, bool);
};