#pragma once

#include "Actor.h"
#include <bitset>

enum class EquipmentSlot {
	None                = -1,
	Begin               = 0,
	HandSlot            = 0,
	Mainhand            = 0,
	Offhand             = 1,
	ArmorSlot           = 2,
	Head                = 2,
	Torso               = 3,
	Legs                = 4,
	Feet                = 5,
	ContainerSlot       = 6,
	Hotbar              = 6,
	Inventory           = 7,
	EnderChest          = 8,
	Saddle              = 9,
	EntityArmor         = 10,
	Chest               = 11,
	EquipmentSlotCount  = 12
};

enum class MobSpawnMethod {
	Unknown           = 0,
	SpawnEgg          = 1,
	Command           = 2,
	Dispenser         = 3,
	Spawner           = 4,
	SpawnMethodCount  = 5
};

class Mob : public Actor {
public:

	enum class TravelType {
		Water  = 0,
		Lava   = 1,
		Ground = 2,
		Air    = 3
	};

	virtual void knockback(class Actor *, int, float, float, float, float, float);
	virtual void resolveDeathLoot(int, class ActorDamageSource const &);
	virtual void spawnAnim();
	virtual void setSleeping(bool);
	virtual bool isSprinting() const;
	virtual void setSprinting(bool);
	virtual void playAmbientSound();
	virtual enum LevelSoundEvent getAmbientSound();
	virtual int getAmbientSoundPostponeTicks();
	virtual int getAmbientSoundPostponeTicksRange();
	virtual struct TextureUVCoordinateSet const *getItemInHandIcon(class ItemStack const &, int);
	virtual float getSpeed() const;
	virtual void setSpeed(float);
	virtual float getJumpPower() const;
	virtual bool hurtEffects(class ActorDamageSource const &, int damage, bool knock, bool ignite);
	virtual int getMeleeWeaponDamageBonus(class Mob *);
	virtual int getMeleeKnockbackBonus();
	virtual void travel(float, float, float);
	virtual void applyFinalFriction(float, bool);
	virtual void updateWalkAnim();
	virtual void aiStep();
	virtual void pushActors();
	virtual void lookAt(class Actor *, float, float);
	virtual bool isLookingAtAnEntity();
	virtual bool checkSpawnRules(bool);
	virtual bool checkSpawnObstruction() const;
	virtual float getAttackAnim(float);
	virtual int getItemUseDuration();
	virtual float getItemUseStartupProgress();
	virtual float getItemUseIntervalProgress();
	virtual int getItemuseIntervalAxis();
	virtual int getTimeAlongSwing();
	virtual void ate();
	virtual float getMaxHeadXRot();
	virtual class Mob *getLastHurtByMob();
	virtual void setLastHurtByMob(class Mob *);
	virtual class Player *getLastHurtByPlayer();
	virtual void setLastHurtByPlayer(class Player *);
	virtual class Mob *getLastHurtMob();
	virtual void setLastHurtMob(class Actor *);
	virtual bool isAlliedTo(Mob *);
	virtual bool doHurtTarget(class Actor *);
	virtual bool canBeControlledByRider();
	virtual void leaveCaravan();
	virtual void joinCaravan(class Mob *);
	virtual bool hasCaravanTail() const;
	virtual struct ActorUniqueID getCaravanHead() const;
	virtual int getArmorValue();
	virtual float getArmorCoverPercentage() const;
	virtual void hurtArmor(class ActorDamageSource const &, int);
	virtual void setDamagedArmor(enum ArmorSlot, class ItemStack const &);
	virtual void sendArmorDamage(std::bitset<4> const &);
	virtual void sendArmor(std::bitset<4> const &);
	virtual void containerChanged(int);
	virtual void updateEquipment();
	virtual int clearEquipment();
	virtual std::vector<class ItemStack const *> getAllArmor() const;
	virtual std::vector<int> getAllArmorID() const;
	virtual std::vector<class ItemStack const *> getAllHand() const;
	virtual std::vector<class ItemStack const *> getAllEquipment() const;
	virtual int getArmorTypeHash();
	virtual void dropEquipment(class ActorDamageSource const &, int);
	virtual void dropEquipment();
	virtual void clearVanishEnchantedItems();
	virtual void sendInventory(bool);
	virtual int getDamageAfterMagicAbsorb(class ActorDamageSource const &, int);
	virtual bool createAIGoals();
	virtual void onBorn(Actor &, Actor &);
	virtual bool setItemSlot(enum EquipmentSlot, class ItemStack const &);
	virtual void setTransitioningSitting(bool);
	virtual void attackAnimation(class Actor *, float);
	virtual int getAttackTime();
	virtual float _getWalkTargetValue(class BlockPos const &);
	virtual bool canExistWhenDisallowMob() const;
	virtual bool useNewAi() const;
	virtual void ascendLadder();
	virtual void ascendScaffolding();
	virtual void descendScaffolding();
	virtual std::unique_ptr<class BodyControl> initBodyControl();
	virtual void jumpFromGround();
	virtual void updateAi();
	virtual void newServerAiStep();
	virtual void _serverAiMobStep();
	virtual int getDamageAfterEnchantReduction(class ActorDamageSource const &, int);
	virtual int getDamageAfterArmorAbsorb(class ActorDamageSource const &, int);
	virtual void dropBags();
	virtual void dropContainer();
	virtual void tickDeath();
	virtual void _endJump();
	virtual void updateGliding();
	virtual bool _allowAscendingScaffolding() const;

