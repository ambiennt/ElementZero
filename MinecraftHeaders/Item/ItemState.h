#pragma once

#include <string>
#include <cstdint>
#include "../dll.h"

#include "../Core/NBT.h"

// const class ItemState
class ItemState {
public:

	struct StateListNode {
		StateListNode *mNext;
		StateListNode *mPrev;
		ItemState *mState;
	};

	// no vtable symbols :(	
	virtual ~ItemState();
	virtual void toNBT(CompoundTag *, int32_t);
	virtual int32_t fromNBT(const CompoundTag *);

	uint64_t mID; // const - 0x8
	uint64_t mVariationCount; // const - 0x10
	std::string mName; // const - 0x18
	ItemState::StateListNode mNode; // 0x38
};

static_assert(sizeof(ItemState) == 0x50);

struct ItemStateInstance {
	uint32_t mMaxBits; // const - 0x0
	uint32_t mStartBit; // 0x4
	uint32_t mNumBits; // 0x8
	uint32_t mVariationCount; // 0xC
	uint32_t mMask; // 0x10
	bool mInitialized; // 0x14
	ItemState *mState; // const - 0x18
};

static_assert(sizeof(ItemStateInstance) == 0x20);