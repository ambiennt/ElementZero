#pragma once

#include <vector>

#include <hook.h>

#include "Actor.h"
#include "Mob.h"
#include "ActorType.h"
#include "../Core/ExtendedCertificate.h"
#include "../Container/PlayerInventory.h"
#include "../Container/EnderChestContainer.h"
#include "../Container/PlayerUIContainer.h"
#include "../Math/Vec3.h"
#include "../Math/BlockPos.h"
#include "../Core/AutomaticID.h"
#include "../Core/VanillaDimensions.h"
#include "../Command/CommandPermissionLevel.h"
#include "../Level/Level.h"
#include "../Level/PlayerPermissionLevel.h"
#include "../Level/GameType.h"
#include "../Level/Abilities.h"
#include "../Packet/LevelChunkPacket.h"
#include "../Packet/AdventureSettingsPacket.h"
#include "../dll.h"

// add custom player fields here
struct EZPlayerFields {
	uint64_t mLastUhcHeadEatTimestamp; // the tick when the player last ate a head/golden head 
	uint64_t mBucketCooldownTimestamp; // the tick when the player last placed a bucket of liquid
	bool mShouldCancelBucketPickup; // whether or not the player can pick up liquid, used to fix MCPE-100598
	uint64_t mLastAttackedActorTimestamp; // the tick when the player last attacked an actor 
	bool mHasResetSprint; // if true, player should administer bonus knockback to other players
	Vec3 mRawPos; // use this value for more accuracy of current pos (sometimes BDS pos zeroes out)
	Vec3 mRawPosOld; // used this value for more accuracy of pos from last tick
	int32_t mHealthOld; // heatlh value from the previous tick
	int32_t mAbsorptionOld; // absorption value from the previous tick
	uint64_t mLastSharpnessParticleEmitTimestamp;

