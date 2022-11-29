#pragma once

#include <cstdint>

enum class Difficulty : int32_t {
	Peaceful  = 0,
	Easy      = 1,
	Normal    = 2,
	Hard      = 3,
	Count     = 4,
	Unknown   = 5,
};