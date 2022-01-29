#pragma once

#include <cmath>

class Vec2 {
public:
	float x = 0.0f, y = 0.0f;
	// For ABI

	static Vec2 ZERO;

	Vec2();
	Vec2(float x, float y) : x(x), y(y) {}
	Vec2(const Vec2& rhs) {
		this->x = rhs.x;
		this->y = rhs.y;
	}
	inline ~Vec2() {}
	Vec2 &operator=(Vec2 const&) = default;
	Vec2 operator+(Vec2 const &rhs) const noexcept { return {x + rhs.x, y + rhs.y}; }
	Vec2 operator*(float factor) const noexcept {
		return { x * factor, y * factor };
	}
	Vec2 operator/(float factor) const noexcept {
		if (factor == 0.f) return Vec2::ZERO;
		float inv = 1.f / factor;
		return { x * inv, y * inv };
	}
	Vec2 &operator*=(float factor) {
		x *= factor;
		y *= factor;
		return *this;
	}

	constexpr bool operator==(Vec2 const &rhs) const noexcept { return x == rhs.x && y == rhs.y; }
	constexpr bool operator!=(Vec2 const &rhs) const noexcept { return !(*this == rhs); }

	inline void normalize(void) {
		float l  = 1.f / sqrt(x * x + y * y);
		x *= l;
		y *= l;
	}
};

inline Vec2 Vec2::ZERO = {0.0f, 0.0f};