	EZPlayerFields() {
		this->mLastUhcHeadEatTimestamp = 0;
		this->mBucketCooldownTimestamp = 0;
		this->mShouldCancelBucketPickup = false;
		this->mLastAttackedActorTimestamp = 0;
		this->mHasResetSprint = false;
		this->mRawPos = Vec3::ZERO;
		this->mRawPosOld = Vec3::ZERO;
		this->mHealthOld = 0;
		this->mAbsorptionOld = 0;
		this->mLastSharpnessParticleEmitTimestamp = 0;
	}
};

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
	virtual void destroyRegion();
	virtual void suspendRegion();
	virtual void _fireWillChangeDimension();
	virtual void _fireDimensionChanged();
	virtual void changeDimensionWithCredits(class AutomaticID<class Dimension, int>);
	virtual int tickWorld(struct Tick const &);
	virtual void frameUpdate(class FrameUpdateContextBase &);
	virtual std::vector<class ChunkPos> const &getTickingOffsets() const;
	virtual void moveView();
	virtual void setName(std::string const &);
	virtual void checkMovementStats(class Vec3 const &);
	virtual class StructureFeature *getCurrentStructureFeature() const;
	virtual bool isAutoJumpEnabled() const;
	virtual void respawn();
	virtual void resetRot();
	virtual void resetPos(bool);
	virtual bool isInTrialMode();
	virtual bool hasResource(int);
	virtual void completeUsingItem();
	virtual void setPermissions(enum CommandPermissionLevel);
	virtual void startDestroying();
	virtual void stopDestroying();
	virtual void openPortfolio();
	virtual void openBook(int, bool, int, BlockActor *);
	virtual void openTrading(struct ActorUniqueID const &, bool);
	virtual bool canOpenContainerScreen();
	virtual void openChalkboard(class ChalkboardBlockActor *, bool);
	virtual void openNpcInteractScreen(Actor &);
	virtual void openInventory();
	virtual void displayChatMessage(std::string const &, std::string const &);
	virtual void displayClientMessage(std::string const &);
	virtual void displayTextObjectMessage(class TextObjectRoot const &);
	virtual void displayTextObjectWhisperMessage(class TextObjectRoot const &, std::string const &, std::string const &);
	virtual void displayWhisperMessage(std::string const &, std::string const &, std::string const &, std::string const &);
	virtual enum BedSleepingResult startSleepInBed(class BlockPos const &);
	virtual void stopSleepInBed(bool forcefulWakeUp, bool updateLevelList);
	virtual bool canStartSleepInBed();
	virtual int getSleepTimer() const;
	virtual int getPreviousTickSleepTimer() const;
	virtual void openSign(BlockPos const &);
	virtual void playEmote(std::string const &);
	virtual bool isLocalPlayer() const;
	virtual bool isHostingPlayer() const;
	virtual bool isLoading() const;
	virtual bool isPlayerInitialized() const;
	virtual void stopLoading();
	virtual void registerTrackedBoss(struct ActorUniqueID);
	virtual void unRegisterTrackedBoss(struct ActorUniqueID);
	virtual void setPlayerGameType(enum GameType);
	virtual void _crit(class Actor &);
	virtual class IMinecraftEventing *getEventing() const;
	virtual uint8_t getUserId();
	virtual void sendEventPacket(class EventPacket &) const;
	virtual void addExperience(int);
	virtual void addLevels(int);
	virtual void setContainerData(class IContainerManager &, int, int);
	virtual void slotChanged(class IContainerManager &, class Container &, int, class ItemStack const &, class ItemStack const &, bool);
	virtual void inventoryChanged(class Container &, int, class ItemStack const &, class ItemStack const &, bool);
	virtual void refreshContainer(class IContainerManager &);
	virtual void deleteContainerManager();
	virtual void setFieldOfViewModifier(float);
	virtual bool isPositionRelevant(class AutomaticID<class Dimension, int>, class BlockPos const &);
	virtual bool isEntityRelevant(class Actor const &);
	virtual bool isTeacher() const;
	virtual void onSuspension();
	virtual void onLinkedSlotsChanged();
	virtual void startCooldown(class Item const *);
	virtual int getItemCooldownLeft(enum CooldownType) const;
	virtual bool isItemInCooldown(enum CooldownType) const;
	virtual void sendInventoryTransaction(class InventoryTransaction const &) const;
	virtual void sendComplexInventoryTransaction(std::unique_ptr<class ComplexInventoryTransaction>) const;
	virtual void sendNetworkPacket(class Packet &) const;
	virtual class PlayerEventCoordinator &getPlayerEventCoordinator();
	virtual class MoveInputHandler *getMoveInputHandler();
	virtual enum InputMode getInputMode() const;
	virtual enum ClientPlayMode getPlayMode() const;
	virtual void reportMovementTelemetry(enum MovementEventType);
	virtual void onMovePlayerPacketNormal(class Vec3 const &, class Vec2 const &, float);

	MCAPI bool isInRaid() const;
	MCAPI bool isSurvival() const;
	MCAPI bool isInCreativeMode() const;
	MCAPI bool isHiddenFrom(class Mob &) const;
	MCAPI bool canBeSeenOnMap() const;
	MCAPI bool canUseOperatorBlocks() const;
	MCAPI bool canDestroy(class Block const &) const;
	MCAPI bool canUseAbility(enum AbilitiesIndex) const;
	MCAPI class Agent *getAgent() const;
	MCAPI int getDirection() const;
	MCAPI int getXpNeededForNextLevel() const;
	MCAPI float getDestroySpeed(class Block const &) const;
	MCAPI float getDestroyProgress(class Block const &) const;
	MCAPI class ItemStack const &getSelectedItem() const;
	MCAPI void setSelectedItem(class ItemStack const&);
	MCAPI class ItemStack const &getCurrentActiveShield() const;
	//MCAPI class EnderChestContainer *getEnderChestContainer();
	//MCAPI class PlayerInventory& getSupplies();
	MCAPI void updateTeleportDestPos();
	MCAPI void updateInventoryTransactions();
	MCAPI void updateSkin(class SerializedSkin const &, int clientSubID); // client side function, has no effect on server
	MCAPI void setAgent(class Agent *);
	MCAPI void setRespawnPosition(class BlockPos const &, bool);
	MCAPI void setBedRespawnPosition(class BlockPos const &);
	MCAPI void setPlayerUIItem(enum PlayerUISlot, class ItemStack const &);
	MCAPI void setContainerManager(class std::shared_ptr<class IContainerManager>);
	MCAPI void eat(int, float);
	MCAPI void startUsingItem(class ItemStack const &, int);
	MCAPI void stopUsingItem();
	MCAPI void releaseUsingItem();
	MCAPI void stopGliding();
	MCAPI void resetPlayerLevel();
	MCAPI void handleJumpEffects();
	MCAPI bool take(class Actor &, int, int);
	MCAPI void updateTrackedBosses();
	MCAPI void causeFoodExhaustion(float);
	MCAPI bool checkNeedAutoJump(float, float);
	MCAPI void clearRespawnPosition();
	MCAPI void recheckSpawnPosition();

	// custom methods
	inline ServerPlayer *asServerPlayer() const noexcept {
		return const_cast<ServerPlayer *>(reinterpret_cast<ServerPlayer const *>(this));
	}

	inline class ItemStack const& getPlayerUIItem() const {
		return this->mPlayerUIContainer.getItem((int32_t)PlayerUISlot::CursorSelected);
	}

	inline class Vec3 const& getRawPlayerPos() const {
		return this->EZPlayerFields->mRawPos;
	}

	inline class Vec3 const& getRawPlayerPosOld() const {
		return this->EZPlayerFields->mRawPosOld;
	}

	// a more reliable way to get pos delta for players
	// since for some reason the player pos delta zeroes out or the old and current pos match on the same tick
	inline class Vec3 getRawPlayerPosDelta() const {
		const auto& prevPos = this->getRawPlayerPosOld();
		const auto& currPos = this->getRawPlayerPos();
		return Vec3(currPos.x - prevPos.x, currPos.y - prevPos.y, currPos.z - prevPos.z);
	}

	// fill LevelChunkPacket with empty values except for cache setting
	inline void crashClient() const {
		LevelChunkPacket badPkt;
		badPkt.mCacheEnabled = true;
		this->sendNetworkPacket(badPkt);
	}

	inline class PlayerInventory& getSupplies() const {
		return *this->mPlayerInventory.get();
	}

	inline class Inventory& getRawInventory() const {
		return *this->mPlayerInventory->mInventory.get();
	}

	inline class EnderChestContainer* getEnderChestContainer() const {
		return this->mEnderChestInventory.get();
	}

	inline bool isOperator() const {
		return (this->getCommandPermissionLevel() >= CommandPermissionLevel::GameMasters);
	}

	inline enum PlayerPermissionLevel getPlayerPermissionLevel() const {
		return this->mAbilities.mPermissionsHandler->mPlayerPermissions;
	}	

	inline void syncAbilities() const {
		AdventureSettingsPacket pkt(this->mLevel->getAdventureSettings(), this->mAbilities, this->getUniqueID(), false);
		this->mLevel->forEachPlayer([&](Player const& p) -> bool {
        	p.sendNetworkPacket(pkt);
        	return true;
    	});
	}

	inline void setPlayerPermissionLevel(enum PlayerPermissionLevel level, bool syncToClients) {
		this->mAbilities.mPermissionsHandler->mPlayerPermissions = level;
		if (syncToClients) { this->syncAbilities(); }
	}

	template <typename T> T getAbilityValue(enum AbilitiesIndex index) const;
	template <> bool getAbilityValue<bool>(enum AbilitiesIndex index) const {
		const auto& abil = this->mAbilities.mAbilities[(int32_t)index];
		if (abil.mType == Ability::Type::BooleanType) { return static_cast<bool>(abil.mValue.mBoolVal); }
		return false;
	}
	template <> float getAbilityValue<float>(enum AbilitiesIndex index) const {
		const auto& abil = this->mAbilities.mAbilities[(int32_t)index];
		if (abil.mType == Ability::Type::FloatType) { return static_cast<float>(abil.mValue.mFloatVal); }
		return 0.f;
	}

	inline void setAbilityValue(enum AbilitiesIndex index, bool flag, bool syncToClients) {
		auto& abil = this->mAbilities.mAbilities[(int32_t)index];
		if (abil.mType == Ability::Type::BooleanType) {
			abil.mValue.mBoolVal = flag;
			if (syncToClients) { this->syncAbilities(); }
		}
	}
	inline void setAbilityValue(enum AbilitiesIndex index, float value, bool syncToClients) {
		auto& abil = this->mAbilities.mAbilities[(int32_t)index];
		if (abil.mType == Ability::Type::FloatType) {
			abil.mValue.mFloatVal = value;
			if (syncToClients) { this->syncAbilities(); }
		}
	}

	// player fields
	// some fields still missing
	BUILD_ACCESS_MUT(int32_t, mCastawayTimer, 0x7D0);  // first field in Player
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
	//BUILD_ACCESS_MUT(class Vec3, mFirstPersonLatestHandOffset, 0xB24); // some remnants of client stuff (REPLACED BY EZPlayerFields)
	BUILD_ACCESS_MUT(class Vec3, mCapePosOld, 0xB30);
	BUILD_ACCESS_MUT(class vec3, mCapePos, 0xB3C);
	BUILD_ACCESS_MUT(float, mDistanceSinceTraveledEvent, 0xB54);
	BUILD_ACCESS_MUT(std::shared_ptr<class IContainerManager>, mContainerManager, 0xB60);
	BUILD_ACCESS_MUT(std::unique_ptr<class PlayerInventory>, mPlayerInventory, 0xB70); // mInventory
	BUILD_ACCESS_MUT(class SerializedSkin, mSkin, 0xB78); // use this to read and write to the player skin
	BUILD_ACCESS_MUT(std::vector<class ItemInstance>, mCreativeItemList, 0xD48);

	using filteredCreativeItemList = std::array<std::vector<class ItemGroup>, 4>;
	BUILD_ACCESS_MUT(filteredCreativeItemList, mFilteredCreativeItemList, 0xD60);

	BUILD_ACCESS_MUT(uint8_t, mClientSubId, 0xDC0); // for the other xbox splitscreen player, if not using splitscreen assume its 0
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

	//BUILD_ACCESS_MUT(AutomaticID<class Dimension, int>, mRespawnOriginalDimension, 0xE94);
	BUILD_ACCESS_MUT(int32_t, mRespawnOriginalDimension, 0xE94);

	BUILD_ACCESS_MUT(bool, mRespawnReady, 0xE98);
	BUILD_ACCESS_MUT(std::string, mRespawnMessage, 0xEA0);
	BUILD_ACCESS_MUT(bool, mCheckBed, 0xEC0); // idk what this is
	BUILD_ACCESS_MUT(bool, mIsInitialSpawnDone, 0xEC1);
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
	BUILD_ACCESS_MUT(int32_t, mLastLevelUpTime, 0x1C40);
	BUILD_ACCESS_MUT(int32_t, mPlayerLevelChanged, 0x1C44);
	BUILD_ACCESS_MUT(int32_t, mPreviousLevelRequirement, 0x1C48);
	BUILD_ACCESS_MUT(std::unique_ptr<class ItemStackNetManagerBase>, mItemStackNetManager, 0x1BD8);
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
	BUILD_ACCESS_MUT(class SerializedSkin, mSerializedSkin, 0x1CE8); // mSkin (0xB78) seems to be used instead - do not use this field
	BUILD_ACCESS_MUT(int32_t, mScanForDolphinTimer, 0x1EB8);
	BUILD_ACCESS_MUT(bool, mR5DataRecoverComplete, 0x1EBC); // mojang...
	BUILD_ACCESS_MUT(std::string, mDeviceId, 0x1EC0);
	BUILD_ACCESS_MUT(bool, mFlagClientForBAIReset, 0x1EE0); // idk what this is
	BUILD_ACCESS_MUT(class BedHelper, mBedHelper, 0x1EE4); // last field in Player, ends at 0x1F0C (0x1EE4 + 0x28)

	// ServerPlayer begins here
	// some fields still missing
	BUILD_ACCESS_MUT(class NetworkHandler*, mNetworkHandler, 0x1F10); // first field in ServerPlayer
	BUILD_ACCESS_MUT(class InventoryMenu, mInventoryMenu, 0x20D8);
	BUILD_ACCESS_MUT(bool, mLocalPlayerInitialized, 0x2123); // in response to SetLocalPlayerAsInitializedPacket, use Player::isPlayerInitialized() instead
	BUILD_ACCESS_MUT(enum InputMode, mCurrentInputMode, 0x21A8);
	BUILD_ACCESS_MUT(enum PlayMode, mPlayMode, 0x21AC);
	BUILD_ACCESS_MUT(enum ContainerID, mContainerCounter, 0x2118);
	BUILD_ACCESS_MUT(int32_t, mClientViewRadius, 0x211C); // max render distance
	BUILD_ACCESS_MUT(class PlayerMovementTelemetryData, mMovementData, 0x21B0); // last field in ServerPlayer, ends at 0x21C0 (0x21B0 + 0x10)

	BUILD_ACCESS_COMPAT(class Certificate &, Certificate);
	BUILD_ACCESS_COMPAT(class NetworkIdentifier const &, NetworkIdentifier);
	BUILD_ACCESS_COMPAT(class BlockPos &, SpawnPosition);
	BUILD_ACCESS_COMPAT(std::string &, DeviceId);
	BUILD_ACCESS_COMPAT(std::string &, ClientPlatformId);
	BUILD_ACCESS_COMPAT(std::string &, PlatformOfflineId);
	BUILD_ACCESS_COMPAT(std::string &, ClientPlatformOnlineId);
	BUILD_ACCESS_COMPAT(uint8_t, ClientSubId);
	BUILD_ACCESS_COMPAT(struct EZPlayerFields*, EZPlayerFields);

	BASEAPI void kick();
};