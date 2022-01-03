#pragma once

#include <vector>

#include <hook.h>

#include "Actor.h"
#include "Mob.h"
#include "../Core/ExtendedCertificate.h"
#include "../Container/PlayerInventory.h"
#include "../Container/EnderChestContainer.h"
#include "../Math/Vec3.h"
#include "../Math/BlockPos.h"
#include "../Core/AutomaticID.h"
#include "../Core/VanillaDimensions.h"
#include "../Command/CommandPermissionLevel.h"
#include "../Level/GameType.h"
#include "../Level/Abilities.h"
#include "../dll.h"

class Packet;
class ServerPlayer;
class NetworkIdentifier;
class Dimension;
class IContainerManager;
enum class StructureFeatureType;
enum class ClientPlayMode;
enum class CooldownType;
enum class BuildPlatform;

enum class MovementEventType {
	PositionCorrected = 0,
	BackInSync        = 1
};

enum class InputMode {
	Undefined         = 0,
	Mouse             = 1,
	Touch             = 2,
	GamePad           = 3,
	MotionController  = 4,
	Count             = 5
};

enum class ClientPlayMode {
	Normal               = 0,
	Teaser               = 1,
	Screen               = 2,
	Viewer               = 3,
	Reality              = 4,
	Placement            = 5,
	LivingRoom           = 6, 
	ExitLevel            = 7,
	ExitLevelLivingRoom  = 8,
	NumModes             = 9
};

enum class PlayerUISlot {
	CursorSelected          = 0,
	AnvilInput              = 1,
	AnvilMaterial           = 2,
	StoneCutterInput        = 3,
	Trade2Ingredient1       = 4,
	Trade2Ingredient2       = 5,
	TradeIngredient1        = 6,
	TradeIngredient2        = 7,
	MaterialReducerInput    = 8,
	LoomInput               = 9,
	LoomDye                 = 10,
	LoomMaterial            = 11,
	CartographyInput        = 12,
	CartographyAdditional   = 13,
	EnchantingInput         = 14,
	EnchantingMaterial      = 15,
	GrindstoneInput         = 16,
	GrindstoneAdditional    = 17,
	CompoundCreatorInput1   = 18,
	CompoundCreatorInput2   = 19,
	CompoundCreatorInput3   = 20,
	CompoundCreatorInput4   = 21,
	CompoundCreatorInput5   = 22,
	CompoundCreatorInput6   = 23,
	CompoundCreatorInput7   = 24,
	CompoundCreatorInput8   = 25,
	CompoundCreatorInput9   = 26,
	BeaconPayment           = 27,
	Crafting2x2Input1       = 28,
	Crafting2x2Input2       = 29,
	Crafting2x2Input3       = 30,
	Crafting2x2Input4       = 31,
	Crafting3x3Input1       = 32,
	Crafting3x3Input2       = 33,
	Crafting3x3Input3       = 34,
	Crafting3x3Input4       = 35,
	Crafting3x3Input5       = 36,
	Crafting3x3Input6       = 37,
	Crafting3x3Input7       = 38,
	Crafting3x3Input8       = 39,
	Crafting3x3Input9       = 40,
	MaterialReducerOutput1  = 41,
	MaterialReducerOutput2  = 42,
	MaterialReducerOutput3  = 43,
	MaterialReducerOutput4  = 44,
	MaterialReducerOutput5  = 45,
	MaterialReducerOutput6  = 46,
	MaterialReducerOutput7  = 47,
	MaterialReducerOutput8  = 48,
	MaterialReducerOutput9  = 49,
	CreatedItemOutput       = 50,
	SmithingTableInput      = 51,
	SmithingTableMaterial   = 52
};

enum class BedSleepingResult {
	OK                 = 0,
	NOT_POSSIBLE_HERE  = 1,
	NOT_POSSIBLE_NOW   = 2,
	TOO_FAR_AWAY       = 3,
	OTHER_PROBLEM      = 4,
	NOT_SAFE           = 5
};

#ifndef BASEAPI
#  define BASEAPI __declspec(dllimport)
#endif

