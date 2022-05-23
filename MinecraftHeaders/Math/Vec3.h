#pragma once

#include "Vec2.h"
#include <cmath>

class Vec3 {
public:
	float x, y, z;

	static const Vec3 ZERO;

	Vec3() : x(0.f), y(0.f), z(0.f) {}
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
	Vec3(Vec3 const& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}
	inline ~Vec3() {}

	Vec3 operator+(Vec3 const &rhs) const {
		return Vec3(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
	}
	Vec3 operator-(Vec3 const &rhs) const {
		return Vec3(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
	}
	Vec3 operator*(float factor) const {
		return Vec3(this->x * factor, this->y * factor, this->z * factor);
	}
	Vec3 operator/(float factor) const {
		return Vec3(this->x / factor, this->y / factor, this->z / factor);
	}
	Vec3& operator=(Vec3 const& rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
		this->z = rhs.z;
		return *this;
	}
	Vec3& operator+=(float factor) {
		this->x += factor;
		this->y += factor;
		this->z += factor;
		return *this;
	}
	Vec3& operator-=(float factor) {
		this->x -= factor;
		this->y -= factor;
		this->z -= factor;
		return *this;
	}
	Vec3& operator*=(float factor) {
		this->x *= factor;
		this->y *= factor;
		this->z *= factor;
		return *this;
	}
	Vec3& operator/=(float factor) {
		this->x /= factor;
		this->y /= factor;
		this->z /= factor;
		return *this;
	}

	bool operator==(Vec3 const &rhs) const { return (this->x == rhs.x) && (this->y == rhs.y) && (this->z == rhs.z); }
	bool operator!=(Vec3 const &rhs) const { return !(*this == rhs); }

	inline float length() const {
		return std::sqrtf((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
	}

	inline Vec3& normalize() {
		float l = this->length();
		if (l <= 0.f) return *this;
		this->operator*=(1.f / l);
		return *this;
	}

	inline Vec3& normalizeXZ() {
		float l = this->length();
		if (l <= 0.f) return *this;
		l = 1.f / l;
		this->x *= l;
		this->z *= l;
		return *this;
	}

	static inline Vec3 directionFromRotation(Vec2 const& rot) {

		float x = (float)(rot.x * -INV_RADIAN_DEGREES);
		float y = (float)((rot.y * -INV_RADIAN_DEGREES) - PI);

		float f1 = std::cosf(y);
		float f2 = std::sinf(y);
		float f3 = std::cosf(x);
		float f4 = std::sinf(x);

		return Vec3(f3 * f2, f4, f3 * f1);
	};
};

inline const Vec3 Vec3::ZERO = {0.f, 0.f, 0.f};