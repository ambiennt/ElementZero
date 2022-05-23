#pragma once

#include "../dll.h"

class DirtyTicksCounter {
	int32_t mTotalTime; // 0x0
	int32_t mLastChange; // 0x4

	inline int32_t getTicksSinceLastChange() const {
		return this->mTotalTime - this->mLastChange;
	}
};