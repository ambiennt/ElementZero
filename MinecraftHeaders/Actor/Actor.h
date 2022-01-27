#pragma once

#include <cstdint>

#include "ActorRuntimeID.h"
#include "ActorType.h"
#include "ActorUniqueID.h"
#include "SynchedActorData.h"
#include "Attribute.h"
#include "../Math/Vec3.h"
#include "../Container/SimpleContainer.h"
#include "../Core/AutomaticID.h"
#include "../Core/Util.h"
#include "../Core/RelativeFloat.h"
#include "../Command/CommandPermissionLevel.h"
#include "../Level/Level.h"
#include "../dll.h"

#include <hook.h>
#include <modutils.h>

class Dimension;
enum class ActorType;
enum class MaterialType;
enum class ActorEvent;
enum class ActorDamageCause;
enum class ItemUseMethod;
enum class LevelSoundEvent;
enum class InputMode;

enum class SpawnRuleEnum {
	Undefined     = -1,
	NoSpawnRules  = 0,
	HasSpawnRules = 1
};

enum class PortalAxis {
	Unknown = 0,
	X       = 1,
	Z       = 2,
	Count   = 3
};

enum class ArmorMaterialType {
	None                  = -1,
	DefaultArmor          = 0,
	EnchantedArmor        = 1,
	LeatherArmor          = 2,
	EnchantedLeatherArmor = 3
};

enum class ArmorTextureType {
	None      = -1,
	Leather   = 0,
	Chain     = 1,
	Iron      = 2,
	Diamond   = 3,
	Gold      = 4,
	Elytra    = 5,
	Turtle    = 6,
	Netherite = 7
};

enum class ActorLocation {
	Feet               = 0,
	Body               = 1,
	WeaponAttachPoint  = 2,
	Head               = 3,
	DropAttachPoint    = 4,
	ExplosionPoint     = 5,
	Eyes               = 6,
	BreathingPoint     = 7,
	Mouth              = 8
};

enum class PaletteColor {
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
	PaletteColorCount  = 16
};

enum class ArmorSlot {
	Head             = 0,
	Torso            = 1,
	Legs             = 2,
	Feet             = 3,
	SlotCount        = 4
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
	NoAI                        = 16, //Immobile flag
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
	Count                       = 95
};

class Actor {

public:
	enum class InitializationMethod {
		INVALID          = 0,
		LOADED           = 1,
		SPAWNED          = 2,
		BORN             = 3,
		TRANSFORMED      = 4,
		UPDATED          = 5,
		EVENT            = 6,
		LEGACY           = 7
	};

