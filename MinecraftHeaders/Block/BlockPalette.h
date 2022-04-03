#pragma once

#include <string>
#include <mutex>
#include <set>

#include "../Core/NBT.h"
#include "../dll.h"

#include <mutex>

class Level;
class Block;
class BlockLegacy;

class BlockPalette {
	MCAPI bool shouldWarnFor(struct NewBlockID, unsigned short) const;
public:

	std::mutex mLegacyBlockStatesConversionWarningMutex; // 0x0
	std::set<std::pair<int32_t, int32_t>> mLegacyBlockStatesConversionWarningSet; // 0x50
	std::map<std::string, BlockLegacy const*> mNameLookup; // 0x60
	std::map<CompoundTag, Block const*> mBlockFromSerId; // 0x70
	std::vector<Block const*> mBlockFromRuntimeId; // 0x80
	Level* mLevel; // 0x98

	MCAPI void initFromBlockDefinitions(void);
	MCAPI class Block const &getBlock(unsigned int const &) const;
	MCAPI class Block const &getBlock(class CompoundTag const &) const;
	MCAPI class BlockLegacy const *getBlockLegacy(std::string const &) const;
	MCAPI class Block const &getBlockFromLegacyData(struct NewBlockID, unsigned int) const;
	MCAPI class Block const &switchBlock(class Block const &, class BlockLegacy const &) const;
};

static_assert(sizeof(BlockPalette) == 0xA0);