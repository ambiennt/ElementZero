#pragma once

#include "../Actor/Actor.h"
#include "../Actor/ActorUniqueID.h"
#include "../Actor/ActorType.h"
#include "../Actor/HitResult.h"
#include "../Math/BlockPos.h"
#include "../Math/Vec3.h"
#include "../Level/Level.h"

#include "../dll.h"
#include "modutils.h"
#include <vector>

enum class ProjectileAnchor {
	Origin    = 0,
	EyeHeight = 1,
	Middle    = 2,
	Count     = 3
};

class ProjectileComponent {
public:

	enum class EAxis : int8_t;

	BUILD_ACCESS_MUT(bool, mWasOnGround, 0x0);
	BUILD_ACCESS_MUT(bool, mNoPhysics, 0x1);
	BUILD_ACCESS_MUT(struct ActorUniqueID, mOwnerId, 0x8);
	BUILD_ACCESS_MUT(class Vec3, mThrownPos, 0x10);
	BUILD_ACCESS_MUT(class Vec3, mApexPos, 0x1C);
	BUILD_ACCESS_MUT(bool, mFoundApex, 0x28);
	BUILD_ACCESS_MUT(int32_t, mLife, 0x2C);
	BUILD_ACCESS_MUT(int32_t, mFlightTIme, 0x30);
	BUILD_ACCESS_MUT(int32_t, mGroundTime, 0x34);
	BUILD_ACCESS_MUT(int32_t, mShakeTime, 0x38);
	BUILD_ACCESS_MUT(class BlockPos, mBlock, 0x3C);
	BUILD_ACCESS_MUT(class BlockPos, mStuckToBlockPos, 0x48);
	BUILD_ACCESS_MUT(class Vec3, mCollisionPos, 0x54);
	BUILD_ACCESS_MUT(int32_t, mEnchantPower, 0x60);
	BUILD_ACCESS_MUT(int32_t, mEnchantImpaler, 0x64);
	BUILD_ACCESS_MUT(class HitResult, mHitResult, 0x68);
	BUILD_ACCESS_MUT(uint8_t, mHitFacing, 0xC8);
	BUILD_ACCESS_MUT(bool, mReflect, 0xC9);
	BUILD_ACCESS_MUT(float, mPower, 0xCC);
	BUILD_ACCESS_MUT(float, mDamage, 0xD0);
	BUILD_ACCESS_MUT(class Vec3, mOffset, 0xD4);
	BUILD_ACCESS_MUT(enum ParticleType, mHitParticle, 0xE0);
	BUILD_ACCESS_MUT(float, mGravity, 0xE4);
	BUILD_ACCESS_MUT(float, mUpwardsAngleOffset, 0xE8);
	BUILD_ACCESS_MUT(std::vector<class OnHitSubcomponent *>, mOnHitCommands, 0xF0);
	BUILD_ACCESS_MUT(class DefinitionTrigger, mOnHitEvent, 0x108);
	BUILD_ACCESS_MUT(float, mUncertaintyBase, 0x188);
	BUILD_ACCESS_MUT(float, mUncertaintyMultiplier, 0x18C);
	BUILD_ACCESS_MUT(enum ActorType, mFilterType, 0x190);
	BUILD_ACCESS_MUT(float, mOnFireTime, 0x194);
	BUILD_ACCESS_MUT(int32_t, mPotionEffect, 0x198); // effect id
	BUILD_ACCESS_MUT(float, mSplashRange, 0x19C);
	BUILD_ACCESS_MUT(bool, mKnockback, 0x1A0);
	BUILD_ACCESS_MUT(float, mKnockbackForce, 0x1A4);
	BUILD_ACCESS_MUT(bool, mCatchFire, 0x1A8);
	BUILD_ACCESS_MUT(bool, mChanneling, 0x1A9);
	BUILD_ACCESS_MUT(bool, mIsSplash, 0x1AA);
	BUILD_ACCESS_MUT(float, mInertiaMod, 0x1AC);
	BUILD_ACCESS_MUT(float, mLiquidInertia, 0x1B0);
	BUILD_ACCESS_MUT(bool, mSemiRandomDiffDamage, 0x1B4);
	BUILD_ACCESS_MUT(enum ProjectileAnchor, mSpawnPosAnchor, 0x1B8); // TODO
	BUILD_ACCESS_MUT(enum LevelSoundEvent, mHitEntitySound, 0x1BC);
	BUILD_ACCESS_MUT(enum LevelSoundEvent, mHitGroundSound, 0x1C0);
	BUILD_ACCESS_MUT(enum LevelSoundEvent, mShootSound, 0x1C4);
	BUILD_ACCESS_MUT(bool, mIsDangerous, 0x1C8);
	BUILD_ACCESS_MUT(bool, mShootTarget, 0x1C9);
	BUILD_ACCESS_MUT(bool, mDamageOwner, 0x1CA);
	BUILD_ACCESS_MUT(bool, mReflectOnHurt, 0x1CB);
	BUILD_ACCESS_MUT(bool, mDestroyOnHurt, 0x1CC);
	BUILD_ACCESS_MUT(bool, mStopOnHit, 0x1CD);
	BUILD_ACCESS_MUT(bool, mCritParticleOnHurt, 0x1CE);
	BUILD_ACCESS_MUT(bool, mHitWater, 0x1CF);
	BUILD_ACCESS_MUT(bool, mHitActor, 0x1D0);
	BUILD_ACCESS_MUT(bool, mMultipleHits, 0x1D1);
	BUILD_ACCESS_MUT(int32_t, mPiercingEnchantLevel, 0x1D4);
	BUILD_ACCESS_MUT(int32_t, mActorHitCount, 0x1D8);
	BUILD_ACCESS_MUT(bool, mIsHoming, 0x1DC);
	BUILD_ACCESS_MUT(struct ActorUniqueID, mPendingTargetID, 0x1E0);
	BUILD_ACCESS_MUT(class Actor*, mTarget, 0x1E8);
	BUILD_ACCESS_MUT(struct ActorUniqueID, mTargetID, 0x1F0);
	BUILD_ACCESS_MUT(class Vec3, mTargetDelta, 0x1F8);
	BUILD_ACCESS_MUT(int32_t, mFlightSteps, 0x204);

