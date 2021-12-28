#pragma once

#include "BlockLegacy.h"
#include "../dll.h"

#include <modutils.h>

class OreBlock : public BlockLegacy {
public:
};

class RedstoneOreBlock : public BlockLegacy {
public:
	BUILD_ACCESS_MUT(bool, mLit, 0x1060);
};