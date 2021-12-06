#pragma once

#include "Vec3.h"
#include <hook.h>

#include <limits>

class BlockPos {
public:
	int x = 0, y = 0, z = 0;
	// For ABI
	inline ~BlockPos() {}

	static BlockPos MIN;
	static BlockPos MAX;
	static BlockPos ZERO;

	BlockPos operator+(BlockPos const &rhs) const noexcept { return {x + rhs.x, y + rhs.y, z + rhs.z}; }
	constexpr bool operator==(BlockPos const &rhs) const noexcept { return x == rhs.x && y == rhs.y && z == rhs.z; }
	constexpr bool operator!=(BlockPos const &rhs) const noexcept { return !(*this == rhs); }
	operator Vec3() { return {(float) x, (float) y, (float) z}; }

	inline BlockPos getBlockPos(const Vec3& currPos) {
    	BlockPos pos;
    	CallServerClassMethod<void>("??0BlockPos@@QEAA@AEBVVec3@@@Z", &pos, currPos);
    	return pos;
	}
};

inline BlockPos BlockPos::MIN = {
		std::numeric_limits<int>::min(), std::numeric_limits<int>::min(), std::numeric_limits<int>::min()};
inline BlockPos BlockPos::MAX = {
		std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), std::numeric_limits<int>::max()};
inline BlockPos BlockPos::ZERO = {0, 0, 0};