class Player : public Mob {
public:
	class PlayerSpawnPoint {
	public:
		inline static BlockPos InvalidSpawnPos = BlockPos::MIN;
		BlockPos spawn_block = InvalidSpawnPos, spawn_pos = InvalidSpawnPos;
		AutomaticID<class Dimension, int> dim = VanillaDimensions::Undefined;

		inline PlayerSpawnPoint()        = default;
		inline PlayerSpawnPoint &operator=(PlayerSpawnPoint &&) = default;
		inline bool hasSpawnPoint() const { return spawn_block != BlockPos::MIN && dim != VanillaDimensions::Undefined; }
		inline void invalidate() { *this = {}; }
		inline bool isValid() const { return dim != VanillaDimensions::Undefined; }
		inline void setSpawnPoint(BlockPos spawn_block, AutomaticID<class Dimension, int> dim, BlockPos spawn_pos) {
			this->spawn_block = spawn_block;
			this->spawn_pos   = spawn_pos;
			this->dim         = dim;
		}
		inline void setSpawnPoint(BlockPos spawn_block, AutomaticID<class Dimension, int> dim) {
			setSpawnPoint(spawn_block, dim, spawn_block);
		}
	};

	struct CachedSpawnData {
		AutomaticID<class Dimension, int> mRespawnDimensionId;
		Vec3 mActualRespawnPosition;
		BlockPos mRequestedRespawnPosition;
		bool mHasRespawnPosition;
		BlockPos mSharedSpawnPosition;
		bool mRespawnReady;
		Vec3 mPlayerPos;
		bool mIsForcedRespawn;
		bool mIsAdventure;
		bool mIsFlyingOrNotOverworld;
		bool mPositionLoadedFromSave;
	};

	inline ServerPlayer *asServerPlayer() const noexcept {
		return const_cast<ServerPlayer *>(reinterpret_cast<ServerPlayer const *>(this));
	}

	enum class SpawnPositionState {
		InitializeSpawnPositionRandomizer = 0,
		WaitForClientAck                  = 1,
		DetermineDimension                = 2,
		ChangeDimension                   = 3,
		WaitForDimension                  = 4,
		ChooseSpawnArea                   = 5,
		CheckLoadedChunk                  = 6,
		ChooseSpawnPosition               = 7,
		SpawnComplete                     = 8,
	};

	enum class PositionMode : uint8_t {
		Normal       = 0,
		Respawn      = 1,
		Teleport     = 2,
		OnlyHeadRot  = 3
	};

	enum class DimensionState {
		Ready                 = 0,
		Pending               = 1,
		WaitingServerResponse = 2,
		WaitingArea           = 3
	};

