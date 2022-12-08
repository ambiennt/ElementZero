#pragma once

#include <cstdint>

#include "ActorRuntimeID.h"
#include "ActorType.h"
#include "ActorCategory.h"
#include "ActorUniqueID.h"
#include "ActorDamageSource.h"
#include "SynchedActorData.h"
#include "Attribute.h"
#include "MobEffect.h"
#include "../Math/Vec3.h"
#include "../Math/BlockPos.h"
#include "../Container/SimpleContainer.h"
#include "../Core/AutomaticID.h"
#include "../Core/Util.h"
#include "../Core/RelativeFloat.h"
#include "../Command/CommandPermissionLevel.h"
#include "../Component/AABBShapeComponent.h"
#include "../Level/Level.h"
#include "../dll.h"

#include <hook.h>
#include <modutils.h>

class Dimension;

enum class ActorEvent : int8_t;
enum class ActorType : int32_t;
enum class MaterialType : int32_t;
enum class ActorDamageCause : int32_t;
enum class ItemUseMethod : int32_t;
enum class LevelSoundEvent : int32_t;
enum class DimensionID : int32_t;

enum class InputMode : int32_t {
	Undefined         = 0,
	Mouse             = 1,
	Touch             = 2,
	GamePad           = 3,
	MotionController  = 4,
	Count             = 5,
};

enum class SpawnRuleEnum : int32_t {
	Undefined     = -1,
	NoSpawnRules  = 0,
	HasSpawnRules = 1,
};

enum class PortalAxis : int32_t {
	Unknown = 0,
	X       = 1,
	Z       = 2,
	Count   = 3,
};

enum class ArmorMaterialType : int32_t {
	None                  = -1,
	DefaultArmor          = 0,
	EnchantedArmor        = 1,
	LeatherArmor          = 2,
	EnchantedLeatherArmor = 3,
};

enum class ArmorTextureType : int32_t {
	None      = -1,
	Leather   = 0,
	Chain     = 1,
	Iron      = 2,
	Diamond   = 3,
	Gold      = 4,
	Elytra    = 5,
	Turtle    = 6,
	Netherite = 7,
};

enum class ActorLocation : int32_t {
	Feet               = 0,
	Body               = 1,
	WeaponAttachPoint  = 2,
	Head               = 3,
	DropAttachPoint    = 4,
	ExplosionPoint     = 5,
	Eyes               = 6,
	BreathingPoint     = 7,
	Mouth              = 8,
};

enum class PaletteColor : int32_t {
	White              = 0,
	Orange             = 1,
	Magenta            = 2,
	LightBlue          = 3,
	Yellow             = 4,
	LightGreen         = 5,
	Pink               = 6,
	Gray               = 7,
	Silver             = 8,
	Cyan               = 9,
	Purple             = 10,
	Blue               = 11,
	Brown              = 12,
	Green              = 13,
	Red                = 14,
	Black              = 15,
	PaletteColorCount  = 16,
};

enum class ArmorSlot : int32_t {
	Head  = 0,
	Torso = 1,
	Legs  = 2,
	Feet  = 3,
	Count = 4,
};

enum class ActorFlags {
	Unknown                     = -1,
	OnFire                      = 0,
	Sneaking                    = 1,
	Riding                      = 2,
	Sprinting                   = 3,
	UsingItem                   = 4,
	Invisible                   = 5,
	Tempted                     = 6,
	InLove                      = 7,
	Saddled                     = 8,
	Powered                     = 9,
	Ignited                     = 10,
	Baby                        = 11,
	Converting                  = 12,
	Critical                    = 13,
	CanShowName                 = 14,
	AlwaysShowName              = 15,
	NoAI                        = 16, // immobile flag
	Immobile                    = 16,
	Silent                      = 17,
	WallClimbing                = 18,
	CanClimb                    = 19,
	CanSwim                     = 20,
	CanFly                      = 21,
	CanWalk                     = 22,
	Resting                     = 23,
	Sitting                     = 24,
	Angry                       = 25,
	Interested                  = 26,
	Charged                     = 27,
	Tamed                       = 28,
	Orphaned                    = 29,
	Leashed                     = 30,
	Sheared                     = 31,
	Gliding                     = 32,
	Elder                       = 33,
	Moving                      = 34,
	Breathing                   = 35,
	Chested                     = 36,
	Stackable                   = 37,
	ShowBottom                  = 38,
	Standing                    = 39,
	Shaking                     = 40,
	Idling                      = 41,
	Casting                     = 42,
	Charging                    = 43,
	WasdControlled              = 44,
	CanPowerJump                = 45,
	Lingering                   = 46,
	HasCollision                = 47,
	HasGravity                  = 48,
	FireImmune                  = 49,
	Dancing                     = 50,
	Enchanted                   = 51,
	ReturnTrident               = 52,
	ContainerIsPrivate          = 53,
	IsTransforming              = 54,
	DamageNearbyMobs            = 55,
	Swimming                    = 56,
	Bribed                      = 57,
	IsPregnant                  = 58,
	LayingEgg                   = 59,
	RiderCanPick                = 60,
	TransitionSitting           = 61,
	Eating                      = 62,
	LayingDown                  = 63,
	Sneezing                    = 64,
	Trusting                    = 65,
	Rolling                     = 66,
	Scared                      = 67,
	InScaffolding               = 68,
	OverScaffolding             = 69,
	FallThroughScaffolding      = 70,
	Blocking                    = 71,
	TransitionBlocking          = 72,
	BlockedUsingShield          = 73,
	BlockedUsingDamagedShield   = 74,
	Sleeping                    = 75,
	WantsToWake                 = 76,
	TradeInterest               = 77,
	DoorBreaker                 = 78,
	BreakingObstruction         = 79,
	DoorOpener                  = 80,
	IsIllagerCaptain            = 81,
	Stunned                     = 82,
	Roaring                     = 83,
	DelayedAttack               = 84,
	IsAvoidingMobs              = 85,
	IsAvoidingBlock             = 86,
	FacingTargetToRangeAttack   = 87,
	HiddenWhenInvisible         = 88,
	IsInUI                      = 89,
	Stalking                    = 90,
	Emoting                     = 91,
	Celebrating                 = 92,
	Admiring                    = 93,
	CelebratingSpecial          = 94,
	Count                       = 95,
};

