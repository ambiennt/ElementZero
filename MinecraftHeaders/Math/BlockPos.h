#pragma once

#include "Vec3.h"
#include <hook.h>

#include <limits>

class BlockPos {
public:
	int x = 0, y = 0, z = 0;
	// For ABI

	static BlockPos MIN;
	static BlockPos MAX;
	static BlockPos ZERO;

	BlockPos();
	BlockPos(int32_t x, int32_t y, int32_t z) : x(x), y(y), z(z) {}
	//BlockPos(const Vec3& vec) : x((int)(std::floorf(vec.x))), y((int)(std::floorf(vec.y))), z((int)(std::floorf(vec.z))) {}
	BlockPos(const Vec3& vec) {
		BlockPos result;
		CallServerClassMethod<void*>("??0BlockPos@@QEAA@AEBVVec3@@@Z", &result, vec);
		this->x = result.x;
		this->y = result.y;
		this->z = result.z;
	}
	BlockPos(const BlockPos& rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
		this->z = rhs.z;
	}
	inline ~BlockPos() {}
	BlockPos operator+(BlockPos const &rhs) const noexcept { return {x + rhs.x, y + rhs.y, z + rhs.z}; }
	constexpr bool operator==(BlockPos const &rhs) const noexcept { return x == rhs.x && y == rhs.y && z == rhs.z; }
	constexpr bool operator!=(BlockPos const &rhs) const noexcept { return !(*this == rhs); }
	operator Vec3() { return {(float) x, (float) y, (float) z}; }
};

inline BlockPos BlockPos::MIN = {
		std::numeric_limits<int>::min(), std::numeric_limits<int>::min(), std::numeric_limits<int>::min()};
inline BlockPos BlockPos::MAX = {
		std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), std::numeric_limits<int>::max()};
inline BlockPos BlockPos::ZERO = {0, 0, 0};