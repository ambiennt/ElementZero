#pragma once

#include <functional>
#include <vector>
#include <string>
#include <cstdint>

#include "../Math/Vec3.h"
#include "../Math/BlockPos.h"
#include "CommandPosition.h"
#include "InvertableFilter.h"
#include "../Actor/ActorDefinitionIdentifier.h"
#include "../dll.h"

class CommandOrigin;
class Actor;
struct ActorDefinitionIdentifier;

class CommandSelectorBase {
private:
	uint32_t version;                                                                     // 0
	uint32_t type;                                                                        // 4
	uint32_t order;                                                                       // 8
	std::vector<InvertableFilter<std::string>> namefilters;                               // 16
	std::vector<InvertableFilter<ActorDefinitionIdentifier>> typefilter2;                 // 40
	std::vector<InvertableFilter<std::string>> tagfilters;                                // 64
	std::vector<std::function<bool(CommandOrigin const &, Actor const &)>> customfilters; // 88
	CommandPosition position;                                                             // 112
	BlockPos box;                                                                         // 128
	float radiusMin;                                                                      // 140
	float radiusMax;                                                                      // 144 = 0x7f7fffff (float max)
	uint64_t resultCount;                                                                 // 152 = 0xFFFFFFFF
	bool includeDeadPlayers;                                                              // 160
	bool isPositionBound;                                                                 // 161
	bool distanceFiltered;                                                                // 162
	bool haveDeltas; // ?????                                                             // 163
	bool playerOnly;                                                                      // 164
	bool explicitIdSelector;                                                              // 165

public:
	inline bool isExplicitIdSelector() const { return this->explicitIdSelector; }
	inline void setExplicitIdSelector(bool value) { this->explicitIdSelector = value; }
	inline void addNameFilter(InvertableFilter<std::string> const &filter) { this->namefilters.emplace_back(filter); }
	inline void addTagFilter(InvertableFilter<std::string> const &filter) {
		if (isExplicitIdSelector()) { this->explicitIdSelector = false; }
		this->tagfilters.emplace_back(filter);
	}
	inline void setIncludeDeadPlayers(bool value) { this->includeDeadPlayers = value; }
	inline void setResultCount(uint64_t value) { this->resultCount = value; }

	MCAPI void addFilter(std::function<bool(CommandOrigin const &, Actor const &)>);
	MCAPI void addTypeFilter(InvertableFilter<std::string> const &);
	MCAPI CommandSelectorBase();
	MCAPI void setBox(BlockPos);
	MCAPI void setPosition(CommandPosition);
	MCAPI void setRadiusMin(float);
	MCAPI void setRadiusMax(float);
	MCAPI bool compile(CommandOrigin const &, std::string &);

protected:
	MCAPI CommandSelectorBase(bool isPlayer);
};

// static_assert(offsetof(CommandSelectorBase, explicitIdSelector) == 0xA5);