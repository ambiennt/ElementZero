#pragma once

#include <string>

#include "../dll.h"
#include <modutils.h>
#include <mutex>

class BlockPalette {
public:

	char pad[0xA0];
	
	BUILD_ACCESS_MUT(std::mutex, mLegacyBlockStatesConversionWarningMutex, 0x0);

	using conversionWarningSet = std::set<std::pair<int,int>>;
	BUILD_ACCESS_MUT(conversionWarningSet, mLegacyBlockStatesConversionWarningSet, 0x50);

	using nameLookupMap = std::map<std::string, class BlockLegacy const*>;
	BUILD_ACCESS_MUT(nameLookupMap, mNameLookup, 0x60);

	using compoundTagBlockMap = std::map<class CompoundTag, class Block const*>;
	BUILD_ACCESS_MUT(compoundTagBlockMap, mBlockFromSerId, 0x70);

	BUILD_ACCESS_MUT(std::vector<class Block const*>, mBlockFromRuntimeId, 0x80);
	BUILD_ACCESS_MUT(class Level*, mLevel, 0x98);

	MCAPI void initFromBlockDefinitions(void);
	MCAPI class Block const &getBlock(unsigned int const &) const;
	MCAPI class Block const &getBlock(class CompoundTag const &) const;
	MCAPI class BlockLegacy const *getBlockLegacy(std::string const &) const;
	MCAPI class Block const &getBlockFromLegacyData(struct NewBlockID, unsigned int) const;
	MCAPI class Block const &switchBlock(class Block const &, class BlockLegacy const &) const;

private:
	MCAPI bool shouldWarnFor(struct NewBlockID, unsigned short) const;
};

static_assert(sizeof(BlockPalette) == 0xA0);