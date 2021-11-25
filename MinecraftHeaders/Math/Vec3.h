#pragma once

class Vec3 {
public:
	float x = 0.0f, y = 0.0f, z = 0.0f;
	// For ABI
	inline ~Vec3() {}

	static Vec3 ZERO;

	Vec3 &operator=(Vec3 const&) = default;
	Vec3 operator+(Vec3 const &rhs) const noexcept { return {x + rhs.x, y + rhs.y, z + rhs.z}; }
	constexpr bool operator==(Vec3 const &rhs) const noexcept { return x == rhs.x && y == rhs.y && z == rhs.z; }
	constexpr bool operator!=(Vec3 const &rhs) const noexcept { return !(*this == rhs); }
};

inline Vec3 Vec3::ZERO = {0.0f, 0.0f, 0.0f};