	MCAPI void frostWalk();
	MCAPI int getCaravanSize() const;
	MCAPI void setEatCounter(int);
	MCAPI void resetAttributes();
	MCAPI void setIsPregnant(bool);
	MCAPI void _updateMobTravel();
	MCAPI class Mob *getFirstCaravanHead();
	MCAPI bool shouldApplyWaterGravity();
	MCAPI enum TravelType getTravelType();
	MCAPI float calcMoveRelativeSpeed(enum TravelType);
	MCAPI bool checkTotemDeathProtection(class ActorDamageSource const &);

	// mob fields
	CLASS_FIELD(mYBodyRot, 0x620, float);
	CLASS_FIELD(mYBodyRotOld, 0x624, float);
	CLASS_FIELD(mYHeadRot, 0x628, float);
	CLASS_FIELD(mYHeadRotOld, 0x62C, float);
	CLASS_FIELD(mHurtTime, 0x630, int32_t);
	CLASS_FIELD(mHurtDuration, 0x634, int32_t);
	CLASS_FIELD(mHurtDirection, 0x638, float);
	CLASS_FIELD(mAttackTime, 0x63C, int32_t);
	CLASS_FIELD(mTiltOld, 0x640, float);
	CLASS_FIELD(mTilt, 0x644, float);
	CLASS_FIELD(mLookTime, 0x648, int32_t);
	CLASS_FIELD(mFallTime, 0x64C, int32_t);
	CLASS_FIELD(mFloatsInLiquid, 0x650, bool);
	CLASS_FIELD(mJumpTicks, 0x654, int32_t);
	CLASS_FIELD(mElytraRot, 0x658, class Vec3);
	CLASS_FIELD(mCompassSpriteCalc, 0x664, class CompassSpriteCalculator);
	CLASS_FIELD(mClockSpriteCalc, 0x670, class ClockSpriteCalculator);
	CLASS_FIELD(mXxa, 0x67C, float);
	CLASS_FIELD(mYya, 0x680, float);
	CLASS_FIELD(mZza, 0x684, float);
	CLASS_FIELD(mYRotA, 0x688, float);
	CLASS_FIELD(mHasMoveInput, 0x68C, bool);
	CLASS_FIELD(mAttackAnim, 0x690, float);
	CLASS_FIELD(mRunOld, 0x694, float);
	CLASS_FIELD(mRun, 0x698, float);
	CLASS_FIELD(mSwinging, 0x69C, bool);
	CLASS_FIELD(mSwingTime, 0x6A0, int32_t);
	CLASS_FIELD(mNoActionTime, 0x6A4, int32_t);
	CLASS_FIELD(mNoJumpDelay, 0x6A8, int32_t);
	CLASS_FIELD(mDefaultLookAngle, 0x6AC, float);
	CLASS_FIELD(mFrictionModifier, 0x6B0, float);
	CLASS_FIELD(mFlyingSpeed, 0x6B4, float);
	CLASS_FIELD(mSwimSpeedMultiplier, 0x6B8, float);
	CLASS_FIELD(mDeathTime, 0x6BC, int32_t);
	CLASS_FIELD(mDeathScore, 0x6C0, int32_t);
	CLASS_FIELD(mAnimStep, 0x6C4, float);
	CLASS_FIELD(mAnimStepOld, 0x6C8, float);
	CLASS_FIELD(mLockedBodyYRot, 0x6CC, float);
	CLASS_FIELD(mRiderYRotLimit, 0x6D0, float);
	CLASS_FIELD(mInterpolation, 0x6D4, class MovementInterpolator);
	CLASS_FIELD(mLastHurt, 0x6FC, int32_t);
	CLASS_FIELD(mLastHurtCause, 0x700, enum ActorDamageCause);
	CLASS_FIELD(mLastHurtTimestamp, 0x708, uint64_t);
	CLASS_FIELD(mDmgSpill, 0x710, int32_t);
	CLASS_FIELD(mDmgPartial, 0x714, int32_t);
	CLASS_FIELD(mJumping, 0x718, bool);
	CLASS_FIELD(mJumpVelRedux, 0x719, bool);
	CLASS_FIELD(mPlayerJumpPendingScale, 0x71C, float);
	CLASS_FIELD(mAllowStandSliding, 0x720, bool);
	CLASS_FIELD(mJumpStartPos, 0x724, class Vec3);
	CLASS_FIELD(mSpeed, 0x730, float);
	CLASS_FIELD(mMovementComponentCurrentSpeed, 0x734, float);
	CLASS_FIELD(mSurfaceMob, 0x738, bool);
	CLASS_FIELD(mNaturallySpawned, 0x739, bool);
	CLASS_FIELD(mDead, 0x73A, bool);
	CLASS_FIELD(mVillageLegacy, 0x740, std::weak_ptr<class VillageLegacy>);
	CLASS_FIELD(mWantsToBeJockey, 0x750, bool);
	CLASS_FIELD(mAmbientPlaybackInterval, 0x754, int32_t);
	CLASS_FIELD(mSpawnedXp, 0x758, bool);
	CLASS_FIELD(mRollCounter, 0x75C, int32_t);
	CLASS_FIELD(mLookingAtId, 0x760, struct ActorUniqueID);
	CLASS_FIELD(mLastHurtMobId, 0x768, struct ActorUniqueID);
	CLASS_FIELD(mLastHurtByMobId, 0x770, struct ActorUniqueID);
	CLASS_FIELD(mLastHurtByPlayerId, 0x778, struct ActorUniqueID);
	CLASS_FIELD(mCaravanHead, 0x780, struct ActorUniqueID);
	CLASS_FIELD(mCaravanTail, 0x788, struct ActorUniqueID);
	CLASS_FIELD(mLastHurtMobTimestamp, 0x790, int32_t);
	CLASS_FIELD(mLastHurtByMobTime, 0x794, int32_t);
	CLASS_FIELD(mLastHurtByMobTimestamp, 0x798, int32_t);
	CLASS_FIELD(mOAttackAnim, 0x79C, int32_t);
	CLASS_FIELD(mArrowCount, 0x7A0, int32_t);
	CLASS_FIELD(mRemoveArrowTime, 0x7A4, int32_t);
	CLASS_FIELD(mFallFlyTicks, 0x7A8, int32_t);
	CLASS_FIELD(mHasBoundOrigin, 0x7AC, bool);
	CLASS_FIELD(mBoundOrigin, 0x7B0, class BlockPos);
	CLASS_FIELD(mSpawnMethod, 0x7BC, enum MobSpawnMethod);
	CLASS_FIELD(mCreateAiOnReload, 0x7C0, bool);
	CLASS_FIELD(mTargetCaptainId, 0x7C8, struct ActorUniqueID);
};