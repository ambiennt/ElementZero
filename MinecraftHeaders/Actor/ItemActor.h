#pragma once

#include "../Item/ItemStack.h"
#include "Actor.h"
#include <modutils.h>

class ItemActor : public Actor {
public:
	BUILD_ACCESS_MUT(class ItemStack, mItem, 0x620);
	BUILD_ACCESS_MUT(int32_t, mAge, 0x6B0);
	BUILD_ACCESS_MUT(int32_t, mPickupDelay, 0x6B4);
	BUILD_ACCESS_MUT(int32_t, mThrowTime, 0x6B8);
	BUILD_ACCESS_MUT(float, mBobOffs, 0x6BC);
	BUILD_ACCESS_MUT(int32_t, mHealth, 0x6C0);
	BUILD_ACCESS_MUT(int32_t, mLifeTime, 0x6C4);
	BUILD_ACCESS_MUT(bool, mIsInItemFrame, 0x6C8);
	BUILD_ACCESS_MUT(bool, mIsFromFishing, 0x6C9);
};