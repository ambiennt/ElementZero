#pragma once

#include <cstdint>

enum class CommandOutputType : int32_t {
	Unknown    = 0, // None
	OnlyResult = 1, // LastOutput
	NoFeedback = 2, // Silent
	Normal     = 3, // AllOutput
	WithJson   = 4, // DataSet
};