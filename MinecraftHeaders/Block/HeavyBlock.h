#pragma once

#include "BlockLegacy.h"
#include "../dll.h"
#include <cstdint>
#include <string>

class Block;
class BlockPos;
class BlockSource;
class Random;
class Color;

class HeavyBlock : public BlockLegacy {
	void _scheduleCheck(BlockSource &, const BlockPos &, const Block &, int32_t);
	BlockPos _findBottomSlidingBlock(BlockSource &, const BlockPos &);
	void _tickBlocksAround2D(BlockSource &region, const BlockPos &pos, const Block &oldBlock);
public:

	virtual Color getDustColor(const Block &) const; // pure
	virtual std::string getDustParticleName(const Block &) const; // pure
	virtual bool falling() const;
	virtual void onLand(BlockSource &, const BlockPos &) const;
	virtual bool isFreeToFall(BlockSource &, const BlockPos &) const;
protected:
	virtual void startFalling(BlockSource &, const BlockPos &, const Block &, bool) const;

	void checkSlide(BlockSource &, const BlockPos &) const;
};