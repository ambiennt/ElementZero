#pragma once

#include "../dll.h"

struct Brightness {
	uint8_t value; // 0x0 - NewType<uint8_t>
};

struct BrightnessPair {
	Brightness mSky; // 0x0
	Brightness mBlock; // 0x1
};