	virtual void prepareRegion(class ChunkSource &);
	virtual void destroyRegion(void);
	virtual void suspendRegion(void);
	virtual void _fireWillChangeDimension(void);
	virtual void _fireDimensionChanged(void);
	virtual void changeDimensionWithCredits(class AutomaticID<class Dimension, int>);
	virtual int tickWorld(struct Tick const &);
	virtual void frameUpdate(class FrameUpdateContextBase &);
	virtual std::vector<class ChunkPos> const &getTickingOffsets(void) const;
	virtual void moveView(void);
	virtual void setName(std::string const &);
	virtual void checkMovementStats(class Vec3 const &);
	virtual class StructureFeature *getCurrentStructureFeature() const;
	virtual bool isAutoJumpEnabled() const;
	virtual void respawn(void);
	virtual void resetRot();
	virtual void resetPos(bool);
	virtual bool isInTrialMode();
	virtual bool hasResource(int);
	virtual void completeUsingItem(void);
	virtual void setPermissions(enum CommandPermissionLevel);
	virtual void startDestroying(void);
	virtual void stopDestroying(void);
	virtual void openPortfolio();
	virtual void openBook(int, bool, int, BlockActor *);
	virtual void openTrading(struct ActorUniqueID const &, bool);
	virtual bool canOpenContainerScreen(void);
	virtual void openChalkboard(class ChalkboardBlockActor *, bool);
	virtual void openNpcInteractScreen(Actor &);
	virtual void openInventory(void);
	virtual void displayChatMessage(std::string const &, std::string const &);
	virtual void displayClientMessage(std::string const &);
	virtual void displayTextObjectMessage(class TextObjectRoot const &);
	virtual void displayTextObjectWhisperMessage(class TextObjectRoot const &, std::string const &, std::string const &);
	virtual void displayWhisperMessage(std::string const &, std::string const &, std::string const &, std::string const &);
	virtual enum BedSleepingResult startSleepInBed(class BlockPos const &);
	virtual void stopSleepInBed(bool forcefulWakeUp, bool updateLevelList);
	virtual bool canStartSleepInBed(void);
	virtual int getSleepTimer(void) const;
	virtual int getPreviousTickSleepTimer(void) const;
	virtual void openSign(BlockPos const &);
	virtual void playEmote(std::string const &);
	virtual bool isLocalPlayer() const;
	virtual bool isHostingPlayer(void) const;
	virtual bool isLoading(void) const;
	virtual bool isPlayerInitialized(void) const;
	virtual void stopLoading();
	virtual void registerTrackedBoss(struct ActorUniqueID);
	virtual void unRegisterTrackedBoss(struct ActorUniqueID);
	virtual void setPlayerGameType(enum GameType);
	virtual void _crit(class Actor &);
	virtual class IMinecraftEventing *getEventing(void) const;
	virtual unsigned char getUserId();
	virtual void sendEventPacket(class EventPacket &) const;
	virtual void addExperience(int);
	virtual void addLevels(int);
	virtual void setContainerData(class IContainerManager &, int, int);
	virtual void slotChanged(class IContainerManager &, class Container &, int, class ItemStack const &, class ItemStack const &, bool);
	virtual void inventoryChanged(class Container &, int, class ItemStack const &, class ItemStack const &, bool);
	virtual void refreshContainer(class IContainerManager &);
	virtual void deleteContainerManager(void);
	virtual void setFieldOfViewModifier(float);
	virtual bool isPositionRelevant(class AutomaticID<class Dimension, int>, class BlockPos const &);
	virtual bool isEntityRelevant(class Actor const &);
	virtual bool isTeacher(void) const;
	virtual void onSuspension(void);
	virtual void onLinkedSlotsChanged(void);
	virtual void startCooldown(class Item const *);
	virtual int getItemCooldownLeft(enum CooldownType) const;
	virtual bool isItemInCooldown(enum CooldownType) const;
	virtual void sendInventoryTransaction(class InventoryTransaction const &) const;
	virtual void sendComplexInventoryTransaction(std::unique_ptr<class ComplexInventoryTransaction>) const;
	virtual void sendNetworkPacket(class Packet &) const;
	virtual class PlayerEventCoordinator &getPlayerEventCoordinator(void);
	virtual class MoveInputHandler *getMoveInputHandler();
	virtual enum InputMode getInputMode(void) const;
	virtual enum ClientPlayMode getPlayMode(void) const;
	virtual void reportMovementTelemetry(enum MovementEventType);
	virtual void onMovePlayerPacketNormal(class Vec3 const &, class Vec2 const &, float);

