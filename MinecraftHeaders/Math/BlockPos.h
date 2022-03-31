#pragma once

#include "Vec3.h"
#include "../dll.h"

#include <limits>

class BlockPos {
public:
	int32_t x = 0, y = 0, z = 0;
	// For ABI

	static const BlockPos MIN;
	static const BlockPos MAX;
	static const BlockPos ZERO;

	BlockPos() {}
	BlockPos(int32_t x, int32_t y, int32_t z) : x(x), y(y), z(z) {}
	BlockPos(BlockPos const& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}
	MCAPI BlockPos(Vec3 const&);
	inline ~BlockPos() {}

	BlockPos operator+(BlockPos const &rhs) const {
		return BlockPos(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
	}
	BlockPos operator-(BlockPos const &rhs) const {
		return BlockPos(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
	}
	BlockPos operator*(float factor) const {
		return BlockPos(this->x * factor, this->y * factor, this->z * factor);
	}
	BlockPos operator/(float factor) const {
		return BlockPos(this->x / factor, this->y / factor, this->z / factor);
	}
	BlockPos& operator=(BlockPos const &rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
		this->z = rhs.z;
		return *this;
	}
	BlockPos& operator+=(float factor) {
		this->x += factor;
		this->y += factor;
		this->z += factor;
		return *this;
	}
	BlockPos& operator-=(float factor) {
		this->x -= factor;
		this->y -= factor;
		this->z -= factor;
		return *this;
	}
	BlockPos& operator*=(float factor) {
		this->x *= factor;
		this->y *= factor;
		this->z *= factor;
		return *this;
	}
	BlockPos& operator/=(float factor) {
		this->x /= factor;
		this->y /= factor;
		this->z /= factor;
		return *this;
	}

	bool operator==(BlockPos const &rhs) const { return (this->x == rhs.x) && (this->y == rhs.y) && (this->z == rhs.z); }
	bool operator!=(BlockPos const &rhs) const { return !(*this == rhs); }
	operator Vec3() { return {(float)x, (float)y, (float)z}; }
};

inline const BlockPos BlockPos::MIN = {std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::min()};
inline const BlockPos BlockPos::MAX = {std::numeric_limits<int32_t>::max(), std::numeric_limits<int32_t>::max(), std::numeric_limits<int32_t>::max()};
inline const BlockPos BlockPos::ZERO = {0, 0, 0};