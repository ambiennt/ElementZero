#pragma once

#include "Player.h"
#include "../dll.h"
#include "../Math/BlockPos.h"
#include "../Math/Vec3.h"
#include "modutils.h"

#include <chrono>

class GameMode {
public:

	BUILD_ACCESS_MUT(class Player*, mPlayer, 0x8);
	BUILD_ACCESS_MUT(class BlockPos, mDestroyBlockPos, 0x10);
	BUILD_ACCESS_MUT(float, mOldDestroyProgress, 0x1C);
	BUILD_ACCESS_MUT(float, mDestroyProgress, 0x20);
	BUILD_ACCESS_MUT(double, mLastDestroyTime, 0x28);
	BUILD_ACCESS_MUT(float, mDistanceTraveled, 0x30);
	BUILD_ACCESS_MUT(class Vec3, mPlayerLastPosition, 0x34);
	BUILD_ACCESS_MUT(class BlockPos, mLastBuiltBlockPosition, 0x40);
	BUILD_ACCESS_MUT(bool, mLastBuildBlockWasInteractive, 0x4C);
	BUILD_ACCESS_MUT(bool, mLastBuildBlockWasSnappable, 0x4D);
	BUILD_ACCESS_MUT(float, mMinPlayerSpeed, 0x50);

	using Timestamp1000000000 = std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<int64_t, std::ratio<1, 1000000000>>>;
	BUILD_ACCESS_MUT(Timestamp1000000000, mLastBuildTime, 0x58);
	BUILD_ACCESS_MUT(Timestamp1000000000, mNoDestroyUntil, 0x60);
	BUILD_ACCESS_MUT(Timestamp1000000000, mNoDestroySoundUntil, 0x68);

	using Timestamp1000 = std::chrono::duration<int64_t, std::ratio<1, 1000>>;
	BUILD_ACCESS_MUT(Timestamp1000, creativeDestructionTickDelay, 0x70);
	BUILD_ACCESS_MUT(Timestamp1000, buildingTickDelay, 0x78);
	BUILD_ACCESS_MUT(Timestamp1000, destroySoundDelay, 0x80);
	
	BUILD_ACCESS_MUT(bool, mHasBuildDirection, 0x88);
	BUILD_ACCESS_MUT(bool, mHasLastBuiltPosition, 0x89);
	BUILD_ACCESS_MUT(uint8_t, mContinueFacing, 0x8A);
	BUILD_ACCESS_MUT(class BlockPos, mBuildDirection, 0x8C);
	BUILD_ACCESS_MUT(class BlockPos, mNextBuildPos, 0x98);
	
	MCAPI virtual ~GameMode();
};