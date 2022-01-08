#pragma once

class Vec2 {
public:
	float x = 0.0f, y = 0.0f;
	// For ABI

	static Vec2 ZERO;

	Vec2();
	Vec2(float x, float y) : x(x), y(y) {}
	inline ~Vec2() {}
	Vec2 &operator=(Vec2 const&) = default;
	Vec2 operator+(Vec2 const &rhs) const noexcept { return {x + rhs.x, y + rhs.y}; }
	constexpr bool operator==(Vec2 const &rhs) const noexcept { return x == rhs.x && y == rhs.y; }
	constexpr bool operator!=(Vec2 const &rhs) const noexcept { return !(*this == rhs); }
};

inline Vec2 Vec2::ZERO = {0.0f, 0.0f};