class Actor {
protected:
	MCAPI bool _damageSensorComponentHurt(int32_t &damage, int32_t lastHurt, ActorDamageSource const& source);

public:
	enum class InitializationMethod : int32_t {
		INVALID          = 0,
		LOADED           = 1,
		SPAWNED          = 2,
		BORN             = 3,
		TRANSFORMED      = 4,
		UPDATED          = 5,
		EVENT            = 6,
		LEGACY           = 7,
	};

	virtual bool hasComponent(class HashedString const &) const;
	virtual void reloadHardcoded(enum InitializationMethod, class VariantParameterList const &);
	virtual void reloadHardcodedClient(enum InitializationMethod, class VariantParameterList const &);
	virtual void initializeComponents(enum InitializationMethod, class VariantParameterList const &);
	virtual void reloadComponents(enum InitializationMethod, class VariantParameterList const &);
	virtual void _serverInitItemStackIds();
	virtual void _doInitialMove();
	virtual ~Actor();
	virtual void reset();
	virtual int getOnDeathExperience();
	virtual enum ActorType getOwnerEntityType();
	virtual void remove();
	virtual void setPos(class Vec3 const &);
	virtual class Vec3 const &getPos() const;
	virtual class Vec3 const &getPosOld() const;
	virtual class Vec3 const getPosExtrapolated(float) const;
	virtual class Vec3 getAttachPos(enum ActorLocation, float) const;
	virtual class Vec3 getFiringPos() const;
	virtual void setRot(class Vec2 const &);
	virtual void move(class Vec3 const &);
	virtual class Vec3 getInterpolatedRidingPosition(float) const;
	virtual float getInterpolatedBodyRot(float) const;
	virtual float getInterpolatedHeadRot(float) const;
	virtual float getInterpolatedBodyYaw(float) const;
	virtual float getYawSpeedInDegreesPerSecond() const;
	virtual float getInterpolatedWalkAnimSpeed(float) const;
	virtual class Vec3 getInterpolatedRidingOffset(float) const;
	virtual void checkBlockCollisions(class AABB const &);
	virtual void checkBlockCollisions();
	virtual bool isFireImmune() const;
	virtual void breaksFallingBlocks() const;
	virtual void blockedByShield(class ActorDamageSource const &, class Actor &);
	virtual void moveRelative(float, float, float, float);
	virtual void teleportTo(class Vec3 const &pos, bool shouldStopRiding, int cause, int entityType, struct ActorUniqueID const &destinationEntityId); // cause, entityType, and destinationEntityId are unused, entityType is actually ActorType
	virtual bool tryTeleportTo(class Vec3 const &pos, bool landOnBlock, bool avoidLiquid, int cause, int entityType); // cause and entityType are unused, entityType is actually ActorType
	virtual void chorusFruitTeleport(class Vec3 &);
	virtual void lerpTo(class Vec3 const &, class Vec2 const &, int);
	virtual void lerpMotion(class Vec3 const &);
	virtual std::unique_ptr<class AddActorBasePacket> getAddPacket();
	virtual void normalTick();
	virtual void baseTick();
	virtual void rideTick();
	virtual void positionRider(class Actor &, float);
	virtual float getRidingHeight();
	virtual bool startRiding(class Actor &);
	virtual void addRider(class Actor &);
	virtual void flagRiderToRemove(class Actor &);
	virtual std::string getExitTip(std::string const &, enum InputMode) const;
	virtual bool intersects(class Vec3 const &, class Vec3 const &) const;
	virtual bool isFree(class Vec3 const &, float);
	virtual bool isFree(class Vec3 const &);
	virtual bool isInWall() const;
	virtual bool isInvisible() const;
	virtual bool canShowNameTag() const;
	virtual bool canExistInPeaceful() const;
	virtual void setNameTagVisible(bool);
	virtual std::string const &getNameTag() const;
	virtual uint64_t getNameTagAsHash() const;
	virtual std::string getFormattedNameTag() const;
	virtual void filterFormattedNameTag(class UIProfanityContext const &);
	virtual void setNameTag(std::string const &);
	virtual bool getAlwaysShowNameTag() const;
	virtual void setScoreTag(std::string const &);
	virtual std::string const &getScoreTag() const;
	virtual bool isInWater() const;
	virtual bool hasEnteredWater() const;
	virtual bool isImmersedInWater() const;
	virtual bool isInWaterOrRain() const;
	virtual bool isInLava() const;
	virtual bool isUnderLiquid(enum MaterialType) const;
	virtual bool isOverWater() const;
	virtual void makeStuckInBlock(float);
	virtual float getCameraOffset() const;
	virtual float getShadowHeightOffs();
	virtual float getShadowRadius() const;
	virtual class Vec3 getHeadLookVector(float);
	virtual bool canSeeInvisible() const;
	virtual bool canSee(class Actor const &) const;
	virtual bool canSee(class Vec3 const &) const;
	virtual bool isSkyLit(float);
	virtual float getBrightness(float) const;
	virtual void interactPreventDefault();
	virtual void playerTouch(Player &);
	virtual void onAboveBubbleColumn(bool);
	virtual void onInsideBubbleColumn(bool);
	virtual bool isImmobile() const;
	virtual bool isSilent();
	virtual bool isPickable();
	virtual bool isFishable() const;
	virtual bool isSleeping() const;
	virtual bool isShootable();
	virtual bool isSneaking() const;
	virtual void setSneaking(bool);
	virtual bool isBlocking() const;
	virtual bool isDamageBlocked(ActorDamageSource const &) const;
	virtual bool isAlive() const;
	virtual bool isOnFire() const;
	virtual bool isOnHotBlock() const;
	virtual bool isCreativeModeAllowed();
	virtual bool isSurfaceMob() const;
	virtual bool isTargetable() const;
	virtual bool canAttack(class Actor *, bool) const;
	virtual void setTarget(class Actor *);
	virtual Actor *findAttackTarget();
	virtual bool isValidTarget(Actor *) const;
	virtual bool attack(class Actor &);
	virtual void performRangedAttack(class Actor &, float);
	virtual void adjustDamageAmount(int &) const;
	virtual int getEquipmentCount() const;
	virtual void setOwner(struct ActorUniqueID);
	virtual void setSitting(bool);
	virtual void onTame();
	virtual void onFailedTame();
	virtual int getInventorySize() const;
	virtual int getEquipSlots() const;
	virtual int getChestSlots() const;
	virtual void setStanding(bool);
	virtual bool canPowerJump() const;
	virtual void setCanPowerJump(bool);
	virtual bool isJumping() const;
	virtual bool isEnchanted() const;
	virtual void rideJumped();
	virtual void rideLanded(Vec3 const &, Vec3 const &);
	virtual bool shouldRender() const;
	virtual bool isInvulnerableTo(class ActorDamageSource const &) const;
	virtual enum ActorDamageCause getBlockDamageCause(class Block const &) const;
	virtual void actuallyHurt(int damage, class ActorDamageSource const &, bool bypassArmor);
	virtual void animateHurt();
	virtual bool doFireHurt(int damage);
	virtual void onLightningHit();
	virtual void onBounceStarted(BlockPos const &, BlockPos const &);
	virtual void feed(int);
	virtual void handleEntityEvent(enum ActorEvent, int);
	virtual float getPickRadius();
	virtual class HashedString const &getActorRendererId() const;
	virtual class ItemActor *spawnAtLocation(int, int);
	virtual class ItemActor *spawnAtLocation(int, int, float);
	virtual class ItemActor *spawnAtLocation(class Block const &, int);
	virtual class ItemActor *spawnAtLocation(class Block const &, int, float);
	virtual class ItemActor *spawnAtLocation(class ItemStack const &, float);
	virtual void despawn();
	virtual void killed(class Actor &);
	virtual void awardKillScore(Actor &, int);
	virtual void setArmor(enum ArmorSlot, class ItemStack const &);
	virtual class ItemStack const &getArmor(enum ArmorSlot) const;
	virtual enum ArmorMaterialType getArmorMaterialTypeInSlot(enum ArmorSlot) const;
	virtual enum ArmorTextureType getArmorMaterialTextureTypeInSlot(enum ArmorSlot) const;
	virtual float getArmorColorInSlot(enum ArmorSlot, int) const;
	virtual void setEquippedSlot(enum ArmorSlot, int, int);
	virtual void setEquippedSlot(enum ArmorSlot, class ItemStack const &);
	virtual class ItemStack const &getCarriedItem() const;
	virtual void setCarriedItem(class ItemStack const &);
	virtual void setOffhandSlot(class ItemStack const &);
	virtual class ItemStack const &getEquippedTotem() const;
	virtual bool consumeTotem();
	virtual bool save(class CompoundTag &);
	virtual void saveWithoutId(class CompoundTag &);
	virtual bool load(class CompoundTag const &, class DataLoadHelper &);
	virtual void loadLinks(class CompoundTag const &, std::vector<struct ActorLink> &, class DataLoadHelper &);
	virtual enum ActorType getEntityTypeId() const;
	virtual class HashedString const &queryEntityRenderer() const;
	virtual struct ActorUniqueID getSourceUniqueID() const;
	virtual void setOnFire(int);
	virtual class AABB getHandleWaterAABB() const;
	virtual void handleInsidePortal(class BlockPos const &);
	virtual int getPortalCooldown() const;
	virtual int getPortalWaitTime() const;
	virtual class AutomaticID<class Dimension, int> getDimensionId() const;
	virtual bool canChangeDimensions() const;
	virtual void changeDimension(class AutomaticID<class Dimension, int>, bool);
	virtual void changeDimension(class ChangeDimensionPacket const &);
	virtual struct ActorUniqueID getControllingPlayer() const;
	virtual void checkFallDamage(float, bool);
	virtual void causeFallDamage(float);
	virtual void handleFallDistanceOnServer(float, bool);
	virtual void playSynchronizedSound(enum LevelSoundEvent, class Vec3 const &, class Block const &, bool isGlobal);
	virtual void playSynchronizedSound(enum LevelSoundEvent, class Vec3 const &, int data, bool isGlobal);
	virtual void onSynchedDataUpdate(int);
	virtual bool canAddRider(class Actor &) const;
	virtual bool canPickupItem(ItemStack const &) const;
	virtual bool canBePulledIntoVehicle() const;
	virtual bool inCaravan() const;
	virtual bool isLeashableType();
	virtual void tickLeash();
	virtual void sendMotionPacketIfNeeded();
	virtual bool canSynchronizeNewEntity() const;
	virtual void stopRiding(bool exitFromRider, bool actorIsBeingDestroyed, bool switchingRides);
	virtual void startSwimming();
	virtual void stopSwimming();
	virtual void buildDebugInfo(std::string &) const;
	virtual enum CommandPermissionLevel getCommandPermissionLevel() const;
	virtual class AttributeInstance *getMutableAttribute(class Attribute const &);
	virtual class AttributeInstance const &getAttribute(class Attribute const &) const;
	virtual int getDeathTime() const;
	virtual void heal(int);
	virtual bool isInvertedHealAndHarm() const;
	virtual bool canBeAffected(int) const;
	virtual bool canBeAffected(class MobEffectInstance const &) const;
	virtual bool canBeAffectedByArrow(class MobEffectInstance const &) const;
	virtual void onEffectAdded(class MobEffectInstance &);
	virtual void onEffectUpdated(class MobEffectInstance const &);
	virtual void onEffectRemoved(class MobEffectInstance &);
	virtual class AnimationComponent &getAnimationComponent();
	virtual void openContainerComponent(class Player &);
	virtual void swing();
	virtual void useItem(class ItemStack &, enum ItemUseMethod, bool consumeItem);
	virtual bool hasOutputSignal(unsigned char) const;
	virtual int getOutputSignal() const;
	virtual void getDebugText(std::vector<std::string> &);
	virtual float getMapDecorationRotation() const;
	virtual float getRiderYRotation(class Actor const &) const;
	virtual float getYHeadRot() const;
	virtual bool isWorldBuilder();
	virtual bool isCreative() const;
	virtual bool isAdventure() const;
	virtual bool add(class ItemStack &item);
	virtual bool drop(class ItemStack const &item, bool randomly);
	virtual bool getInteraction(class Player &, class ActorInteraction &, class Vec3 const &);
	virtual bool canDestroyBlock(Block const &) const;
	virtual void setAuxValue(int);
	virtual void setSize(float, float);
	virtual int getLifeSpan() const;
	virtual void onOrphan();
	virtual void wobble();
	virtual bool wasHurt();
	virtual void startSpinAttack();
	virtual void stopSpinAttack();
	virtual void setDamageNearbyMobs(bool);
	virtual void renderDebugServerState(class Options const &);
	virtual void reloadLootTable();
	virtual void reloadLootTable(struct EquipmentTableDescription const *);
	virtual float getDeletionDelayTimeSeconds() const;
	virtual void kill();
	virtual void die(class ActorDamageSource const &);
	virtual bool shouldTick() const;
	virtual void updateEntitySpecificMolangVariables(class RenderParams &);
	virtual bool shouldTryMakeStepSound();
	virtual float getNextStep(float);
	virtual bool canMakeStepSound() const;
	virtual void outOfWorld();
	virtual bool _hurt(class ActorDamageSource const &, int damage, bool knock, bool ignite);
	virtual void markHurt();
	virtual void readAdditionalSaveData(class CompoundTag const &, class DataLoadHelper &);
	virtual void addAdditionalSaveData(class CompoundTag &);
	virtual void _playStepSound(class BlockPos const &, class Block const &);
	virtual void _playFlySound(class BlockPos const &, class Block const &);
	virtual void _makeFlySound() const;
	virtual void checkInsideBlocks(float);
	virtual void pushOutOfBlocks(class Vec3 const &);
	virtual bool updateWaterState();
	virtual void doWaterSplashEffect();
	virtual void spawnTrailBubbles();
	virtual void updateInsideBlock();
	virtual class LootTable *getLootTable();
	virtual class LootTable *getDefaultLootTable();
	virtual void _removeRider(struct ActorUniqueID const &, bool, bool, bool);
	virtual void _onSizeUpdated();
	virtual void _doAutoAttackOnTouch(Actor &);

