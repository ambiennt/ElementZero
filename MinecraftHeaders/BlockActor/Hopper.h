#pragma once

#include "../Math/BlockPos.h"

class Hopper {
public:
	int mCooldownTime;
	bool mTransferredFromChestMinecart, mIsEntity;
	int mMoveItemSpeed;
};

class HopperComponent : public Hopper {
public:
	BlockPos mLastPosition;
};