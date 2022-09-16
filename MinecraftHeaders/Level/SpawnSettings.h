#pragma once

#include <string>
#include <cstdint>

#include "DimensionID.h"

class SpawnSettings {
public:

	union Type {
		uint8_t mTypes[2];
		uint16_t mRaw = 0x0;
	};

	Type mType;
	std::string mUserDefinedBiomeName;
	DimensionID mDim; // AutomaticID<Dimension, int32_t>
};

static_assert(sizeof(SpawnSettings) == 0x30);