	MCAPI bool isRiding() const;
	MCAPI bool isRider(class Actor const &) const;
	MCAPI bool isUnderWaterfall() const;
	MCAPI bool isInsideBorderBlock(float) const;
	MCAPI bool isControlledByLocalInstance() const;
	MCAPI bool isWithinRestriction(class BlockPos const &) const;
	MCAPI int getSkinID() const;
	MCAPI int getVariant() const;
	MCAPI int getStrength() const;
	MCAPI int getMarkVariant() const;
	MCAPI int getControllingSeat();
	MCAPI ActorRuntimeID getRuntimeID() const;
	MCAPI int getRiderIndex(class Actor &) const;
	MCAPI int getStructuralIntegrity() const;
	MCAPI class Vec3 getViewVector(float) const;
	MCAPI enum PaletteColor getColor() const;
	MCAPI enum PaletteColor getColor2() const;
	MCAPI struct ActorUniqueID const getOwnerId() const;
	MCAPI bool getStatusFlag(enum ActorFlags) const;
	MCAPI std::vector<struct ActorLink> getLinks() const;
	MCAPI std::unique_ptr<class CompoundTag> getPersistingTradeOffers();
	MCAPI class Actor *getTarget() const;
	MCAPI class Mob *getOwner() const;
	MCAPI class Actor *getRideRoot() const;
	MCAPI class Player *getTradingPlayer() const;
	MCAPI class Player *getPlayerOwner() const;
	MCAPI class ITickingArea *getTickingArea();
	MCAPI class MerchantRecipeList *getTradeOffers();
	MCAPI class MobEffectInstance const *getEffect(class MobEffect const &) const;
	MCAPI struct ActorUniqueID const &getUniqueID() const;
	MCAPI void setSkinID(int);
	MCAPI void setCanFly(bool);
	MCAPI void setHurtDir(int);
	MCAPI void setVariant(int);
	MCAPI void setHurtTime(int);
	MCAPI void setStrength(int);
	MCAPI void setCanClimb(bool);
	MCAPI void setPersistent();
	MCAPI void setInvisible(bool);
	MCAPI void setInLove(class Actor *);
	MCAPI void setLimitedLife(int);
	MCAPI void setMarkVariant(int);
	MCAPI void setStrengthMax(int);
	MCAPI void setJumpDuration(int);
	MCAPI void setStructuralIntegrity(int);
	MCAPI void setColor(enum PaletteColor);
	MCAPI void setColor2(enum PaletteColor);
	MCAPI void setTradingPlayer(class Player *);
	MCAPI void setLeashHolder(struct ActorUniqueID);
	MCAPI bool setStatusFlag(enum ActorFlags, bool);
	MCAPI void setActorRendererId(class HashedString);
	MCAPI void setPreviousPosRot(class Vec3 const &, class Vec2 const &);
	MCAPI void setSeatDescription(class Vec3 const &, struct SeatDescription const &);
	MCAPI void setBaseDefinition(struct ActorDefinitionIdentifier const &, bool, bool);
	MCAPI bool hasPlayerRider() const;
	MCAPI bool hasRestriction() const;
	MCAPI bool hasSubBBInLava() const;
	MCAPI bool hasTickingArea() const;
	MCAPI bool hasEffect(class MobEffect const &) const;
	MCAPI bool hasFamily(class HashedString const &) const;
	MCAPI bool hasTag(std::string const &) const;
	MCAPI void addEffect(class MobEffectInstance const &);
	MCAPI bool addTag(std::string const &);
	MCAPI void removeEffect(int);
	MCAPI void removeAllEffects();
	MCAPI void removeAllRiders(bool, bool);
	MCAPI void removeEffectParticles();
	MCAPI void updateDescription();
	MCAPI void updateTickingData();
	MCAPI void updateBBFromDescription();
	MCAPI void updateInvisibilityStatus();
	MCAPI void updateInBubbleColumnState();
	MCAPI void moveTo(class Vec3 const &, class Vec2 const &);
	MCAPI void teleportRidersTo(class Vec3 const &, int, int);
	MCAPI void saveEntityFlags(class CompoundTag &);
	MCAPI std::unique_ptr<class ListTag> saveLinks() const;
	MCAPI void savePersistingTrade(std::unique_ptr<class CompoundTag>, int);
	MCAPI bool canCurrentlySwim() const;
	MCAPI bool canBeginOrContinueClimbingLadder(bool) const;
	MCAPI void spawnDeathParticles();
	MCAPI void spawnDustParticles(int);
	MCAPI void spawnTamingParticles(bool);
	MCAPI void spawnBalloonPopParticles();
	MCAPI void spawnEatParticles(class ItemStack const &, int);
	MCAPI void sendMotionToServer();
	MCAPI void sendActorDefinitionEventTriggered(std::string const &);
	MCAPI void _sendDirtyActorData();
	//MCAPI void forEachLeashedActor(class std::function<void (class gsl::not_null<class Actor* >)>);
	MCAPI bool shouldOrphan(class BlockSource &);
	MCAPI bool onLadder() const;
	MCAPI void reload();
	MCAPI bool moveChunks();
	MCAPI void dropLeash(bool, bool);
	MCAPI void moveBBs(class Vec3 const &);
	MCAPI void positionAllRiders();
	MCAPI bool pullInEntity(class Actor &);
	MCAPI bool _tryPlaceAt(class Vec3 const &);
	MCAPI bool tick(class BlockSource &);
	MCAPI class Vec3 _randomHeartPos();
	MCAPI void pickUpItem(class ItemActor &, int);
	MCAPI int calculateAttackDamage(class Actor &);
	MCAPI bool hurt(class ActorDamageSource const &, int damage, bool knock, bool ignite);
	MCAPI void dropTowards(class ItemStack const &, class Vec3);
	MCAPI void transferTickingArea(class Dimension &);
	MCAPI void initEntity(class EntityRegistryOwned &);
	MCAPI void playSound(enum LevelSoundEvent, class Vec3 const &, int);
	MCAPI void pushBackActionEventToActionQueue(class ActionEvent);
	MCAPI void loadEntityFlags(class CompoundTag const &, class DataLoadHelper &);
	MCAPI void testForCollidableMobs(class BlockSource &, class AABB const &, std::vector<class AABB> &);
	MCAPI std::vector<struct DistanceSortedActor> fetchNearbyActorsSorted(class Vec3 const &, enum ActorType);
	MCAPI class ItemStack const& getOffhandSlot() const;
	MCAPI class BlockPos getBlockPosCurrentlyStandingOn() const; // use getBlockPosGrounded instead
	MCAPI class FishingHook* fetchFishingHook();

