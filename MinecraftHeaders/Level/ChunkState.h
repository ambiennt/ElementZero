#pragma once

#include "../dll.h"

enum class ChunkState : int8_t {
	Unloaded                    = 0,
	Generating                  = 1,
	Generated                   = 2,
	PostProcessing              = 3,
	PostProcessed               = 4,
	CheckingForReplacementData  = 5,
	NeedsLighting               = 6,
	Lighting                    = 7,
	LightingFinished            = 8,
	Loaded                      = 9
};