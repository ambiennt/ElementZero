#pragma once

#include "Vec2.h"
#include <cmath>

#define PI 3.141592654
#define RAD 0.017453292

class Vec3 {
public:
	float x = 0.0f, y = 0.0f, z = 0.0f;
	// For ABI

	static Vec3 ZERO;

	Vec3();
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
	inline ~Vec3() {}
	Vec3 &operator=(Vec3 const&) = default;
	Vec3 operator+(Vec3 const &rhs) const noexcept { return {x + rhs.x, y + rhs.y, z + rhs.z}; }
	constexpr bool operator==(Vec3 const &rhs) const noexcept { return x == rhs.x && y == rhs.y && z == rhs.z; }
	constexpr bool operator!=(Vec3 const &rhs) const noexcept { return !(*this == rhs); }

	inline Vec3 directionFromRotation(Vec2 const& rot) {

		float x = (float)(rot.x * -RAD);
		float y = (float)(rot.y * -RAD) - PI;

		float f1 = cos(y);
		float f2 = sin(y);
		float f3 = cos(x);
		float f4 = sin(x);

		Vec3 result;
		result.x = f3 * f2;
		result.y = f4;
		result.z = f3 * f1;
		return result;
	};
};

inline Vec3 Vec3::ZERO = {0.0f, 0.0f, 0.0f};