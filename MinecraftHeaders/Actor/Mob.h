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
  virtual bool isSprinting(void) const;
  virtual void setSprinting(bool);
  virtual void playAmbientSound(void);
  virtual enum LevelSoundEvent getAmbientSound(void);
  virtual int getAmbientSoundPostponeTicks(void);
  virtual int getAmbientSoundPostponeTicksRange(void);
  virtual struct TextureUVCoordinateSet const *getItemInHandIcon(class ItemStack const &, int);
  virtual float getSpeed(void) const;
  virtual void setSpeed(float);
  virtual float getJumpPower(void) const;
  virtual bool hurtEffects(class ActorDamageSource const &, int, bool, bool);
  virtual int getMeleeWeaponDamageBonus(class Mob *);
  virtual int getMeleeKnockbackBonus(void);
  virtual void travel(float, float, float);
  virtual void applyFinalFriction(float, bool);
  virtual void updateWalkAnim(void);
  virtual void aiStep(void);
  virtual void pushActors(void);
  virtual void lookAt(class Actor *, float, float);
  virtual bool isLookingAtAnEntity(void);
  virtual bool checkSpawnRules(bool);
  virtual bool checkSpawnObstruction(void) const;
  virtual float getAttackAnim(float);
  virtual int getItemUseDuration();
  virtual float getItemUseStartupProgress();
  virtual float getItemUseIntervalProgress();
  virtual int getItemuseIntervalAxis(void);
  virtual int getTimeAlongSwing(void);
  virtual void ate();
  virtual float getMaxHeadXRot(void);
  virtual class Mob *getLastHurtByMob(void);
  virtual void setLastHurtByMob(class Mob *);
  virtual class Player *getLastHurtByPlayer(void);
  virtual void setLastHurtByPlayer(class Player *);
  virtual class Mob *getLastHurtMob(void);
  virtual void setLastHurtMob(class Actor *);
  virtual bool isAlliedTo(Mob *);
  virtual bool doHurtTarget(class Actor *);
  virtual bool canBeControlledByRider();
  virtual void leaveCaravan(void);
  virtual void joinCaravan(class Mob *);
  virtual bool hasCaravanTail(void) const;
  virtual struct ActorUniqueID getCaravanHead(void) const;
  virtual int getArmorValue(void);
  virtual float getArmorCoverPercentage(void) const;
  virtual void hurtArmor(class ActorDamageSource const &, int);
  virtual void setDamagedArmor(enum ArmorSlot, class ItemStack const &);
  virtual void sendArmorDamage(std::bitset<4> const &);
  virtual void sendArmor(std::bitset<4> const &);
  virtual void containerChanged(int);
  virtual void updateEquipment(void);
  virtual int clearEquipment(void);
  virtual std::vector<class ItemStack const *> getAllArmor(void) const;
  virtual std::vector<int> getAllArmorID(void) const;
  virtual std::vector<class ItemStack const *> getAllHand(void) const;
  virtual std::vector<class ItemStack const *> getAllEquipment(void) const;
  virtual int getArmorTypeHash(void);
  virtual void dropEquipment(class ActorDamageSource const &, int);
  virtual void dropEquipment();
  virtual void clearVanishEnchantedItems(void);
  virtual void sendInventory(bool);
  virtual int getDamageAfterMagicAbsorb(class ActorDamageSource const &, int);
  virtual bool createAIGoals(void);
  virtual void onBorn(Actor &, Actor &);
  virtual bool setItemSlot(enum EquipmentSlot, class ItemStack const &);
  virtual void setTransitioningSitting(bool);
  virtual void attackAnimation(class Actor *, float);
  virtual int getAttackTime(void);
  virtual float _getWalkTargetValue(class BlockPos const &);
  virtual bool canExistWhenDisallowMob() const;
  virtual bool useNewAi() const;
  virtual void ascendLadder(void);
  virtual void ascendScaffolding(void);
  virtual void descendScaffolding(void);
  virtual std::unique_ptr<class BodyControl> initBodyControl(void);
  virtual void jumpFromGround(void);
  virtual void updateAi(void);
  virtual void newServerAiStep(void);
  virtual void _serverAiMobStep();
  virtual int getDamageAfterEnchantReduction(class ActorDamageSource const &, int);
  virtual int getDamageAfterArmorAbsorb(class ActorDamageSource const &, int);
  virtual void dropBags(void);
  virtual void dropContainer(void);
  virtual void tickDeath(void);
  virtual void _endJump(void);
  virtual void updateGliding(void);
  virtual bool _allowAscendingScaffolding(void) const;

  void frostWalk(void);
  int getCaravanSize(void) const;
  void setEatCounter(int);
  void resetAttributes(void);
  void setIsPregnant(bool);
  void _updateMobTravel(void);
  class Mob *getFirstCaravanHead(void);
  bool shouldApplyWaterGravity(void);
  enum TravelType getTravelType(void);
  float calcMoveRelativeSpeed(enum TravelType);
  bool checkTotemDeathProtection(class ActorDamageSource const &);

  BUILD_ACCESS_MUT(float, mYBodyRot, 0x620);
  BUILD_ACCESS_MUT(float, mYBodyRotO, 0x624);
  BUILD_ACCESS_MUT(float, mYHeadRot, 0x628);
  BUILD_ACCESS_MUT(float, mYHeadRotO, 0x62C);
  BUILD_ACCESS_MUT(int, mHurtTime, 0x630);
  BUILD_ACCESS_MUT(int, mHurtDuration, 0x634);
  BUILD_ACCESS_MUT(float, mHurtDirection, 0x638);
  BUILD_ACCESS_MUT(int, mAttackTime, 0x63C);
  BUILD_ACCESS_MUT(float, mOTilt, 0x640);
  BUILD_ACCESS_MUT(float, mTilt, 0x644);
  BUILD_ACCESS_MUT(int, mLookTime, 0x648);
  BUILD_ACCESS_MUT(int, mFallTime, 0x64C);
  BUILD_ACCESS_MUT(bool, mFloatsInLiquid, 0x650);
  BUILD_ACCESS_MUT(int, mJumpTicks, 0x654);
  BUILD_ACCESS_MUT(class Vec3, mElytraRot, 0x658);
  BUILD_ACCESS_MUT(class CompassSpriteCalculator, mCompassSpriteCalc, 0x664);
  BUILD_ACCESS_MUT(class ClockSpriteCalculator, mClockSpriteCalc, 0x670);
  BUILD_ACCESS_MUT(float, mXxa, 0x67C);
  BUILD_ACCESS_MUT(float, mYya, 0x680);
  BUILD_ACCESS_MUT(float, mZza, 0x684);
  BUILD_ACCESS_MUT(float, mYRotA, 0x688);
  BUILD_ACCESS_MUT(bool, mHasMoveInput, 0x68C);
  BUILD_ACCESS_MUT(float, mAttackAnim, 0x690);
  BUILD_ACCESS_MUT(float, mORun, 0x694);
  BUILD_ACCESS_MUT(float, mRun, 0x698);
  BUILD_ACCESS_MUT(bool, mSwinging, 0x69C);
  BUILD_ACCESS_MUT(int, mSwingTime, 0x6A0);
  BUILD_ACCESS_MUT(int, mNoActionTime, 0x6A4);
  BUILD_ACCESS_MUT(int, mNoJumpDelay, 0x6A8);
  BUILD_ACCESS_MUT(float, mDefaultLookAngle, 0x6AC);
  BUILD_ACCESS_MUT(float, mFrictionModifier, 0x6B0);
  BUILD_ACCESS_MUT(float, mFlyingSpeed, 0x6B4);
  BUILD_ACCESS_MUT(float, mSwimSpeedMultiplier, 0x6B8);
  BUILD_ACCESS_MUT(int, mDeathTime, 0x6BC);
  BUILD_ACCESS_MUT(int, mDeathScore, 0x6C0);
  BUILD_ACCESS_MUT(float, mAnimStep, 0x6C4);
  BUILD_ACCESS_MUT(float, mAnimStepO, 0x6C8);
  BUILD_ACCESS_MUT(float, mLockedBodyYRot, 0x6CC);
  BUILD_ACCESS_MUT(float, mRiderYRotLimit, 0x6D0);
  BUILD_ACCESS_MUT(class MovementInterpolator, mInterpolation, 0x6D4);
  BUILD_ACCESS_MUT(int, mLastHurt, 0x6FC);
  BUILD_ACCESS_MUT(enum ActorDamageCause, mLastHurtCause, 0x700);
  BUILD_ACCESS_MUT(uint64_t, mLastHurtTimestamp, 0x708);
  BUILD_ACCESS_MUT(int, mDmgSpill, 0x710);
  BUILD_ACCESS_MUT(int, mDmgPartial, 0x714);
  BUILD_ACCESS_MUT(bool, mJumping, 0x718);
  BUILD_ACCESS_MUT(bool, mJumpVelRedux, 0x719);
  BUILD_ACCESS_MUT(float, mPlayerJumpPendingScale, 0x71C);
  BUILD_ACCESS_MUT(bool, mAllowStandSliding, 0x720);
  BUILD_ACCESS_MUT(class Vec3, mJumpStartPos, 0x724);
  BUILD_ACCESS_MUT(float, mSpeed, 0x730);
  BUILD_ACCESS_MUT(float, mMovementComponentCurrentSpeed, 0x734);
  BUILD_ACCESS_MUT(bool, mSurfaceMob, 0x738);
  BUILD_ACCESS_MUT(bool, mNaturallySpawned, 0x739);
  BUILD_ACCESS_MUT(bool, mDead, 0x73A);
  BUILD_ACCESS_MUT(std::weak_ptr<class VillageLegacy>, mVillageLegacy, 0x740);
  BUILD_ACCESS_MUT(bool, mWantsToBeJockey, 0x750);
  BUILD_ACCESS_MUT(int, mAmbientPlaybackInterval, 0x754);
  BUILD_ACCESS_MUT(bool, mSpawnedXp, 0x758);
  BUILD_ACCESS_MUT(int, mRollCounter, 0x75C);
  BUILD_ACCESS_MUT(struct ActorUniqueID, mLookingAtId, 0x760);
  BUILD_ACCESS_MUT(struct ActorUniqueID, mLastHurtMobId, 0x768);
  BUILD_ACCESS_MUT(struct ActorUniqueID, mLastHurtByMobId, 0x770);
  BUILD_ACCESS_MUT(struct ActorUniqueID, mLastHurtByPlayerId, 0x778);
  BUILD_ACCESS_MUT(struct ActorUniqueID, mCaravanHead, 0x780);
  BUILD_ACCESS_MUT(struct ActorUniqueID, mCaravanTail, 0x788);
  BUILD_ACCESS_MUT(int, mLastHurtMobTimestamp, 0x790);
  BUILD_ACCESS_MUT(int, mLastHurtByMobTime, 0x794);
  BUILD_ACCESS_MUT(int, mLastHurtByMobTimestamp, 0x798);
  BUILD_ACCESS_MUT(int, mOAttackAnim, 0x79C);
  BUILD_ACCESS_MUT(int, mArrowCount, 0x7A0);
  BUILD_ACCESS_MUT(int, mRemoveArrowTime, 0x7A4);
  BUILD_ACCESS_MUT(int, mFallFlyTicks, 0x7A8);
  BUILD_ACCESS_MUT(bool, mHasBoundOrigin, 0x7AC);
  BUILD_ACCESS_MUT(class BlockPos, mBoundOrigin, 0x7B0);
  BUILD_ACCESS_MUT(enum MobSpawnMethod, mSpawnMethod, 0x7BC);
  BUILD_ACCESS_MUT(bool, mCreateAiOnReload, 0x7C0);
  BUILD_ACCESS_MUT(struct ActorUniqueID, mTargetCaptainId, 0x7C8);
};