#pragma once

#include "../Math/BlockPos.h"
#include "../BlockActor/Hopper.h"

class HopperComponent : public Hopper {
public:
	BlockPos mLastPosition;
};

static_assert(sizeof(HopperComponent) == 0x18);