	virtual bool hasComponent(class HashedString const &) const;
	virtual void reloadHardcoded(enum InitializationMethod, class VariantParameterList const &);
	virtual void reloadHardcodedClient(enum InitializationMethod, class VariantParameterList const &);
	virtual void initializeComponents(enum InitializationMethod, class VariantParameterList const &);
	virtual void reloadComponents(enum InitializationMethod, class VariantParameterList const &);
	virtual void _serverInitItemStackIds(void);
	virtual void _doInitialMove(void);
	virtual ~Actor();
	virtual void reset(void);
	virtual int getOnDeathExperience(void);
	virtual enum ActorType getOwnerEntityType(void);
	virtual void remove(void);
	virtual void setPos(class Vec3 const &);
	virtual class Vec3 const &getPos(void) const;
	virtual class Vec3 const &getPosOld(void) const;
	virtual class Vec3 const getPosExtrapolated(float) const;
	virtual class Vec3 getAttachPos(enum ActorLocation, float) const;
	virtual class Vec3 getFiringPos(void) const;
	virtual void setRot(class Vec2 const &);
	virtual void move(class Vec3 const &);
	virtual class Vec3 getInterpolatedRidingPosition(float) const;
	virtual float getInterpolatedBodyRot(float) const;
	virtual float getInterpolatedHeadRot(float) const;
	virtual float getInterpolatedBodyYaw(float) const;
	virtual float getYawSpeedInDegreesPerSecond(void) const;
	virtual float getInterpolatedWalkAnimSpeed(float) const;
	virtual class Vec3 getInterpolatedRidingOffset(float) const;
	virtual void checkBlockCollisions(class AABB const &);
	virtual void checkBlockCollisions();
	virtual bool isFireImmune(void) const;
	virtual void breaksFallingBlocks() const;
	virtual void blockedByShield(class ActorDamageSource const &, class Actor &);
	virtual void moveRelative(float, float, float, float);
	virtual void teleportTo(class Vec3 const &pos, bool shouldStopRiding, int cause, int entityType, struct ActorUniqueID const &destinationEntityId); // cause, entityType, and destinationEntityId are unused
	virtual bool tryTeleportTo(class Vec3 const &pos, bool landOnBlock, bool avoidLiquid, int cause, int entityType); // cause and entityType are unused
	virtual void chorusFruitTeleport(class Vec3 &);
	virtual void lerpTo(class Vec3 const &, class Vec2 const &, int);
	virtual void lerpMotion(class Vec3 const &);
	virtual std::unique_ptr<class AddActorBasePacket> getAddPacket(void);
	virtual void normalTick(void);
	virtual void baseTick(void);
	virtual void rideTick(void);
	virtual void positionRider(class Actor &, float);
	virtual float getRidingHeight(void);
	virtual bool startRiding(class Actor &);
	virtual void addRider(class Actor &);
	virtual void flagRiderToRemove(class Actor &);
	virtual std::string getExitTip(std::string const &, enum InputMode) const;
	virtual bool intersects(class Vec3 const &, class Vec3 const &) const;
	virtual bool isFree(class Vec3 const &, float);
	virtual bool isFree(class Vec3 const &);
	virtual bool isInWall(void) const;
	virtual bool isInvisible(void) const;
	virtual bool canShowNameTag() const;
	virtual bool canExistInPeaceful() const;
	virtual void setNameTagVisible(bool);
	virtual std::string const &getNameTag(void) const;
	virtual unsigned __int64 getNameTagAsHash(void) const;
	virtual std::string getFormattedNameTag(void) const;
	virtual void filterFormattedNameTag(class UIProfanityContext const &);
	virtual void setNameTag(std::string const &);
	virtual bool getAlwaysShowNameTag() const;
	virtual void setScoreTag(std::string const &);
	virtual std::string const &getScoreTag(void) const;
	virtual bool isInWater(void) const;
	virtual bool hasEnteredWater(void) const;
	virtual bool isImmersedInWater(void) const;
	virtual bool isInWaterOrRain(void) const;
	virtual bool isInLava(void) const;
	virtual bool isUnderLiquid(enum MaterialType) const;
	virtual bool isOverWater(void) const;
	virtual void makeStuckInBlock(float);
	virtual float getCameraOffset() const;
	virtual float getShadowHeightOffs(void);
	virtual float getShadowRadius(void) const;
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
	virtual bool isImmobile(void) const;
	virtual bool isSilent(void);
	virtual bool isPickable(void);
	virtual bool isFishable() const;
	virtual bool isSleeping(void) const;
	virtual bool isShootable();
	virtual bool isSneaking(void) const;
	virtual void setSneaking(bool);
	virtual bool isBlocking(void) const;
	virtual bool isDamageBlocked(ActorDamageSource const &) const;
	virtual bool isAlive(void) const;
	virtual bool isOnFire(void) const;
	virtual bool isOnHotBlock(void) const;
	virtual bool isCreativeModeAllowed();
	virtual bool isSurfaceMob(void) const;
	virtual bool isTargetable() const;
	virtual bool canAttack(class Actor *, bool) const;
	virtual void setTarget(class Actor *);
	virtual Actor *findAttackTarget();
	virtual bool isValidTarget(Actor *) const;
	virtual bool attack(class Actor &);
	virtual void performRangedAttack(class Actor &, float);
	virtual void adjustDamageAmount(int &) const;
	virtual int getEquipmentCount(void) const;
	virtual void setOwner(struct ActorUniqueID);
	virtual void setSitting(bool);
	virtual void onTame();
	virtual void onFailedTame();
	virtual int getInventorySize(void) const;
	virtual int getEquipSlots(void) const;
	virtual int getChestSlots(void) const;
	virtual void setStanding(bool);
	virtual bool canPowerJump(void) const;
	virtual void setCanPowerJump(bool);
	virtual bool isJumping(void) const;
	virtual bool isEnchanted(void) const;
	virtual void rideJumped();
	virtual void rideLanded(Vec3 const &, Vec3 const &);
	virtual bool shouldRender(void) const;
	virtual bool isInvulnerableTo(class ActorDamageSource const &) const;
	virtual enum ActorDamageCause getBlockDamageCause(class Block const &) const;
	virtual void actuallyHurt(int, class ActorDamageSource const &, bool);
	virtual void animateHurt(void);
	virtual bool doFireHurt(int);
	virtual void onLightningHit(void);
	virtual void onBounceStarted(BlockPos const &, BlockPos const &);
	virtual void feed(int);
	virtual void handleEntityEvent(enum ActorEvent, int);
	virtual float getPickRadius();
	virtual class HashedString const &getActorRendererId(void) const;
	virtual class ItemActor *spawnAtLocation(int, int);
	virtual class ItemActor *spawnAtLocation(int, int, float);
	virtual class ItemActor *spawnAtLocation(class Block const &, int);
	virtual class ItemActor *spawnAtLocation(class Block const &, int, float);
	virtual class ItemActor *spawnAtLocation(class ItemStack const &, float);
	virtual void despawn(void);
	virtual void killed(class Actor &);
	virtual void awardKillScore(Actor &, int);
	virtual void setArmor(enum ArmorSlot, class ItemStack const &);
	virtual class ItemStack const &getArmor(enum ArmorSlot) const;
	virtual enum ArmorMaterialType getArmorMaterialTypeInSlot(enum ArmorSlot) const;
	virtual enum ArmorTextureType getArmorMaterialTextureTypeInSlot(enum ArmorSlot) const;
	virtual float getArmorColorInSlot(enum ArmorSlot, int) const;
	virtual void setEquippedSlot(enum ArmorSlot, int, int);
	virtual void setEquippedSlot(enum ArmorSlot, class ItemStack const &);
	virtual class ItemStack const &getCarriedItem(void) const;
	virtual void setCarriedItem(class ItemStack const &);
	virtual void setOffhandSlot(class ItemStack const &);
	virtual class ItemStack const &getEquippedTotem(void) const;
	virtual bool consumeTotem(void);
	virtual bool save(class CompoundTag &);
	virtual void saveWithoutId(class CompoundTag &);
	virtual bool load(class CompoundTag const &, class DataLoadHelper &);
	virtual void loadLinks(class CompoundTag const &, std::vector<struct ActorLink> &, class DataLoadHelper &);
	virtual enum ActorType getEntityTypeId(void) const;
	virtual class HashedString const &queryEntityRenderer(void) const;
	virtual struct ActorUniqueID getSourceUniqueID() const;
	virtual void setOnFire(int);
	virtual class AABB getHandleWaterAABB(void) const;
	virtual void handleInsidePortal(class BlockPos const &);
	virtual int getPortalCooldown(void) const;
	virtual int getPortalWaitTime() const;
	virtual class AutomaticID<class Dimension, int> getDimensionId(void) const;
	virtual bool canChangeDimensions() const;
	virtual void changeDimension(class AutomaticID<class Dimension, int>, bool);
	virtual void changeDimension(class ChangeDimensionPacket const &);
	virtual struct ActorUniqueID getControllingPlayer(void) const;
	virtual void checkFallDamage(float, bool);
	virtual void causeFallDamage(float);
	virtual void handleFallDistanceOnServer(float, bool);
	virtual void playSynchronizedSound(enum LevelSoundEvent, class Vec3 const &, class Block const &, bool isGlobal);
	virtual void playSynchronizedSound(enum LevelSoundEvent, class Vec3 const &, int data, bool isGlobal);
	virtual void onSynchedDataUpdate(int);
	virtual bool canAddRider(class Actor &) const;
	virtual bool canPickupItem(ItemStack const &) const;
	virtual bool canBePulledIntoVehicle() const;
	virtual bool inCaravan(void) const;
	virtual bool isLeashableType();
	virtual void tickLeash(void);
	virtual void sendMotionPacketIfNeeded(void);
	virtual bool canSynchronizeNewEntity() const;
	virtual void stopRiding(bool, bool, bool);
	virtual void startSwimming(void);
	virtual void stopSwimming(void);
	virtual void buildDebugInfo(std::string &) const;
	virtual enum CommandPermissionLevel getCommandPermissionLevel(void) const;
	virtual class AttributeInstance *getMutableAttribute(class Attribute const &);
	virtual class AttributeInstance const &getAttribute(class Attribute const &) const;
	virtual int getDeathTime(void) const;
	virtual void heal(int);
	virtual bool isInvertedHealAndHarm(void) const;
	virtual bool canBeAffected(int) const;
	virtual bool canBeAffected(class MobEffectInstance const &) const;
	virtual bool canBeAffectedByArrow(class MobEffectInstance const &) const;
	virtual void onEffectAdded(class MobEffectInstance &);
	virtual void onEffectUpdated(class MobEffectInstance const &);
	virtual void onEffectRemoved(class MobEffectInstance &);
	virtual class AnimationComponent &getAnimationComponent(void);
	virtual void openContainerComponent(class Player &);
	virtual void swing(void);
	virtual void useItem(class ItemStack &, enum ItemUseMethod, bool consumeItem);
	virtual bool hasOutputSignal(unsigned char) const;
	virtual int getOutputSignal() const;
	virtual void getDebugText(std::vector<std::string> &);
	virtual float getMapDecorationRotation(void) const;
	virtual float getRiderYRotation(class Actor const &) const;
	virtual float getYHeadRot() const;
	virtual bool isWorldBuilder(void);
	virtual bool isCreative() const;
	virtual bool isAdventure(void) const;
	virtual bool add(class ItemStack &);
	virtual bool drop(class ItemStack const &, bool);
	virtual bool getInteraction(class Player &, class ActorInteraction &, class Vec3 const &);
	virtual bool canDestroyBlock(Block const &) const;
	virtual void setAuxValue(int);
	virtual void setSize(float, float);
	virtual int getLifeSpan(void) const;
	virtual void onOrphan(void);
	virtual void wobble(void);
	virtual bool wasHurt(void);
	virtual void startSpinAttack(void);
	virtual void stopSpinAttack();
	virtual void setDamageNearbyMobs(bool);
	virtual void renderDebugServerState(class Options const &);
	virtual void reloadLootTable(void);
	virtual void reloadLootTable(struct EquipmentTableDescription const *);
	virtual float getDeletionDelayTimeSeconds() const;
	virtual void kill(void);
	virtual void die(class ActorDamageSource const &);
	virtual bool shouldTick(void) const;
	virtual void updateEntitySpecificMolangVariables(class RenderParams &);
	virtual bool shouldTryMakeStepSound(void);
	virtual float getNextStep(float);
	virtual bool canMakeStepSound() const;
	virtual void outOfWorld(void);
	virtual bool _hurt(class ActorDamageSource const &, int, bool, bool);
	virtual void markHurt(void);
	virtual void readAdditionalSaveData(class CompoundTag const &, class DataLoadHelper &);
	virtual void addAdditionalSaveData(class CompoundTag &);
	virtual void _playStepSound(class BlockPos const &, class Block const &);
	virtual void _playFlySound(class BlockPos const &, class Block const &);
	virtual void _makeFlySound() const;
	virtual void checkInsideBlocks(float);
	virtual void pushOutOfBlocks(class Vec3 const &);
	virtual bool updateWaterState(void);
	virtual void doWaterSplashEffect(void);
	virtual void spawnTrailBubbles(void);
	virtual void updateInsideBlock(void);
	virtual class LootTable *getLootTable();
	virtual class LootTable *getDefaultLootTable();
	virtual void _removeRider(struct ActorUniqueID const &, bool, bool, bool);
	virtual void _onSizeUpdated(void);
	virtual void _doAutoAttackOnTouch(Actor &);

