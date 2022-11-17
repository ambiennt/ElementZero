#pragma once

#include <cstdint>

enum class GeneratorType : int32_t {
	Legacy           = 0,
	Overworld        = 1,
	Flat             = 2,
	Nether           = 3,
	TheEnd           = 4,
	Undefined        = 5,
};