	template <typename T> MCAPI T *tryGetComponent();
	template <typename T> MCAPI T const *tryGetComponent() const;

	// custom methods
	inline std::string getEntityName() const {
		return CallServerFunction<std::string>(
			"?getEntityName@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBVActor@@@Z", this);
	}

	inline void teleport(Vec3 destination, Vec3 const &facePosition, AutomaticID<Dimension, int> destinationDimension,
		RelativeFloat yaw = {0}, RelativeFloat pitch = {0}, int commandVersion = 0, ActorUniqueID const &id = ActorUniqueID::INVALID_ID) {
		CallServerFunction<void>(
			"?teleport@TeleportCommand@@SAXAEAVActor@@VVec3@@PEAV3@V?$AutomaticID@VDimension@@H@@VRelativeFloat@@4HAEBUActorUniqueID@@@Z",
			this, destination, &facePosition, destinationDimension, yaw, pitch, commandVersion, &id);
	}

	inline AttributeInstance &getAttributeInstance(AttributeID id) const {
		return this->mAttributes->getInstance(id);
	}

	inline float getHealth() const {
		return this->getAttributeInstance(AttributeID::Health).mCurrentValue;
	}

	inline float getAbsorption() const {
		return this->getAttributeInstance(AttributeID::Absorption).mCurrentValue;
	}