	MCAPI bool isInRaid(void) const;
	MCAPI bool isSurvival(void) const;
	MCAPI bool isInCreativeMode(void) const;
	MCAPI bool isHiddenFrom(class Mob &) const;
	MCAPI bool canBeSeenOnMap(void) const;
	MCAPI bool canUseOperatorBlocks(void) const;
	MCAPI bool canDestroy(class Block const &) const;
	MCAPI bool canUseAbility(enum AbilitiesIndex) const;
	MCAPI class Agent *getAgent(void) const;
	MCAPI int getDirection(void) const;
	MCAPI int getXpNeededForNextLevel(void) const;
	MCAPI float getDestroySpeed(class Block const &) const;
	MCAPI float getDestroyProgress(class Block const &) const;
	MCAPI class ItemStack const &getSelectedItem(void) const;
	MCAPI class ItemStack const &getCurrentActiveShield(void) const;
	MCAPI class EnderChestContainer *getEnderChestContainer(void);
	MCAPI void updateTeleportDestPos(void);
	MCAPI void updateInventoryTransactions(void);
	MCAPI void updateSkin(class SerializedSkin const &, int);
	MCAPI void setAgent(class Agent *);
	MCAPI void setRespawnPosition(class BlockPos const &, bool);
	MCAPI void setBedRespawnPosition(class BlockPos const &);
	MCAPI void setPlayerUIItem(enum PlayerUISlot, class ItemStack const &);
	MCAPI void setContainerManager(class std::shared_ptr<class IContainerManager>);
	MCAPI void eat(int, float);
	MCAPI void startUsingItem(class ItemStack const &, int);
	MCAPI void stopUsingItem(void);
	MCAPI void releaseUsingItem(void);
	MCAPI void stopGliding(void);
	MCAPI void resetPlayerLevel(void);
	MCAPI void handleJumpEffects(void);
	MCAPI bool take(class Actor &, int, int);
	MCAPI void updateTrackedBosses(void);
	MCAPI void causeFoodExhaustion(float);
	MCAPI bool checkNeedAutoJump(float, float);
	MCAPI void clearRespawnPosition(void);
	MCAPI void recheckSpawnPosition(void);

	inline class ItemStack const& getPlayerUIItem(void) {
		return CallServerClassMethod<class ItemStack const&>(
			"?getItem@SimpleContainer@@UEBAAEBVItemStack@@H@Z", &direct_access<class SimpleContainer>(this, 0x1078), PlayerUISlot::CursorSelected);
	}

	inline bool dropItem(ItemStack const &item, bool randomly) {
		return CallServerClassMethod<bool>("?drop@Player@@UEAA_NAEBVItemStack@@_N@Z", this, &item, false);
	}

	inline bool addItem(ItemStack &item) {
		return CallServerClassMethod<bool>("?add@Player@@UEAA_NAEAVItemStack@@@Z", this, &item);
	}

	//a more reliable way to get pos delta for players
	inline Vec3 getPosDelta(void) {
		Vec3 posDelta;
		const auto& prevPos = this->getPosOld();
		const auto& currPos = this->getPos();
		posDelta.x = currPos.x - prevPos.x;
		posDelta.y = currPos.y - prevPos.y;
		posDelta.z = currPos.z - prevPos.z;
		return posDelta;
	}

