#pragma once

#include <cmath>

#define PI 3.14159265359
#define TAU 6.28318530718
#define INV_RADIAN_DEGREES 0.01745329251
#define RADIAN_DEGREES 57.2957795131

class Vec2 {
public:
	float x = 0.f, y = 0.f;
	// For ABI

	static const Vec2 ZERO;

	Vec2() {}
	Vec2(float x, float y) : x(x), y(y) {}
	Vec2(Vec2 const& rhs) : x(rhs.x), y(rhs.y) {}
	inline ~Vec2() {}

	Vec2 operator+(Vec2 const &rhs) const {
		return Vec2(this->x + rhs.x, this->y + rhs.y);
	}
	Vec2 operator-(Vec2 const &rhs) const {
		return Vec2(this->x - rhs.x, this->y - rhs.y);
	}
	Vec2 operator*(float factor) const {
		return Vec2(this->x * factor, this->y * factor);
	}
	Vec2 operator/(float factor) const {
		return Vec2(this->x / factor, this->y / factor);
	}
	Vec2& operator=(Vec2 const &rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
		return *this;
	}
	Vec2& operator+=(float factor) {
		this->x += factor;
		this->y += factor;
		return *this;
	}
	Vec2& operator-=(float factor) {
		this->x -= factor;
		this->y -= factor;
		return *this;
	}
	Vec2& operator*=(float factor) {
		this->x *= factor;
		this->y *= factor;
		return *this;
	}
	Vec2& operator/=(float factor) {
		this->x /= factor;
		this->y /= factor;
		return *this;
	}

	bool operator==(Vec2 const &rhs) const { return (this->x == rhs.x) && (this->y == rhs.y); }
	bool operator!=(Vec2 const &rhs) const { return !(*this == rhs); }

	inline float length(void) const {
		return std::sqrtf((this->x * this->x) + (this->y * this->y));
	}

	inline Vec2& normalize(void) {
		float l = this->length();
		if (l == 0.f) return *this;
		this->operator*=(1.f / l);
		return *this;
	}
};

inline const Vec2 Vec2::ZERO = {0.f, 0.f};