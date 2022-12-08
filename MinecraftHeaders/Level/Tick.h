#pragma once

#include "../dll.h"
#include <cstdint>

struct Tick {
	uint64_t value{};

	MCAPI static const Tick MAX;
};