	// some fields still missing
	BUILD_ACCESS_MUT(int32_t, mCastawayTimer, 0x7D0);
	BUILD_ACCESS_MUT(bool, mAteKelp, 0x7D4);
	BUILD_ACCESS_MUT(int32_t, mLastBiome, 0x7D8); // I guess biome ids are ints
	BUILD_ACCESS_MUT(std::vector<int32_t>, mOceanBiomes, 0x7E0);
	BUILD_ACCESS_MUT(bool, mCastawaySent, 0x7F8);
	BUILD_ACCESS_MUT(enum Player::DimensionState, mDimensionState, 0x7FC);
	BUILD_ACCESS_MUT(bool, mServerHasMovementAuthority, 0x800); // check mServerAuthoritativeMovement in Level instead
	BUILD_ACCESS_MUT(int32_t, mScore, 0x804); // no clue what this is for
	BUILD_ACCESS_MUT(float, mBob, 0x80C);
	BUILD_ACCESS_MUT(bool, mHandsBusy, 0x810);
	BUILD_ACCESS_MUT(std::string, mPlayerName, 0x818);
	BUILD_ACCESS_MUT(enum BuildPlatform, mBuildPlatform, 0x838);
	BUILD_ACCESS_MUT(class Abilities, mAbilities, 0x840);
	BUILD_ACCESS_MUT(const class NetworkIdentifier, mOwner, 0x980);
	BUILD_ACCESS_MUT(std::string, mUniqueName, 0xA18); // seems to be in the form of a hash
	BUILD_ACCESS_MUT(std::string, mServerId, 0xA38);
	BUILD_ACCESS_MUT(std::string, mSelfSignedId, 0xA58);
	BUILD_ACCESS_MUT(std::string, mPlatformOfflineId, 0xA78);
	BUILD_ACCESS_MUT(uint64_t, mClientRandomId, 0xA98);
	BUILD_ACCESS_MUT(const class mce::UUID, mClientUUID, 0xAA0);
	BUILD_ACCESS_MUT(std::unique_ptr<class Certificate>, mCertificate, 0xAB0);
	BUILD_ACCESS_MUT(std::string, mPlatformId, 0xAB8);
	BUILD_ACCESS_MUT(struct ActorUniqueID, mPendingRideID, 0xAD8);
	BUILD_ACCESS_MUT(struct ActorUniqueID, mPendingLeftShoulderRiderID, 0xAE0);
	BUILD_ACCESS_MUT(struct ActorUniqueID, mPendingRightShoulderRiderID, 0xAE8);
	BUILD_ACCESS_MUT(struct ActorUniqueID, mInteractTarget, 0xAF0);
	BUILD_ACCESS_MUT(class Vec3, mInteractTargetPos, 0xAF8);
	BUILD_ACCESS_MUT(bool, mHasFakeInventory, 0xB04);
	BUILD_ACCESS_MUT(std::unique_ptr<class ChunkViewSource>, mChunkSource, 0xB08);
	BUILD_ACCESS_MUT(std::unique_ptr<class ChunkViewSource>, mSpawnChunkSource, 0xB10);
	BUILD_ACCESS_MUT(std::unique_ptr<class BlockSource>, mOwnedBlockSource, 0xB18);
	BUILD_ACCESS_MUT(bool, mUpdateMobs, 0xB20); // whether or not the player can tick nearby mobs?
	BUILD_ACCESS_MUT(class Vec3, mFirstPersonLatestHandOffset, 0xB24); // some remnants of client stuff
	BUILD_ACCESS_MUT(class Vec3, mCapePosOld, 0xB30);
	BUILD_ACCESS_MUT(class vec3, mCapePos, 0xB3C);
	BUILD_ACCESS_MUT(float, mDistanceSinceTraveledEvent, 0xB54);
	BUILD_ACCESS_MUT(std::shared_ptr<class IContainerManager>, mContainerManager, 0xB60);
	BUILD_ACCESS_MUT(std::unique_ptr<class PlayerInventory>, mInventory, 0xB70);
	BUILD_ACCESS_MUT(class SerializedSkin, mSkin, 0xB78);
	//BUILD_ACCESS_MUT(std::vector<class ItemInstance>, mCreativeItemList, 0xD48);
	//BUILD_ACCESS_MUT(std::array<std::vector<class ItemGroup>, 4>, mFilteredCreativeItemList, 0xD60);
	BUILD_ACCESS_MUT(uint8_t, mClientSubId, 0xDC0);
	BUILD_ACCESS_MUT(std::string, mPlatformOnlineId, 0xDC8);
	BUILD_ACCESS_MUT(enum Player::SpawnPositionState, mSpawnPositionState, 0xDE8);
	BUILD_ACCESS_MUT(class Vec3, mSpawnPositioningTestPosition, 0xDF0);
	BUILD_ACCESS_MUT(bool, mBlockRespawnUntilClientMessage, 0xDFC);
	BUILD_ACCESS_MUT(uint32_t, mRespawnChunkBuilderPolicyHandle, 0xE00);
	BUILD_ACCESS_MUT(Player::CachedSpawnData, mCachedSpawnData, 0xE04);
	BUILD_ACCESS_MUT(std::unique_ptr<class BlockSource>, mSpawnBlockSource, 0xE48);
	BUILD_ACCESS_MUT(bool, mHasSeenCredits, 0xE50);
	BUILD_ACCESS_MUT(class StopWatch, mRespawnStopwatchSearching, 0xE58);
	BUILD_ACCESS_MUT(class Vec3, mRespawnOriginalPosition, 0xE88);
	// can also be written like how dimension Id is done in ../Level/Dimension.h
	//BUILD_ACCESS_MUT(AutomaticID<class Dimension, int>, mRespawnOriginalDimension, 0xE94);
	BUILD_ACCESS_MUT(int32_t, mRespawnOriginalDimension, 0xE94);
	BUILD_ACCESS_MUT(bool, mRespawnReady, 0xE98);
	BUILD_ACCESS_MUT(std::string, mRespawnMessage, 0xEA0);
	BUILD_ACCESS_MUT(bool, mCheckBed, 0xEC0); // idk what this is
	BUILD_ACCESS_MUT(class ItemStack, mItemInUse, 0xEC8); // why isnt this a pointer?
	BUILD_ACCESS_MUT(struct PlayerInventory::SlotData, mItemInUseSlot, 0xF58);
	BUILD_ACCESS_MUT(int32_t, mItemInUseDuration, 0xF60);
	BUILD_ACCESS_MUT(int16_t, mSleepCounter, 0xF64);
	BUILD_ACCESS_MUT(int16_t, mPrevSleepCounter, 0xF66);
	BUILD_ACCESS_MUT(bool, mInteractDataDirty, 0xF68);
	BUILD_ACCESS_MUT(struct ActorUniqueID, mPreviousInteractEntity, 0xF70);
	BUILD_ACCESS_MUT(int32_t, mPreviousCarriedItemSlot, 0xF78);
	BUILD_ACCESS_MUT(bool, mAutoJumping, 0xF7C);
	BUILD_ACCESS_MUT(int32_t, mEmoteTicks, 0xF80);
	BUILD_ACCESS_MUT(class PacketSender *, mPacketSender, 0xF88);
	BUILD_ACCESS_MUT(class BlockPos, mBounceStartPos, 0xF90);
	BUILD_ACCESS_MUT(const class Block *, mBounceBlock, 0xFA0);
	BUILD_ACCESS_MUT(float, mFOVModifier, 0xFA8);
	BUILD_ACCESS_MUT(std::shared_ptr<class HudContainerManagerModel>, mHudContainerManagerModel, 0xFB0);
	BUILD_ACCESS_MUT(std::unique_ptr<class EnderChestContainer>, mEnderChestInventory, 0xFC0);
	BUILD_ACCESS_MUT(std::vector<struct ActorUniqueID>, mTrackedBossIDs, 0xFC8);
	BUILD_ACCESS_MUT(enum Player::PositionMode, mPositionMode, 0xFE0);
	BUILD_ACCESS_MUT(enum ActorType, mLastHurtBy, 0xFE4);
	BUILD_ACCESS_MUT(class ItemGroup, mCursorSelectedItemGroup, 0xFE8);
	BUILD_ACCESS_MUT(class PlayerUIContainer, mPlayerUIContainer, 0x1078);
	BUILD_ACCESS_MUT(class InventoryTransactionManager, mTransactionManager, 0x1178);
	BUILD_ACCESS_MUT(std::unique_ptr<class GameMode>, mGameMode, 0x11A0);
	BUILD_ACCESS_MUT(class PlayerSpawnRandomizer, mSpawnRandomizer, 0x11A8); // this is 0x10 bytes smaller in the public 1.16.20 BDS

