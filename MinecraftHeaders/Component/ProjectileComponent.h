#pragma once

#include "../Actor/ActorUniqueID.h"
#include "../Actor/HitResult.h"
#include "../Math/BlockPos.h"
#include "../Math/Vec3.h"
#include "../dll.h"

#include <string>
#include <vector>

class ActorDamageSource;
class Actor;
class CompoundTag;
class OnHitSubcomponent;
class DataLoadHelper;

enum class ParticleType : int32_t;
enum class ActorType : int32_t;
enum class LevelSoundEvent : int32_t;

enum class ProjectileAnchor : int32_t {
	Origin    = 0,
	EyeHeight = 1,
	Middle    = 2,
	Count     = 3,
};

struct DefinitionTrigger {
	std::string mType, mTarget;
	//ActorFilterGroup mFilter; // TODO
	uint8_t mFilter[0x40];
};

static_assert(sizeof(DefinitionTrigger) == 0x80);

class ProjectileComponent {
public:

	enum class EAxis : int8_t;

	bool mWasOnGround; // 0x0
	bool mNoPhysics; // 0x1
	ActorUniqueID mOwnerId; // 0x8
	Vec3 mThrownPos; // 0x10
	Vec3 mApexPos; // 0x1C
	bool mFoundApex; // 0x28
	int32_t mLife; // 0x2C
	int32_t mFlightTIme; // 0x30
	int32_t mGroundTime; // 0x34
	int32_t mShakeTime; // 0x38
	BlockPos mBlock; // 0x3C
	BlockPos mStuckToBlockPos; // 0x48
	Vec3 mCollisionPos; // 0x54
	int32_t mEnchantPower; // 0x60
	int32_t mEnchantImpaler; // 0x64
	HitResult mHitResult; // 0x68
	uint8_t mHitFacing; // 0xC8
	bool mReflect; // 0xC9
	float mPower; // 0xCC
	float mDamage; // 0xD0
	Vec3 mOffset; // 0xD4
	ParticleType mHitParticle; // 0xE0
	float mGravity; // 0xE4
	float mUpwardsAngleOffset; // 0xE8
	std::vector<OnHitSubcomponent *> mOnHitCommands; // 0xF0
	DefinitionTrigger mOnHitEvent; // 0x108
	float mUncertaintyBase; // 0x188
	float mUncertaintyMultiplier; // 0x18C
	ActorType mFilterType; // 0x190
	float mOnFireTime; // 0x194
	int32_t mPotionEffect; // 0x198 // effect id
	float mSplashRange; // 0x19C
	bool mKnockback; // 0x1A0
	float mKnockbackForce; // 0x1A4
	bool mCatchFire; // 0x1A8
	bool mChanneling; // 0x1A9
	bool mIsSplash; // 0x1AA
	float mInertiaMod; // 0x1AC
	float mLiquidInertia; // 0x1B0
	bool mSemiRandomDiffDamage; // 0x1B4
	ProjectileAnchor mSpawnPosAnchor; // 0x1B8
	LevelSoundEvent mHitEntitySound; // 0x1BC
	LevelSoundEvent mHitGroundSound; // 0x1C0
	LevelSoundEvent mShootSound; // 0x1C4
	bool mIsDangerous; // 0x1C8
	bool mShootTarget; // 0x1C9
	bool mDamageOwner; // 0x1CA
	bool mReflectOnHurt; // 0x1CB
	bool mDestroyOnHurt; // 0x1CC
	bool mStopOnHit; // 0x1CD
	bool mCritParticleOnHurt; // 0x1CE
	bool mHitWater; // 0x1CF
	bool mHitActor; // 0x1D0
	bool mMultipleHits; // 0x1D1
	int32_t mPiercingEnchantLevel; // 0x1D4
	int32_t mActorHitCount; // 0x1D8
	bool mIsHoming; // 0x1DC
	ActorUniqueID mPendingTargetID; // 0x1E0
	Actor* mTarget; // 0x1E8
	ActorUniqueID mTargetID; // 0x1F0
	Vec3 mTargetDelta; // 0x1F8
	int32_t mFlightSteps; // 0x204
	int8_t mCurrentMoveDirection[4]; // 0x208
	bool mShouldBounce; // 0x20C
	uint32_t mCurrentDelay; // 0x210
	bool mWaitingForServer; // 0x214
	bool mWaitingForServerHitGround; // 0x215
	HitResult mCachedHitResult; // 0x218
	bool mDelayOneFrame; // 0x278

	MCAPI void _handleLightningOnHit(Actor& owner);
	MCAPI bool _isLoyaltyTrident(Actor const& owner);
	MCAPI bool _selectNextMoveDirection(Actor& owner, ProjectileComponent::EAxis avoidAxis);
	MCAPI void addAdditionalSaveData(CompoundTag& tag);
	MCAPI Vec3 getShooterAngle(Actor& owner);
	MCAPI void handleMovementGravity(Actor& owner);
	MCAPI void handleMovementHoming(Actor& owner);
	MCAPI void hurt(Actor& owner, ActorDamageSource const& damageSource);
	MCAPI void initFromDefinition(Actor& owner);
	MCAPI void lerpMotion(Actor& owner, Vec3 const& delta);
	MCAPI void onHit(Actor& owner, HitResult const& result);
	MCAPI bool operator=(ProjectileComponent const &rhs);
	MCAPI void readAdditionalSaveData(Actor&, CompoundTag const&, DataLoadHelper&);
	MCAPI void setHitResult(HitResult result);
	MCAPI void shoot(Actor& owner, Actor& shooter);
	MCAPI void shoot(Actor& owner, Vec3 const& direction, float power, float uncertainty, Vec3 const& baseSpeed, Actor* target);

	MCAPI static uint32_t const DELAY_ON_HIT = 5;
};

static_assert(offsetof(ProjectileComponent, mKnockbackForce) == 0x1A4);
static_assert(sizeof(ProjectileComponent) == 0x280);