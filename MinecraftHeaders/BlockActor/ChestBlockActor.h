#pragma once

#include "../dll.h"
#include "../Container/RandomizableBlockActorFillingContainer.h"
#include "../Math/BlockPos.h"
#include "../Math/Vec3.h"
#include "../Actor/ActorUniqueID.h"
#include "../Level/Level.h"

#include <functional>
#include <set>
#include <modutils.h>

class ChestBlockActor : public RandomizableBlockActorFillingContainer {
public:

	enum class Flags {
		mPairLead = 1,
		mPairingChanged = 2,
		mAlongX = 3,
		mDeferredPairLoad = 4,
		mConverted = 5
	};

	BUILD_ACCESS_MUT(float, mSpeed, 0x1F8);
	BUILD_ACCESS_MUT(bool, mIsGlobalChest, 0x1FC);
	BUILD_ACCESS_MUT(bool, mUsesLegacyBlockDetection, 0x1FD);
	BUILD_ACCESS_MUT(float, mObstructionHeight, 0x200);
	BUILD_ACCESS_MUT(float, mOpenness, 0x204);
	BUILD_ACCESS_MUT(float, mOldOpenness, 0x208);
	BUILD_ACCESS_MUT(bool, mIsOpen, 0x20C);
	BUILD_ACCESS_MUT(int32_t, mTickInterval, 0x210);
	BUILD_ACCESS_MUT(uint32_t, mFlags, 0x214); // bit flags - use ChestBlockActor::hasBitFlag(enum ChestBlockActor::Flags)
	BUILD_ACCESS_MUT(int32_t, mDeferredPairX, 0x218);
	BUILD_ACCESS_MUT(int32_t, mDeferredPairZ, 0x21C);
	BUILD_ACCESS_MUT(class ChestBlockActor *, mLargeChestPaired, 0x220);
	BUILD_ACCESS_MUT(class BlockPos, mLargeChestPairedPosition, 0x228);
	BUILD_ACCESS_MUT(bool, mIsTrappedChest, 0x234);
	BUILD_ACCESS_MUT(bool, mIsFindable, 0x235);
	BUILD_ACCESS_MUT(std::unordered_set<struct ActorUniqueID>, mOpenedByIds, 0x238);
	BUILD_ACCESS_MUT(bool, mNotifyPlayersOnChange, 0x278);

	MCAPI ChestBlockActor(enum BlockActorType type, std::string const& id, enum BlockActorRendererId renderId, class BlockPos const& pos, bool isTrapped);
	virtual ~ChestBlockActor();

	MCAPI void _closeChest(class BlockSource &region, class Player *player);
	MCAPI bool _detectBlockObstruction(class BlockSource &region);
	MCAPI bool _saveClientSideState(class CompoundTag &tag);
	MCAPI void _unpair(void);
	MCAPI bool canPairWith(class BlockActor *actor, class BlockSource &region);
	MCAPI void forceCloseChest(class BlockSource &region);
	MCAPI void pairWith(class ChestBlockActor *chest, bool isLeadingChest);
	MCAPI void unpair(class BlockSource &region);

	inline bool hasBitFlag(enum ChestBlockActor::Flags flag) {
		return this->mFlags & (uint32_t)flag;
	}
};