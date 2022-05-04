#pragma once

#include "BlockLegacy.h"
#include "../dll.h"

class OreBlock : public BlockLegacy {
public:
};

class RedstoneOreBlock : public BlockLegacy {
public:
	bool mLit; // 0x1060
};

static_assert(offsetof(RedstoneOreBlock, mLit) == 0x1060);