	using int8Arr4 = int8_t[4];
	BUILD_ACCESS_MUT(int8Arr4, mCurrentMoveDirection, 0x208);

	BUILD_ACCESS_MUT(bool, mShouldBounce, 0x20C);
	BUILD_ACCESS_MUT(uint32_t, mCurrentDelay, 0x210);
	BUILD_ACCESS_MUT(bool, mWaitingForServer, 0x214);
	BUILD_ACCESS_MUT(bool, mWaitingForServerHitGround, 0x215);
	BUILD_ACCESS_MUT(class HitResult, mCachedHitResult, 0x218);
	BUILD_ACCESS_MUT(bool, mDelayOneFrame, 0x278);

	MCAPI void _handleLightningOnHit(class Actor& owner);
	MCAPI bool _isLoyaltyTrident(class Actor const& owner);
	MCAPI bool _selectNextMoveDirection(Actor& owner, enum ProjectileComponent::EAxis avoidAxis);
	MCAPI void addAdditionalSaveData(class CompoundTag& tag);
	MCAPI Vec3 getShooterAngle(class Actor& owner);
	MCAPI void handleMovementGravity(class Actor& owner);
	MCAPI void handleMovementHoming(class Actor& owner);
	MCAPI void hurt(class Actor& owner, class ActorDamageSource const& damageSource);
	MCAPI void initFromDefinition(class Actor& owner);
	MCAPI void lerpMotion(class Actor& owner, class Vec3 const& delta);
	MCAPI void onHit(class Actor& owner, class HitResult const& result);
	MCAPI bool operator=(class ProjectileComponent const &rhs);
	MCAPI void readAdditionalSaveData(class Actor&, class CompoundTag const&, class DataLoadHelper&);
	MCAPI void setHitResult(class HitResult result);
	MCAPI void shoot(class Actor& owner, class Actor& shooter);
	MCAPI void shoot(
		class Actor& owner, class Vec3 const& direction, float power, float uncertainty, class Vec3 const& baseSpeed, class Actor* target);

	MCAPI static uint32_t const DELAY_ON_HIT = 5;
};