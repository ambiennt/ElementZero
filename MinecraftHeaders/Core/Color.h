#pragma once

#include <string>

#include "../dll.h"

class Color {
public:
	float r, g, b, a;

	inline Color() : r(0.f), g(0.f), b(0.f), a(0.f) {}
	inline Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
	inline Color(Color const &rhs) : r(rhs.r), g(rhs.g), b(rhs.b), a(rhs.a) {}

	bool operator==(Color const &rhs) const { return (this->r == rhs.r) && (this->g == rhs.g) && (this->b == rhs.b) && (this->a == rhs.a); }
	bool operator!=(Color const &rhs) const { return !(*this == rhs); }

	MCAPI static Color fromARGB(int);
	MCAPI static Color fromHexString(std::string const &);
	MCAPI int toARGB() const;
	MCAPI std::string toHexString() const;

	MCAPI static Color NIL, WHITE, PURPLE, YELLOW, RED, BLACK, MINECON_GOLD, SHADE_WEST_EAST,
		SHADE_NORTH_SOUTH, SHADE_UP, SHADE_DOWN, PINK, CYAN, ORANGE, BLUE, GREEN, GREY;
};