	MCAPI bool isRiding(void) const;
	MCAPI bool isRider(class Actor const &) const;
	MCAPI bool isUnderWaterfall(void) const;
	MCAPI bool isInsideBorderBlock(float) const;
	MCAPI bool isControlledByLocalInstance(void) const;
	MCAPI bool isWithinRestriction(class BlockPos const &) const;
	MCAPI int getSkinID(void) const;
	MCAPI int getVariant(void) const;
	MCAPI int getStrength(void) const;
	MCAPI int getMarkVariant(void) const;
	MCAPI int getControllingSeat(void);
	MCAPI ActorRuntimeID getRuntimeID(void) const;
	MCAPI int getRiderIndex(class Actor &) const;
	MCAPI int getStructuralIntegrity(void) const;
	MCAPI class Vec3 getViewVector(float) const;
	MCAPI enum PaletteColor getColor(void) const;
	MCAPI enum PaletteColor getColor2(void) const;
	MCAPI struct ActorUniqueID const getOwnerId(void) const;
	MCAPI bool getStatusFlag(enum ActorFlags) const;
	MCAPI std::vector<struct ActorLink> getLinks(void) const;
	MCAPI std::unique_ptr<class CompoundTag> getPersistingTradeOffers(void);
	MCAPI class Actor *getTarget(void) const;
	MCAPI class Mob *getOwner(void) const;
	MCAPI class Actor *getRideRoot(void) const;
	MCAPI class Player *getTradingPlayer(void) const;
	MCAPI class Player *getPlayerOwner(void) const;
	MCAPI class ITickingArea *getTickingArea(void);
	MCAPI class MerchantRecipeList *getTradeOffers(void);
	MCAPI class MobEffectInstance const *getEffect(class MobEffect const &) const;
	MCAPI struct ActorUniqueID const &getUniqueID(void) const;
	MCAPI void setSkinID(int);
	MCAPI void setCanFly(bool);
	MCAPI void setHurtDir(int);
	MCAPI void setVariant(int);
	MCAPI void setHurtTime(int);
	MCAPI void setStrength(int);
	MCAPI void setCanClimb(bool);
	MCAPI void setPersistent(void);
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
	MCAPI bool hasPlayerRider(void) const;
	MCAPI bool hasRestriction(void) const;
	MCAPI bool hasSubBBInLava(void) const;
	MCAPI bool hasTickingArea(void) const;
	MCAPI bool hasEffect(class MobEffect const &) const;
	MCAPI bool hasFamily(class Util::HashString const &) const;
	MCAPI bool hasTag(std::string const &) const;
	MCAPI void addEffect(class MobEffectInstance const &);
	MCAPI bool addTag(std::string const &);
	MCAPI void removeEffect(int);
	MCAPI void removeAllEffects(void);
	MCAPI void removeAllRiders(bool, bool);
	MCAPI void removeEffectParticles(void);
	MCAPI void updateDescription(void);
	MCAPI void updateTickingData(void);
	MCAPI void updateBBFromDescription(void);
	MCAPI void updateInvisibilityStatus(void);
	MCAPI void updateInBubbleColumnState(void);
	MCAPI void moveTo(class Vec3 const &, class Vec2 const &);
	MCAPI void teleportRidersTo(class Vec3 const &, int, int);
	MCAPI void saveEntityFlags(class CompoundTag &);
	MCAPI std::unique_ptr<class ListTag> saveLinks(void) const;
	MCAPI void savePersistingTrade(std::unique_ptr<class CompoundTag>, int);
	MCAPI bool canCurrentlySwim(void) const;
	MCAPI bool canBeginOrContinueClimbingLadder(bool) const;
	MCAPI void spawnDeathParticles(void);
	MCAPI void spawnDustParticles(int);
	MCAPI void spawnTamingParticles(bool);
	MCAPI void spawnBalloonPopParticles(void);
	MCAPI void spawnEatParticles(class ItemStack const &, int);
	MCAPI void sendMotionToServer(void);
	MCAPI void sendActorDefinitionEventTriggered(std::string const &);
	MCAPI void _sendDirtyActorData(void);
	//MCAPI void forEachLeashedActor(std::function<void(gsl::not_null<class Actor *>)>);
	MCAPI bool shouldOrphan(class BlockSource &);
	MCAPI bool onLadder(bool) const;
	MCAPI void reload(void);
	MCAPI bool moveChunks(void);
	MCAPI void dropLeash(bool, bool);
	MCAPI void moveBBs(class Vec3 const &);
	MCAPI void positionAllRiders(void);
	MCAPI bool pullInEntity(class Actor &);
	MCAPI bool _tryPlaceAt(class Vec3 const &);
	MCAPI bool tick(class BlockSource &);
	MCAPI class Vec3 _randomHeartPos(void);
	MCAPI void pickUpItem(class ItemActor &, int);
	MCAPI int calculateAttackDamage(class Actor &);
	MCAPI bool hurt(class ActorDamageSource const &, int, bool, bool);
	MCAPI void dropTowards(class ItemStack const &, class Vec3);
	MCAPI void transferTickingArea(class Dimension &);
	MCAPI void initEntity(class EntityRegistryOwned &);
	MCAPI void playSound(enum LevelSoundEvent, class Vec3 const &, int);
	MCAPI void pushBackActionEventToActionQueue(class ActionEvent);
	MCAPI void loadEntityFlags(class CompoundTag const &, class DataLoadHelper &);
	MCAPI void testForCollidableMobs(class BlockSource &, class AABB const &, std::vector<class AABB> &);
	MCAPI std::vector<struct DistanceSortedActor> fetchNearbyActorsSorted(class Vec3 const &, enum ActorType);
	//MCAPI const class ItemStack* getOffhandSlot(void) const; // idk why it says undefined symbol