	// note to self: shift every offset back 0x10 bytes from here and below
	BUILD_ACCESS_MUT(std::unique_ptr<class ItemStackNetManagerBase>, mItemStackNetManager, 0x1BD8); // calling methods on this prints garbage for some reason
	BUILD_ACCESS_MUT(float, mVRMoveAdjAngle, 0x1BE0);
	BUILD_ACCESS_MUT(std::shared_ptr<class AnimationComponent>, mUIAnimationComponent, 0x1BE8);
	BUILD_ACCESS_MUT(std::shared_ptr<class AnimationComponent>, mMapAnimationComponent, 0x1BF8);
	BUILD_ACCESS_MUT(class Player::PlayerSpawnPoint, mPlayerRespawnPoint, 0x1C08);
	BUILD_ACCESS_MUT(bool, mUseUIAnimationComponent, 0x1C24);
	BUILD_ACCESS_MUT(std::vector<class PlayerListener *>, mListeners, 0x1C28);
	BUILD_ACCESS_MUT(class Vec3, mRespawnPositionCandidate, 0x1C4C);
	BUILD_ACCESS_MUT(bool, mPlayerIsSleeping, 0x1C58);
	BUILD_ACCESS_MUT(bool, mDestroyingBlock, 0x1C5A);
	BUILD_ACCESS_MUT(class Vec3, mSurvivalViewerPosition, 0x1C5C);
	BUILD_ACCESS_MUT(std::vector<uint32_t>, mOnScreenAnimationTextures, 0x1C68);
	BUILD_ACCESS_MUT(int32_t, mOnScreenAnimationTicks, 0x1C80);
	BUILD_ACCESS_MUT(enum GameType, mPlayerGameType, 0x1C84);
	BUILD_ACCESS_MUT(uint32_t, mChunkRadius, 0x1C8C); // always mClientViewRadius + 5
	BUILD_ACCESS_MUT(int32_t, mMapIndex, 0x1C90);
	BUILD_ACCESS_MUT(uint64_t, mElytraLoop, 0x1C98);
	BUILD_ACCESS_MUT(float, mElytraVolume, 0x1CA0);
	BUILD_ACCESS_MUT(float, mUnderwaterLightLevel, 0x1CA4);
	BUILD_ACCESS_MUT(std::vector<int32_t>, mCooldowns, 0x1CA8); // for item use, like chorus fruit
	BUILD_ACCESS_MUT(int64_t, mStartedBlockingTimeStamp, 0x1CC0);
	BUILD_ACCESS_MUT(int64_t, mBlockedUsingShieldTimeStamp, 0x1CC8);
	BUILD_ACCESS_MUT(int64_t, mBlockedUsingDamagedShieldTimeStamp, 0x1CD0);
	BUILD_ACCESS_MUT(bool, mPrevBlockedUsingShield, 0x1CD8);
	BUILD_ACCESS_MUT(bool, mUsedPotion, 0x1CDA);
	BUILD_ACCESS_MUT(int32_t, mBounceHeight, 0x1CDC);
	BUILD_ACCESS_MUT(class SkinAdjustments, mSkinAdjustments, 0x1CE0);
	BUILD_ACCESS_MUT(class SerializedSkin, mSerializedSkin, 0x1CE8); // idk how this differs from mSkin
	BUILD_ACCESS_MUT(int32_t, mScanForDolphinTimer, 0x1EB8);
	BUILD_ACCESS_MUT(bool, mR5DataRecoverComplete, 0x1EBC); // mojang...
	BUILD_ACCESS_MUT(std::string, mDeviceId, 0x1EC0);
	BUILD_ACCESS_MUT(bool, mFlagClientForBAIReset, 0x1EE0); // idk what this is
	BUILD_ACCESS_MUT(class BedHelper, mBedHelper, 0x1EE4);

