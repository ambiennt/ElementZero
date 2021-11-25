#pragma once

enum class CommandOutputType {
	Unknown    = 0, // None
	OnlyResult = 1, // LastOutput
	NoFeedback = 2, // Silent
	Normal     = 3, // AllOutput
	WithJson   = 4, // DataSet
};