	inline int32_t getHealthAsInt() const {
		return static_cast<int32_t>(this->getHealth());
	}

	inline int32_t getAbsorptionAsInt() const {
		return static_cast<int32_t>(this->getAbsorption());
	}

	inline bool hasAnyEffects() const {
		if (this->mMobEffects.empty()) return false;
		for (const auto& effect : this->mMobEffects) {
			if (effect != MobEffectInstance::NO_EFFECT) return true;
		}
		return false;
	}

	inline bool hasCategory(ActorCategory category) const {
		return this->mCategories & static_cast<uint32_t>(category);
	}

	inline bool isInstanceOfMob() const {
		return this->hasCategory(ActorCategory::Mob);
	}

	inline bool isInstanceOfPlayer() const {
		return this->hasCategory(ActorCategory::Player);
	}

	inline bool hasRider() const {
		return !this->mRiderIDs.empty();
	}

	inline class Actor* getRide() const {
		if (this->mRidingID.value == -1) { return nullptr; }
		return this->mLevel->fetchEntity(this->mRidingID, false);
	}

	// the pos delta for the mob's position delta in its state vector seems to be inconsistent,
	// so I think its better to calculate manually
	// only use this on non-player entities, for players use getRawPlayerPosDelta()
	inline class Vec3 getRawActorPosDelta() const {
		return this->getPos() - this->getPosOld();
	}