	// ServerPlayer begins here
	BUILD_ACCESS_MUT(class InventoryMenu, mInventoryMenu, 0x20D8);
	BUILD_ACCESS_MUT(enum InputMode, mCurrentInputMode, 0x21A8);
	BUILD_ACCESS_MUT(enum PlayMode, mPlayMode, 0x21AC);
	BUILD_ACCESS_MUT(int32_t, mClientViewRadius, 0x211C); // max render distance

	BUILD_ACCESS_COMPAT(PlayerInventory &, Inventory);
	BUILD_ACCESS_COMPAT(class EnderChestContainer *, EnderChestContainer);
	BUILD_ACCESS_COMPAT(class Certificate &, Certificate);
	BUILD_ACCESS_COMPAT(class NetworkIdentifier const &, NetworkIdentifier);
	BUILD_ACCESS_COMPAT(class BlockPos &, SpawnPosition);
	BUILD_ACCESS_COMPAT(std::string &, DeviceId);
	BUILD_ACCESS_COMPAT(std::string &, ClientPlatformId);
	BUILD_ACCESS_COMPAT(std::string &, PlatformOfflineId);
	BUILD_ACCESS_COMPAT(std::string &, ClientPlatformOnlineId);
	BUILD_ACCESS_COMPAT(unsigned char, ClientSubId);

	BASEAPI void kick();
};