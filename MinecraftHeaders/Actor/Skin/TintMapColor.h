#pragma once

#include "../../Core/Color.h"

#include <array>

class TintMapColor {
	std::array<Color, 4> mColors;
};

static_assert(sizeof(TintMapColor) == 0x40);