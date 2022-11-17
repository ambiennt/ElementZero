#pragma once

enum class DimensionID : int32_t { // this enum doesn't actually exist in bds but the automatic id stuff is bloat
	Overworld = 0,
	Nether    = 1,
	TheEnd    = 2,
	Undefined = 3,
};