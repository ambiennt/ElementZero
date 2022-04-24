#pragma once

#include "../Math/BlockPos.h"

class BlockVolume {
public:
	void* mBlocks[2]; // buffer_span_mut<Block const *>
	uint32_t mWidth, mHeight, mDepth;

	struct BlockVolumeIter {
		BlockPos mPos; // Pos
		BlockPos mDims;
		void* mBlockIter; // buffer_span_mut<Block const *>::iterator
	};
};

static_assert(sizeof(BlockVolume) == 0x20);
static_assert(sizeof(BlockVolume::BlockVolumeIter) == 0x20);