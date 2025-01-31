#pragma once

#include "Vec3.h"
#include "../dll.h"

#include <cstdint>
#include <limits>

class BlockPos {
public:
	int32_t x, y, z;

	static const BlockPos MIN, MAX, ZERO;

	BlockPos() : x(0), y(0), z(0) {}
	BlockPos(int32_t x, int32_t y, int32_t z) : x(x), y(y), z(z) {}
	BlockPos(const BlockPos &rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}
	BlockPos(const Vec3 &rhs) :
		x(static_cast<int32_t>(std::floorf(rhs.x))),
		y(static_cast<int32_t>(std::floorf(rhs.y))),
		z(static_cast<int32_t>(std::floorf(rhs.z))) {}

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

	inline bool operator==(BlockPos const &rhs) const { return (this->x == rhs.x) && (this->y == rhs.y) && (this->z == rhs.z); }
	inline bool operator!=(BlockPos const &rhs) const { return !(*this == rhs); }
	inline operator Vec3() { return Vec3((float)x, (float)y, (float)z); }
};

inline const BlockPos BlockPos::MIN = {(std::numeric_limits<int32_t>::min)(), (std::numeric_limits<int32_t>::min)(), (std::numeric_limits<int32_t>::min)()};
inline const BlockPos BlockPos::MAX = {(std::numeric_limits<int32_t>::max)(), (std::numeric_limits<int32_t>::max)(), (std::numeric_limits<int32_t>::max)()};
inline const BlockPos BlockPos::ZERO = {0, 0, 0};