	inline class Vec3 getPosGrounded() const {
		const auto& aabb = this->mAABBComponent.mAABB;
		auto ride = this->getRide();

		float yNew{};
		if (ride) {
			yNew = std::max(aabb.min.y, ride->mAABBComponent.mAABB.min.y);
		}
		else {
			yNew = aabb.min.y;
		}

		const auto& pos = this->getPos();
		return Vec3{pos.x, yNew, pos.z};
	}

	inline class BlockPos getBlockPos() const {
		return BlockPos(this->getPos());
	}

	inline class BlockPos getBlockPosGrounded() const {
		return BlockPos(this->getPosGrounded());
	}

	// actor fields
	//CLASS_FIELD(mEntity, 0x8, class OwnerPtrT<class EntityRefTraits>); // stupid entt component bloat
	CLASS_FIELD(mInitMethod, 0x20, enum InitializationMethod);
	CLASS_FIELD(mCustomInitEventName, 0x28, std::string);
	CLASS_FIELD(mInitParams, 0x48, class VariantParameterList);
	CLASS_FIELD(mForceInitMethodToSpawnOnReload, 0xC8, bool);
	CLASS_FIELD(mDimensionId, 0xCC, enum DimensionID); // xref: Actor::getDimensionId, class AutomaticID<class Dimension, int>
	CLASS_FIELD(mAdded, 0xD0, bool);
	CLASS_FIELD(mDefinitions, 0xD8, class ActorDefinitionGroup *);
	CLASS_FIELD(mCurrentDescription, 0xE0, std::unique_ptr<class ActorDefinitionDescriptor>);
	CLASS_FIELD(mUniqueID, 0xE8, struct ActorUniqueID); // maps to Actor::getUniqueID(), but use Actor::getUniqueID() instead
	CLASS_FIELD(mLeashRopeSystem, 0xF0, std::shared_ptr<class RopeSystem>);
	CLASS_FIELD(mRot, 0x100, class Vec2);
	CLASS_FIELD(mRotPrev, 0x108, class Vec2);
	CLASS_FIELD(mSwimAmount, 0x110, float);
	CLASS_FIELD(mSwimPrev, 0x114, float);
	CLASS_FIELD(mChunkPos, 0x118, class ChunkPos);
	CLASS_FIELD(mRenderPos, 0x120, class Vec3);
	CLASS_FIELD(mRenderRot, 0x12C, class Vec2);
	CLASS_FIELD(mAmbientSoundTime, 0x134, int32_t);
	CLASS_FIELD(mLastHurtByPlayerTime, 0x138, int32_t);
	CLASS_FIELD(mCategories, 0x13C, uint32_t); // bit flags for enum ActorCategory
	CLASS_FIELD(mEntityData, 0x140, class SynchedActorData); // xref: ServerPlayer::handleActorPickRequestOnServer
	CLASS_FIELD(mNetworkData, 0x160, std::unique_ptr<class SpatialActorNetworkData>);
	CLASS_FIELD(mSentDelta, 0x168, class Vec3);
	CLASS_FIELD(mScale, 0x174, float);
	CLASS_FIELD(mScalePrev, 0x178, float);
	CLASS_FIELD(mNameTagHash, 0x180, uint64_t);
	CLASS_FIELD(mInsideBlock, 0x188, const class Block *);
	CLASS_FIELD(mInsideBlockPos, 0x190, class BlockPos);
	CLASS_FIELD(mFallDistance, 0x19C, float);
	CLASS_FIELD(mOnGround, 0x1A0, bool);
	CLASS_FIELD(mWasOnGround, 0x1A1, bool);
	CLASS_FIELD(mHorizontalCollision, 0x1A2, bool);
	CLASS_FIELD(mVerticalCollision, 0x1A3, bool);
	CLASS_FIELD(mCollision, 0x1A4, bool);
	CLASS_FIELD(mIgnoreLighting, 0x1A5, bool);
	CLASS_FIELD(mFilterLighting, 0x1A6, bool);
	CLASS_FIELD(mTintColor, 0x1A8, class Color);
	CLASS_FIELD(mTintColor2, 0x1B8, class Color);
	CLASS_FIELD(mStepSoundVolume, 0x1C8, float);
	CLASS_FIELD(mStepSoundPitch, 0x1CC, float);
	CLASS_FIELD(mLastHitBB, 0x1D0, class AABB *);
	CLASS_FIELD(mSubBBs, 0x1D8, std::vector<class AABB>); // presumably for ender dragon?
	CLASS_FIELD(mTerrainSurfaceOffset, 0x1F0, float);
	CLASS_FIELD(mHeightOffset, 0x1F4, float); // 1.62001 for players
	CLASS_FIELD(mExplosionOffset, 0x1F8, float);
	CLASS_FIELD(mShadowOffset, 0x1FC, float);
	CLASS_FIELD(mMaxAutoStep, 0x200, float);
	CLASS_FIELD(mPushthrough, 0x204, float);
	CLASS_FIELD(mWalkDistPrev, 0x208, float);
	CLASS_FIELD(mWalkDist, 0x20C, float);
	CLASS_FIELD(mMoveDist, 0x210, float);
	CLASS_FIELD(mBlockMovementSlowdownMultiplier, 0x214, float);
	CLASS_FIELD(mNextStep, 0x218, float);
	CLASS_FIELD(mImmobile, 0x21C, bool);
	CLASS_FIELD(mWasInWater, 0x21D, bool);
	CLASS_FIELD(mHasEnteredWater, 0x21E, bool);
	CLASS_FIELD(mHeadInWater, 0x21F, bool);
	CLASS_FIELD(mIsWet, 0x220, bool);
	CLASS_FIELD(mSlideOffset, 0x224, class Vec2);
	CLASS_FIELD(mHeadOffset, 0x22C, class Vec3);
	CLASS_FIELD(mEyeOffset, 0x238, class Vec3);
	CLASS_FIELD(mBreathingOffset, 0x244, class Vec3);
	CLASS_FIELD(mMouthOffset, 0x250, class Vec2);
	CLASS_FIELD(mDropOffset, 0x25C, class Vec3);
	CLASS_FIELD(mFirstTick, 0x268, bool);
	CLASS_FIELD(mTickCount, 0x26C, int32_t);
	CLASS_FIELD(mInvulnerableTime, 0x270, int32_t);
	CLASS_FIELD(mLastHealth, 0x274, int32_t);
	CLASS_FIELD(mFallDamageImmune, 0x278, bool);
	CLASS_FIELD(mHurtMarked, 0x279, bool);
	CLASS_FIELD(mWasHurtLastFrame, 0x27A, bool);
	CLASS_FIELD(mInvulnerable, 0x27B, bool);
	CLASS_FIELD(mOnFireTicks, 0x27C, int32_t);
	CLASS_FIELD(mFlameTexFrameIndex, 0x280, int32_t);
	CLASS_FIELD(mClientSideFireTransitionStartTick, 0x284, int32_t);
	CLASS_FIELD(mFlameFrameIncrementTime, 0x288, float);
	CLASS_FIELD(mOnHotBlock, 0x28C, bool);
	CLASS_FIELD(mClientSideFireTransitionLatch, 0x28D, bool);
	CLASS_FIELD(mAlwaysFireImmune, 0x28E, bool);
	CLASS_FIELD(mPortalCooldown, 0x290, int32_t);
	CLASS_FIELD(mPortalBlockPos, 0x294, class BlockPos);
	CLASS_FIELD(mPortalEntranceAxis, 0x2A0, enum PortalAxis);
	CLASS_FIELD(mInsidePortalTime, 0x2A4, int32_t);
	CLASS_FIELD(mRiderIDs, 0x2A8, std::vector<struct ActorUniqueID>);
	CLASS_FIELD(mRiderIDsToRemove, 0x2C0, std::vector<struct ActorUniqueID>);
	CLASS_FIELD(mRidingID, 0x2D8, struct ActorUniqueID);
	CLASS_FIELD(mRidingPrevID, 0x2E0, struct ActorUniqueID);
	CLASS_FIELD(mPushedByID, 0x2E8, struct ActorUniqueID);
	CLASS_FIELD(mInheritRotationWhenRiding, 0x2F0, bool);
	CLASS_FIELD(mRidersChanged, 0x2F1, bool);
	CLASS_FIELD(mBlocksBuilding, 0x2F2, bool);
	CLASS_FIELD(mUsesOneWayCollision, 0x2F3, bool);
	CLASS_FIELD(mForcedLoading, 0x2F4, bool);
	CLASS_FIELD(mPrevPosRotSetThisTick, 0x2F5, bool);
	CLASS_FIELD(mTeleportedThisTick, 0x2F6, bool);
	CLASS_FIELD(mForceSendMotionPacket, 0x2F7, bool);
	CLASS_FIELD(mSoundVolume, 0x2F8, float);
	CLASS_FIELD(mShakeTime, 0x2FC, int32_t); // for arrows
	CLASS_FIELD(mWalkAnimSpeedMultiplier, 0x300, float); // set to 1.5x when hurt
	CLASS_FIELD(mWalkAnimSpeedO, 0x304, float);
	CLASS_FIELD(mWalkAnimSpeed, 0x308, float);
	CLASS_FIELD(mWalkAnimPos, 0x30C, float);
	//CLASS_FIELD(mLegacyUniqueID, 0x310, struct ActorUniqueID); // DO NOT USE THIS, use the getter/mUniqueID instead
	CLASS_FIELD(mHighlightedThisFrame, 0x318, bool);
	CLASS_FIELD(mInitialized, 0x319, bool);
	CLASS_FIELD(mRegion, 0x320, class BlockSource *); // xref: Actor::_getBlockWhenClimbing
	CLASS_FIELD(mDimension, 0x328, class Dimension *); // xref: PlayerCommandOrigin::getDimension
	CLASS_FIELD(mLevel, 0x330, class Level *);
	CLASS_FIELD(mActorRendererId, 0x338, class HashedString);
	CLASS_FIELD(mActorRendererIdThatAnimationComponentWasInitializedWith, 0x360, class HashedString); // yes this is the actual name
	CLASS_FIELD(mChanged, 0x388, bool);
	CLASS_FIELD(mRemoved, 0x389, bool); // probably died on this tick
	CLASS_FIELD(mGlobal, 0x38A, bool);
	CLASS_FIELD(mAutonomous, 0x38B, bool);
	CLASS_FIELD(mActorType, 0x38C, enum ActorType);
	CLASS_FIELD(mActorIdentifier, 0x390, struct ActorDefinitionIdentifier);
	CLASS_FIELD(mAttributes, 0x438, std::unique_ptr<class BaseAttributeMap>);
	CLASS_FIELD(mEconomyTradeableComponent, 0x440, std::unique_ptr<class EconomyTradeableComponent>);
	CLASS_FIELD(mAnimationComponent, 0x448, std::shared_ptr<class AnimationComponent>);
	CLASS_FIELD(mAABBComponent, 0x458, class AABBShapeComponent);
	CLASS_FIELD(mStateVectorComponent, 0x47C, struct StateVectorComponent);
	CLASS_FIELD(mTargetId, 0x4A0, struct ActorUniqueID);
	CLASS_FIELD(mRestrictRadius, 0x4A8, float);
	CLASS_FIELD(mRestrictCenter, 0x4AC, class BlockPos);
	CLASS_FIELD(mInLovePartner, 0x4B8, struct ActorUniqueID);
	CLASS_FIELD(mMobEffects, 0x4C0, std::vector<class MobEffectInstance>);
	CLASS_FIELD(mEffectsDirty, 0x4D8, bool);
	CLASS_FIELD(mLootDropped, 0x4D9, bool);
	CLASS_FIELD(mPersistingTrade, 0x4DA, bool);
	CLASS_FIELD(mPersistingTradeOffers, 0x4E0, std::unique_ptr<class CompoundTag>);
	CLASS_FIELD(mPersistingTradeRiches, 0x4E8, int32_t);
	CLASS_FIELD(mRuntimeID, 0x4F0, class ActorRuntimeID);
	CLASS_FIELD(mHurtColor, 0x4F8, class Color); // r 1.0, g 0.0, b 0.0, a 0.6
	CLASS_FIELD(mDefinitionList, 0x508, std::unique_ptr<class ActorDefinitionDiffList>);
	CLASS_FIELD(mHasLimitedLife, 0x510, bool);
	CLASS_FIELD(mEnforceRiderRotationLimit, 0x511, bool);
	CLASS_FIELD(mIsStuckItem, 0x512, bool);
	CLASS_FIELD(mIsSafeToSleepNear, 0x513, bool);
	CLASS_FIELD(mLimitedLifeTicks, 0x514, int32_t);
	CLASS_FIELD(mForceVisibleTimerTicks, 0x518, int32_t);
	CLASS_FIELD(mRidingExitDistance, 0x51C, float);
	CLASS_FIELD(mFilteredNameTag, 0x520, std::string); // idk why but this is always empty for players
	CLASS_FIELD(mTerrainInterlockData, 0x540, class ActorTerrainInterlockData);
	CLASS_FIELD(mArmorDropChance, 0x558, std::array<float, 4>); // actually a c array, default: 25% for each armor piece
	CLASS_FIELD(mHandDropChance, 0x568, std::array<float, 2>); // actually a c array, default: 25% chance for mainhand and offhand
	CLASS_FIELD(mIsKnockedBackOnDeath, 0x570, bool); // does not work on players
	CLASS_FIELD(mUpdateEffects, 0x571, bool);
	CLASS_FIELD(mArmorContainer, 0x578, std::unique_ptr<class SimpleContainer>); // xref: Actor::Actor
	CLASS_FIELD(mHandContainer, 0x580, std::unique_ptr<class SimpleContainer>); // xref: Actor::Actor
	CLASS_FIELD(mOnewayPhysicsBlocks, 0x588, std::vector<class AABB>);
	CLASS_FIELD(mStuckInCollider, 0x5A0, bool);
	CLASS_FIELD(mPenetratingLastFrame, 0x5A1, bool);
	CLASS_FIELD(mCollidableMobNear, 0x5A2, bool);
	CLASS_FIELD(mCollidableMob, 0x5A3, bool);
	CLASS_FIELD(mCanPickupItems, 0x5A4, bool);
	CLASS_FIELD(mHasSetCanPickupItems, 0x5A5, bool);
	CLASS_FIELD(mChainedDamageEffects, 0x5A6, bool);
	CLASS_FIELD(mWasInBubbleColumn, 0x5A7, bool);
	CLASS_FIELD(mIsExperimental, 0x5A8, bool);
	CLASS_FIELD(mWasInWallLastTick, 0x5A9, bool);
	CLASS_FIELD(mTicksInWall, 0x5AC, int32_t);
	CLASS_FIELD(mDamageNearbyMobsTick, 0x5B0, int32_t); // riptide / spin attack
	CLASS_FIELD(mSpawnRulesEnum, 0x5B4, enum SpawnRuleEnum);
	CLASS_FIELD(mActionQueue, 0x5B8, std::unique_ptr<class ActionQueue>);
	CLASS_FIELD(mMolangVariables, 0x5C0, class MolangVariableMap);
	CLASS_FIELD(mCachedComponentData, 0x600, class CompoundTag);
	CLASS_FIELD(mFishingHookID, 0x618, struct ActorUniqueID); // when player casts fishing hook
};

// CLASS SIZE RANGES:
// account for vtables at start of each class (8 bytes), then first field after
// ACTOR: 0x0 - 0x620
// MOB: 0x620 - 0x7D0
// PLAYER: 0x7D0 - 0x1F10
// SERVERPLAYER: 0x1F10 - 0x21C0