	template <typename T> MCAPI T *tryGetComponent(void);
	template <typename T> MCAPI T const *tryGetComponent(void) const;
	
	// custom methods
	inline std::string getEntityName() const {
		return CallServerFunction<std::string>(
			"?getEntityName@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AEBVActor@@@Z", this);
	}

	inline void teleport(Vec3 destination, Vec3 const &facePosition, AutomaticID<Dimension, int> destinationDimension,
		RelativeFloat yaw = {0}, RelativeFloat pitch = {0}, int commandVersion = 0, ActorUniqueID const &id = ActorUniqueID::INVALID_ID) {
		CallServerClassMethod<void>(
			"?teleport@TeleportCommand@@SAXAEAVActor@@VVec3@@PEAV3@V?$AutomaticID@VDimension@@H@@VRelativeFloat@@4HAEBUActorUniqueID@@@Z",
			this, destination, &facePosition, destinationDimension, yaw, pitch, commandVersion, &id);
	}

	inline ItemStack* getOffhandSlot() const {
		return CallServerClassMethod<ItemStack*>("?getOffhandSlot@Actor@@QEBAAEBVItemStack@@XZ", this);
	}

	inline AttributeInstance* getAttributeInstanceFromId(AttributeIds id) {
		return this->mAttributes->getMutableInstance((uint32_t) id);
	}
	
