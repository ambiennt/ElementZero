#pragma once

#include "BlockLegacy.h"
#include "../dll.h"

class LiquidBlock : public BlockLegacy {
public:

	inline bool isSourceBlock(class BlockSource &region, class BlockPos const &pos) {
		return getDepth(region, pos) == 0;
	}

protected:
	MCAPI int getDepth(class BlockSource &, class BlockPos const &) const;
};