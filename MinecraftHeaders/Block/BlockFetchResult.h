#pragma once

#include <functional>
#include <cstdint>

#include "../Math/BlockPos.h"
#include "../dll.h"

class Block;

class BlockFetchResult {
public:
	std::reference_wrapper<Block const> mBlock; // 0x0
	BlockPos mBlockPos; // 0x8
	uint32_t mDistanceSquared; // 0x14
};

static_assert(sizeof(BlockFetchResult) == 0x18);