#pragma once

#include <cstdint>
#include <chrono>

class ActorTerrainInterlockData {
public:

	enum class VisibilityState : int8_t {
        InitialNotVisible            = 0x0,
        Visible_0                    = 0x1,
        DelayedDestructionNotVisible = 0x2,
	};

	VisibilityState mRenderVisibilityState;
	std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<int64_t, std::ratio<1, 1000000000>>> mCreationTime;
	bool mHasBeenDelayedDeleted;
};

static_assert(sizeof(ActorTerrainInterlockData) == 0x18);