	// actor fields
	//BUILD_ACCESS_MUT(class OwnerPtrT<class EntityRefTraits>, mEntity, 0x8); // idk what this is, probably some legacy field?
	BUILD_ACCESS_MUT(enum InitializationMethod, mInitMethod, 0x20);
	BUILD_ACCESS_MUT(std::string, mCustomInitEventName, 0x28);
	BUILD_ACCESS_MUT(class VariantParameterList, mInitParams, 0x48);
	BUILD_ACCESS_MUT(bool, mForceInitMethodToSpawnOnReload, 0xC8);

	//using dimensionId = class AutomaticID<class Dimension, int;
	//BUILD_ACCESS_MUT(dimensionId, mDimensionId, 0xCC);
	BUILD_ACCESS_MUT(int32_t, mDimensionId, 0xCC); // its just easier to use an int directly

	BUILD_ACCESS_MUT(bool, mAdded, 0xD0);
	BUILD_ACCESS_MUT(class ActorDefinitionGroup *, mDefinitions, 0xD8);
	BUILD_ACCESS_MUT(std::unique_ptr<class ActorDefinitionDescriptor>, mCurrentDescription, 0xE0);
	BUILD_ACCESS_MUT(struct ActorUniqueID, mUniqueID, 0xE8); // maps to Actor::getUniqueID
	BUILD_ACCESS_MUT(std::shared_ptr<class RopeSystem>, mLeashRopeSystem, 0xF0);
	BUILD_ACCESS_MUT(class Vec2, mRot, 0x100);
	BUILD_ACCESS_MUT(class Vec2, mRotPrev, 0x108);
	BUILD_ACCESS_MUT(float, mSwimAmount, 0x110);
	BUILD_ACCESS_MUT(float, mSwimPrev, 0x114);
	BUILD_ACCESS_MUT(class ChunkPos, mChunkPos, 0x118);
	BUILD_ACCESS_MUT(class Vec3, mRenderPos, 0x120);
	BUILD_ACCESS_MUT(class Vec2, mRenderRot, 0x12C);
	BUILD_ACCESS_MUT(int32_t, mAmbientSoundTime, 0x134);
	BUILD_ACCESS_MUT(int32_t, mLastHurtByPlayerTime, 0x138);

