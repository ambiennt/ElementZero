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
	Vec3(const Vec3& rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
		this->z = rhs.z;
	}
	inline ~Vec3() {}
	Vec3 &operator=(Vec3 const&) = default;
	Vec3 operator+(Vec3 const &rhs) const noexcept { return { x + rhs.x, y + rhs.y, z + rhs.z }; }
	Vec3 operator-(Vec3 const &rhs) const noexcept { return { x - rhs.x, y - rhs.y, z - rhs.z }; }
	Vec3 operator*(float factor) const noexcept {
		return { x * factor, y * factor, z * factor };
	}
	Vec3 operator/(float factor) {
		if (factor == 0.f) return Vec3::ZERO;
		float inv = 1.f / factor;
		return { x * inv, y * inv, z * inv };
	}
	Vec3 &operator*=(float factor) {
		x *= factor;
		y *= factor;
		z *= factor;
		return *this;
	}

	constexpr bool operator==(Vec3 const &rhs) const noexcept { return x == rhs.x && y == rhs.y && z == rhs.z; }
	constexpr bool operator!=(Vec3 const &rhs) const noexcept { return !(*this == rhs); }

	inline void normalize(void) {
		float l  = 1.f / sqrt(x * x + y * y + z * z);
		x *= l;
		y *= l;
		z *= l;
	}

	inline void normalizeXZ(void) {
		float l  = 1.f / sqrt(x * x + z * z);
		x *= l;
		z *= l;
	}

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