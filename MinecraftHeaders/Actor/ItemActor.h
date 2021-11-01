#pragma once

#include <modutils.h>
#include "Actor.h"

class ItemActor : public Actor {
public:
    BUILD_ACCESS_MUT(class ItemStack, mItem, 0x620);
    BUILD_ACCESS_MUT(int, mAge, 0x6B0);
    BUILD_ACCESS_MUT(int, mPickupDelay, 0x6B4);
    BUILD_ACCESS_MUT(int, mThrowTime, 0x6B8);
    BUILD_ACCESS_MUT(float, mBobOffs, 0x6BC);
    BUILD_ACCESS_MUT(int, mHealth, 0x6C0);
    BUILD_ACCESS_MUT(int, mLifeTime, 0x6C4);
    BUILD_ACCESS_MUT(bool, mIsInItemFrame, 0x6C8);
    BUILD_ACCESS_MUT(bool, mIsFromFishing, 0x6C9);
};