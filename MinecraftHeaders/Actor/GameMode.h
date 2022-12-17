#pragma once

#include "Player.h"
#include "../Math/BlockPos.h"
#include "../Math/Vec3.h"

#include "../dll.h"
#include <chrono>
#include <functional>

class ItemStack;

class GameMode {
	MCAPI bool _canDestroy(const BlockPos &, uint8_t);
	MCAPI bool _creativeDestroyBlock(const BlockPos &, uint8_t);
public:

	Player* mPlayer; // 0x8
	BlockPos mDestroyBlockPos; // 0x10
	float mOldDestroyProgress; // 0x1C
	float mDestroyProgress; // 0x20
	long double mLastDestroyTime; // 0x28
	float mDistanceTraveled; // 0x30
	Vec3 mPlayerLastPosition; // 0x34
	BlockPos mLastBuiltBlockPosition; // 0x40
	bool mLastBuildBlockWasInteractive; // 0x4C
	bool mLastBuildBlockWasSnappable; // 0x4D
	float mMinPlayerSpeed; // 0x50
	std::chrono::nanoseconds mLastBuildTime; // 0x58
	std::chrono::nanoseconds mNoDestroyUntil; // 0x60
	std::chrono::nanoseconds mNoDestroySoundUntil; // 0x68
	std::chrono::milliseconds mCreativeDestructionTickDelay; // 0x70
	std::chrono::milliseconds mBuildingTickDelay; // 0x78
	std::chrono::milliseconds mDestroySoundDelay; // 0x80
	bool mHasBuildDirection; // 0x88
	bool mHasLastBuiltPosition; // 0x89
	uint8_t mContinueFacing; // 0x8A
	BlockPos mBuildDirection; // 0x8C
	BlockPos mNextBuildPos; // 0x98
	
	virtual ~GameMode();
	virtual bool startDestroyBlock(const BlockPos& pos, uint8_t face, bool& hasDestroyedBlock); // hasDestroyedBlock is the return value
	virtual bool destroyBlock(const BlockPos& pos, uint8_t face);
	virtual bool continueDestroyBlock(const BlockPos& pos, uint8_t face, const Vec3&, bool& hasDestroyedBlock); // hasDestroyedBlock is the return value
	virtual void stopDestroyBlock(const BlockPos& pos);
	virtual void startBuildBlock(const BlockPos& pos, uint8_t face);
	virtual bool buildBlock(const BlockPos& pos, uint8_t face);
	virtual void continueBuildBlock(const BlockPos& pos, uint8_t face);
	virtual void stopBuildBlock();
	virtual void tick();
	virtual float getPickRange(InputMode const&, bool isVR);
	virtual bool useItem(ItemStack& item);
	virtual bool useItemOn(ItemStack& item, const BlockPos& at, uint8_t face, const Vec3& hitPoint, const Block* targetBlock);
	virtual bool interact(Actor& actor, const Vec3& hitPoint);
	virtual bool attack(Actor& actor);
	virtual void releaseUsingItem();
	virtual void setTrialMode(bool trialModeValue);
	virtual bool isInTrialMode();
	virtual void registerUpsellScreenCallback(std::function<void (bool)>);

	MCAPI bool baseUseItem(ItemStack &item);
};

static_assert(offsetof(GameMode, mDistanceTraveled) == 0x30);
static_assert(offsetof(GameMode, mMinPlayerSpeed) == 0x50);
static_assert(offsetof(GameMode, mNoDestroySoundUntil) == 0x68);
static_assert(offsetof(GameMode, mDestroySoundDelay) == 0x80);
static_assert(offsetof(GameMode, mNextBuildPos) == 0x98);
static_assert(sizeof(GameMode) == 0xA8);