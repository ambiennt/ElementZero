#pragma once

#include <cstdint>

class Hopper {
public:
	int32_t mCooldownTime;
	bool mTransferredFromChestMinecart, mIsEntity;
	int32_t mMoveItemSpeed;
};