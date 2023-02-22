#pragma once

#include <cstdint>

enum class GameType : int32_t {
	Undefined      = -1,
	Survival       = 0,
	Creative       = 1,
	Adventure      = 2,
	SurvivalViewer = 3,
	CreativeViewer = 4,
	Default        = 5,
	WorldDefault   = 5,
};