	using uint8Arr4 = uint8_t[4];
	BUILD_ACCESS_MUT(uint8Arr4, mCategories, 0x13C); // _BYTE in ida? idk

	BUILD_ACCESS_MUT(class SynchedActorData, mEntityData, 0x140);
	BUILD_ACCESS_MUT(std::unique_ptr<class SpatialActorNetworkData>, mNetworkData, 0x160);
	BUILD_ACCESS_MUT(class Vec3, mSentDelta, 0x168);
	BUILD_ACCESS_MUT(float, mScale, 0x174);
	BUILD_ACCESS_MUT(float, mScalePrev, 0x178);
	BUILD_ACCESS_MUT(uint64_t, mNameTagHash, 0x180);
	BUILD_ACCESS(const class Block *, mInsideBlock, 0x188);
	BUILD_ACCESS_MUT(class BlockPos, mInsideBlockPos, 0x190);
	BUILD_ACCESS_MUT(float, mFallDistance, 0x19C);
	BUILD_ACCESS_MUT(bool, mOnGround, 0x1A0);
	BUILD_ACCESS_MUT(bool, mWasOnGround, 0x1A1);
	BUILD_ACCESS_MUT(bool, mHorizontalCollision, 0x1A2);
	BUILD_ACCESS_MUT(bool, mVerticalCollision, 0x1A3);
	BUILD_ACCESS_MUT(bool, mCollision, 0x1A4);
	BUILD_ACCESS_MUT(bool, mIgnoreLighting, 0x1A5);
	BUILD_ACCESS_MUT(bool, mFilterLighting, 0x1A6);
	BUILD_ACCESS_MUT(class Color, mTintColor, 0x1A8);
	BUILD_ACCESS_MUT(class Color, mTintColor2, 0x1B8);
	BUILD_ACCESS_MUT(float, mStepSoundVolume, 0x1C8);
	BUILD_ACCESS_MUT(float, mStepSoundPitch, 0x1CC);
	BUILD_ACCESS_MUT(class AABB *, mLastHitBB, 0x1D0);
	BUILD_ACCESS_MUT(std::vector<class AABB>, mSubBBs, 0x1D8); // presumably for ender dragon?
	BUILD_ACCESS_MUT(float, mTerrainSurfaceOffset, 0x1F0);
	BUILD_ACCESS_MUT(float, mHeightOffset, 0x1F4); // 1.620001 for players
	BUILD_ACCESS_MUT(float, mExplosionOffset, 0x1F8);
	BUILD_ACCESS_MUT(float, mShadowOffset, 0x1FC);
	BUILD_ACCESS_MUT(float, mMaxAutoStep, 0x200);
	BUILD_ACCESS_MUT(float, mPushthrough, 0x204);
	BUILD_ACCESS_MUT(float, mWalkDistPrev, 0x208);
	BUILD_ACCESS_MUT(float, mWalkDist, 0x20C);
	BUILD_ACCESS_MUT(float, mMoveDist, 0x210);
	BUILD_ACCESS_MUT(float, mBlockMovementSlowdownMultiplier, 0x214);
	BUILD_ACCESS_MUT(float, mNextStep, 0x218);
	BUILD_ACCESS_MUT(bool, mImmobile, 0x21C);
	BUILD_ACCESS_MUT(bool, mWasInWater, 0x21D);
	BUILD_ACCESS_MUT(bool, mHasEnteredWater, 0x21E);
	BUILD_ACCESS_MUT(bool, mHeadInWater, 0x21F);
	BUILD_ACCESS_MUT(bool, mIsWet, 0x220);
	BUILD_ACCESS_MUT(class Vec2, mSlideOffset, 0x224);
	BUILD_ACCESS_MUT(class Vec3, mHeadOffset, 0x22C);
	BUILD_ACCESS_MUT(class Vec3, mEyeOffset, 0x238);
	BUILD_ACCESS_MUT(class Vec3, mBreathingOffset, 0x244);
	BUILD_ACCESS_MUT(class Vec2, mMouthOffset, 0x250);
	BUILD_ACCESS_MUT(class Vec3, mDropOffset, 0x25C);
	BUILD_ACCESS_MUT(bool, mFirstTick, 0x268);
	BUILD_ACCESS_MUT(int32_t, mTickCount, 0x26C);
	BUILD_ACCESS_MUT(int32_t, mInvulnerableTime, 0x270);
	BUILD_ACCESS_MUT(int32_t, mLastHealth, 0x274);
	BUILD_ACCESS_MUT(bool, mFallDamageImmune, 0x278);
	BUILD_ACCESS_MUT(bool, mHurtMarked, 0x279);
	BUILD_ACCESS_MUT(bool, mWasHurtLastFrame, 0x27A);
	BUILD_ACCESS_MUT(bool, mInvulnerable, 0x27B);
	BUILD_ACCESS_MUT(int32_t, mOnFireTicks, 0x27C);
	BUILD_ACCESS_MUT(int32_t, mFlameTexFrameIndex, 0x280);
	BUILD_ACCESS_MUT(int32_t, mClientSideFireTransitionStartTick, 0x284);
	BUILD_ACCESS_MUT(float, mFlameFrameIncrementTime, 0x288);
	BUILD_ACCESS_MUT(bool, mOnHotBlock, 0x28C);
	BUILD_ACCESS_MUT(bool, mClientSideFireTransitionLatch, 0x28D);
	BUILD_ACCESS_MUT(bool, mAlwaysFireImmune, 0x28E);
	BUILD_ACCESS_MUT(int32_t, mPortalCooldown, 0x290);
	BUILD_ACCESS_MUT(class BlockPos, mPortalBlockPos, 0x294);
	BUILD_ACCESS_MUT(enum PortalAxis, mPortalEntranceAxis, 0x2A0);
	BUILD_ACCESS_MUT(int32_t, mInsidePortalTime, 0x2A4);
	BUILD_ACCESS_MUT(std::vector<struct ActorUniqueID>, mRiderIDs, 0x2A8);
	BUILD_ACCESS_MUT(std::vector<struct ActorUniqueID>, mRiderIDsToRemove, 0x2C0);
	BUILD_ACCESS_MUT(struct ActorUniqueID, mRidingID, 0x2D8);
	BUILD_ACCESS_MUT(struct ActorUniqueID, mRidingPrevID, 0x2E0);
	BUILD_ACCESS_MUT(struct ActorUniqueID, mPushedByID, 0x2E8);
	BUILD_ACCESS_MUT(bool, mInheritRotationWhenRiding, 0x2F0);
	BUILD_ACCESS_MUT(bool, mRidersChanged, 0x2F1);
	BUILD_ACCESS_MUT(bool, mBlocksBuilding, 0x2F2);
	BUILD_ACCESS_MUT(bool, mUsesOneWayCollision, 0x2F3);
	BUILD_ACCESS_MUT(bool, mForcedLoading, 0x2F4);
	BUILD_ACCESS_MUT(bool, mPrevPosRotSetThisTick, 0x2F5);
	BUILD_ACCESS_MUT(bool, mTeleportedThisTick, 0x2F6);
	BUILD_ACCESS_MUT(bool, mForceSendMotionPacket, 0x2F7);
	BUILD_ACCESS_MUT(float, mSoundVolume, 0x2F8);
	BUILD_ACCESS_MUT(int32_t, mShakeTime, 0x2FC); // for arrows
	BUILD_ACCESS_MUT(float, mWalkAnimSpeedMultiplier, 0x300); // set to 1.5x when hurt
	BUILD_ACCESS_MUT(float, mWalkAnimSpeedO, 0x304);
	BUILD_ACCESS_MUT(float, mWalkAnimSpeed, 0x308);
	BUILD_ACCESS_MUT(float, mWalkAnimPos, 0x30C);
	BUILD_ACCESS_MUT(struct ActorUniqueID, mLegacyUniqueID, 0x310);
	BUILD_ACCESS_MUT(bool, mHighlightedThisFrame, 0x318);
	BUILD_ACCESS_MUT(bool, mInitialized, 0x319);
	BUILD_ACCESS_MUT(class BlockSource *, mRegion, 0x320);
	BUILD_ACCESS_MUT(class Dimension *, mDimension, 0x328);
	BUILD_ACCESS_MUT(class Level *, mLevel, 0x330);
	BUILD_ACCESS_MUT(class HashedString, mActorRendererId, 0x338);
	BUILD_ACCESS_MUT(class HashedString,
		mActorRendererIdThatAnimationComponentWasInitializedWith, 0x360); // yes this is the actual name
	BUILD_ACCESS_MUT(bool, mChanged, 0x388);
	BUILD_ACCESS_MUT(bool, mRemoved, 0x389); // probably died on this tick
	BUILD_ACCESS_MUT(bool, mGlobal, 0x38A);
	BUILD_ACCESS_MUT(bool, mAutonomous, 0x38B);
	BUILD_ACCESS_MUT(enum ActorType, mActorType, 0x38C);
	BUILD_ACCESS_MUT(struct ActorDefinitionIdentifier, mActorIdentifier, 0x390);
	BUILD_ACCESS_MUT(std::unique_ptr<class BaseAttributeMap>, mAttributes, 0x438);
	BUILD_ACCESS_MUT(std::unique_ptr<class EconomyTradeableComponent>, mEconomyTradeableComponent, 0x440);
	BUILD_ACCESS_MUT(std::shared_ptr<class AnimationComponent>, mAnimationComponent, 0x448);
	BUILD_ACCESS_MUT(class AABBShapeComponent, mAABBComponent, 0x458);
	BUILD_ACCESS_MUT(struct StateVectorComponent, mStateVectorComponent, 0x47C);
	BUILD_ACCESS_MUT(struct ActorUniqueID, mTargetId, 0x4A0);
	BUILD_ACCESS_MUT(float, mRestrictRadius, 0x4A8);
	BUILD_ACCESS_MUT(class BlockPos, mRestrictCenter, 0x4AC);
	BUILD_ACCESS_MUT(struct ActorUniqueID, mInLovePartner, 0x4B8);
	BUILD_ACCESS_MUT(std::vector<class MobEffectInstance>, mMobEffects, 0x4C0);
	BUILD_ACCESS_MUT(bool, mEffectsDirty, 0x4D8);
	BUILD_ACCESS_MUT(bool, mLootDropped, 0x4D9);
	BUILD_ACCESS_MUT(bool, mPersistingTrade, 0x4DA);
	BUILD_ACCESS_MUT(std::unique_ptr<class CompoundTag>, mPersistingTradeOffers, 0x4E0);
	BUILD_ACCESS_MUT(int32_t, mPersistingTradeRiches, 0x4E8);
	BUILD_ACCESS_MUT(class ActorRuntimeID, mRuntimeID, 0x4F0);
	BUILD_ACCESS_MUT(class Color, mHurtColor, 0x4F8); // r 1.0, g 0.0, b 0.0, a 0.6
	BUILD_ACCESS_MUT(std::unique_ptr<class ActorDefinitionDiffList>, mDefinitionList, 0x508);
	BUILD_ACCESS_MUT(bool, mHasLimitedLife, 0x510);
	BUILD_ACCESS_MUT(bool, mEnforceRiderRotationLimit, 0x511);
	BUILD_ACCESS_MUT(bool, mIsStuckItem, 0x512);
	BUILD_ACCESS_MUT(bool, mIsSafeToSleepNear, 0x513);
	BUILD_ACCESS_MUT(int32_t, mLimitedLifeTicks, 0x514);
	BUILD_ACCESS_MUT(int32_t, mForceVisibleTimerTicks, 0x518);
	BUILD_ACCESS_MUT(float, mRidingExitDistance, 0x51C);
	BUILD_ACCESS_MUT(std::string, mFilteredNameTag, 0x520); // idk why but this is always empty for players
	BUILD_ACCESS_MUT(class ActorTerrainInterlockData, mTerrainInterlockData, 0x540);

