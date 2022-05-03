#pragma once

#include "../Container/RandomizableBlockActorContainer.h"
#include "../Math/BlockPos.h"
#include "../Math/Vec3.h"
#include "../Actor/ActorUniqueID.h"
#include "../dll.h"

#include <functional>
#include <set>

class ChestBlockActor : public RandomizableBlockActorFillingContainer {
public:

	enum class Flags {
		mPairLead = 1,
		mPairingChanged = 2,
		mAlongX = 3,
		mDeferredPairLoad = 4,
		mConverted = 5
	};

	float mSpeed; // 0x1F8
	bool mIsGlobalChest; // 0x1FC
	bool mUsesLegacyBlockDetection; // 0x1FD
	float mObstructionHeight; // 0x200
	float mOpenness; // 0x204
	float mOldOpenness; // 0x208
	bool mIsOpen; // 0x20C
	int32_t mTickInterval; // 0x210
	uint32_t mFlags; // 0x214 // bit flags for enum ChestBlockActor::Flags
	int32_t mDeferredPairX; // 0x218
	int32_t mDeferredPairZ; // 0x21C
	ChestBlockActor * mLargeChestPaired; // 0x220
	BlockPos mLargeChestPairedPosition; // 0x228
	bool mIsTrappedChest; // 0x234
	bool mIsFindable; // 0x235
	std::unordered_set<ActorUniqueID> mOpenedByIds; // 0x238
	bool mNotifyPlayersOnChange; // 0x278

	MCAPI ChestBlockActor(BlockActorType type, std::string const& id, BlockActorRendererId renderId, BlockPos const& pos, bool isTrapped);

	MCAPI void _closeChest(BlockSource &region, Player *player);
	MCAPI bool _detectBlockObstruction(BlockSource &region);
	MCAPI bool _saveClientSideState(CompoundTag &tag);
	MCAPI void _unpair();
	MCAPI bool canPairWith(BlockActor *actor, BlockSource &region);
	MCAPI void forceCloseChest(BlockSource &region);
	MCAPI void pairWith(ChestBlockActor *chest, bool isLeadingChest);
	MCAPI void unpair(BlockSource &region);

	inline bool hasBitFlag(ChestBlockActor::Flags flag) {
		return this->mFlags & (uint32_t)flag;
	}
};