	using floatArr4 = float[4];
	BUILD_ACCESS_MUT(floatArr4, mArmorDropChance, 0x558); // default: 25% for each armor piece

	using floatArr2 = float[2];
	BUILD_ACCESS_MUT(floatArr2, mHandDropChance, 0x568); // default: 25% chance for mainhand and offhand

	BUILD_ACCESS_MUT(bool, mIsKnockedBackOnDeath, 0x570); // does not work on players
	BUILD_ACCESS_MUT(bool, mUpdateEffects, 0x571);
	BUILD_ACCESS_MUT(std::unique_ptr<class SimpleContainer>, mArmorContainer, 0x578);
	BUILD_ACCESS_MUT(std::unique_ptr<class SimpleContainer>, mHandContainer, 0x580);
	BUILD_ACCESS_MUT(std::vector<class AABB>, mOnewayPhysicsBlocks, 0x588);
	BUILD_ACCESS_MUT(bool, mStuckInCollider, 0x5A0);
	BUILD_ACCESS_MUT(bool, mPenetratingLastFrame, 0x5A1);
	BUILD_ACCESS_MUT(bool, mCollidableMobNear, 0x5A2);
	BUILD_ACCESS_MUT(bool, mCollidableMob, 0x5A3);
	BUILD_ACCESS_MUT(bool, mCanPickupItems, 0x5A4);
	BUILD_ACCESS_MUT(bool, mHasSetCanPickupItems, 0x5A5);
	BUILD_ACCESS_MUT(bool, mChainedDamageEffects, 0x5A6);
	BUILD_ACCESS_MUT(bool, mWasInBubbleColumn, 0x5A7);
	BUILD_ACCESS_MUT(bool, mIsExperimental, 0x5A8);
	BUILD_ACCESS_MUT(bool, mWasInWallLastTick, 0x5A9);
	BUILD_ACCESS_MUT(int32_t, mTicksInWall, 0x5AC);
	BUILD_ACCESS_MUT(int32_t, mDamageNearbyMobsTick, 0x5B0); // riptide / spin attack
	BUILD_ACCESS_MUT(enum SpawnRuleEnum, mSpawnRulesEnum, 0x5B4);
	BUILD_ACCESS_MUT(std::unique_ptr<class ActionQueue>, mActionQueue, 0x5B8);
	BUILD_ACCESS_MUT(class MolangVariableMap, mMolangVariables, 0x5C0);
	BUILD_ACCESS_MUT(class CompoundTag, mCachedComponentData, 0x600);
	BUILD_ACCESS_MUT(struct ActorUniqueID, mFishingHookID, 0x618); // when player casts fishing hook

	BUILD_ACCESS_COMPAT(SimpleContainer &, EquipmentContainer);
	BUILD_ACCESS_COMPAT(SimpleContainer &, HandContainer);
	BUILD_ACCESS_COMPAT(SynchedActorData &, EntityData);
	BUILD_ACCESS_COMPAT(class Dimension *, Dimension);
};

// CLASS SIZE RANGES:
// account for vtables at start of each class (8 bytes), then first field after
// ACTOR: 0x0 - 0x620
// MOB: 0x620 - 0x7D0
// PLAYER: 0x7D0 - 0x1F10
// SERVERPLAYER: 0x1F10 - 0x21C0