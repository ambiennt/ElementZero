#pragma once

#include "Mob.h"
#include "ActorType.h"
#include "../Core/ExtendedCertificate.h"
#include "../Container/PlayerInventory.h"
#include "../Container/PlayerUIContainer.h"
#include "../Inventory/ContainerManager.h"
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
#include <modutils.h>
#include <base/ezplayer.h>
#include "../dll.h"

class Attribute;
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

class Player : public Mob {
public:

	MCAPI static const Attribute HUNGER;
	MCAPI static const Attribute SATURATION;
	MCAPI static const Attribute EXHAUSTION;
	MCAPI static const Attribute LEVEL;
	MCAPI static const Attribute EXPERIENCE;

	class PlayerSpawnPoint {
	public:
		static inline const BlockPos INVALID_SPAWN_POS = BlockPos::MIN;

		BlockPos mSpawnBlockPos, mPlayerPosition;
		AutomaticID<class Dimension, int32_t> mDimension;
		
		PlayerSpawnPoint() : mSpawnBlockPos(INVALID_SPAWN_POS), mPlayerPosition(INVALID_SPAWN_POS), mDimension(VanillaDimensions::Undefined) {}
		inline bool hasSpawnPoint() const { return (this->mSpawnBlockPos != BlockPos::MIN) && (this->mDimension != VanillaDimensions::Undefined); }
		inline void invalidate() { *this = {}; }
		inline bool isValid() const { return (this->mDimension != VanillaDimensions::Undefined); }
		inline void setSpawnPoint(const BlockPos& spawnBlock, const BlockPos& spawnPos, AutomaticID<class Dimension, int32_t> dim) {
			this->mSpawnBlockPos  = spawnBlock;
			this->mPlayerPosition = spawnPos;
			this->mDimension      = dim;
		}
		inline void setSpawnPoint(BlockPos spawnBlock, AutomaticID<class Dimension, int32_t> dim) {
			this->setSpawnPoint(spawnBlock, spawnBlock, dim);
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
		return this->mPlayerUIContainer.getItem(static_cast<int32_t>(PlayerUISlot::CursorSelected));
	}

	inline class Vec3 const& getRawPlayerPos() const {
		return this->mEZPlayer->mRawPos;
	}

	inline class Vec3 const& getRawPlayerPosOld() const {
		return this->mEZPlayer->mRawPosOld;
	}

	// a more reliable way to get pos delta for players
	// since for some reason the player pos delta zeroes out or the old and current pos match on the same tick
	inline class Vec3 getRawPlayerPosDelta() const {
		const auto& prevPos = this->getRawPlayerPosOld();
		const auto& currPos = this->getRawPlayerPos();
		return currPos - prevPos;
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

	inline class EnderChestContainer& getEnderChestContainer() const {
		return *this->mEnderChestInventory.get();
	}

	inline bool isOperator() const {
		return this->getCommandPermissionLevel() >= CommandPermissionLevel::GameMasters;
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

	inline enum ContainerType getContainerType() const {
		auto container = this->mContainerManager.get();
		return (container ? container->getContainerType() : ContainerType::NONE);
	}

	// player fields
	// some fields still missing
	CLASS_FIELD(mCastawayTimer, 0x7D0, int32_t);  // first field in Player
	CLASS_FIELD(mAteKelp, 0x7D4, bool);
	CLASS_FIELD(mLastBiome, 0x7D8, int32_t); // I guess biome ids are ints
	CLASS_FIELD(mOceanBiomes, 0x7E0, std::vector<int32_t>);
	CLASS_FIELD(mCastawaySent, 0x7F8, bool);
	CLASS_FIELD(mDimensionState, 0x7FC, enum Player::DimensionState);
	CLASS_FIELD(mServerHasMovementAuthority, 0x800, bool); // check mServerAuthoritativeMovement in Level instead
	CLASS_FIELD(mScore, 0x804, int32_t); // no clue what this is for
	CLASS_FIELD(mBob, 0x80C, float);
	CLASS_FIELD(mHandsBusy, 0x810, bool);
	CLASS_FIELD(mPlayerName, 0x818, std::string); // mName
	CLASS_FIELD(mBuildPlatform, 0x838, enum BuildPlatform);
	CLASS_FIELD(mAbilities, 0x840, class Abilities);
	//CLASS_FIELD(mOwner, 0x980, const class NetworkIdentifier); // xref: ServerPlayer::ServerPlayer, this seems to be the same thing as the ServerPlayer NetowrkIdentifier but just to avoid confusion, use the ServerPlayer one 
	CLASS_FIELD(mUniqueName, 0xA18, std::string); // seems to be in the form of a hash
	CLASS_FIELD(mServerId, 0xA38, std::string);
	CLASS_FIELD(mSelfSignedId, 0xA58, std::string);
	CLASS_FIELD(mPlatformOfflineId, 0xA78, std::string); // xref: ServerNetworkHandler::_createNewPlayer
	CLASS_FIELD(mClientRandomId, 0xA98, uint64_t);
	CLASS_FIELD(mClientUUID, 0xAA0, const class mce::UUID);
	CLASS_FIELD(mCertificate, 0xAB0, std::unique_ptr<class Certificate>); // xref: Player::Player
	CLASS_FIELD(mPlatformId, 0xAB8, std::string); // xref: ServerNetworkHandler::_createNewPlayer
	CLASS_FIELD(mPendingRideID, 0xAD8, struct ActorUniqueID);
	CLASS_FIELD(mPendingLeftShoulderRiderID, 0xAE0, struct ActorUniqueID);
	CLASS_FIELD(mPendingRightShoulderRiderID, 0xAE8, struct ActorUniqueID);
	CLASS_FIELD(mInteractTarget, 0xAF0, struct ActorUniqueID);
	CLASS_FIELD(mInteractTargetPos, 0xAF8, class Vec3);
	CLASS_FIELD(mHasFakeInventory, 0xB04, bool);
	CLASS_FIELD(mChunkSource, 0xB08, std::unique_ptr<class ChunkViewSource>);
	CLASS_FIELD(mSpawnChunkSource, 0xB10, std::unique_ptr<class ChunkViewSource>);
	CLASS_FIELD(mOwnedBlockSource, 0xB18, std::unique_ptr<class BlockSource>);
	CLASS_FIELD(mUpdateMobs, 0xB20, bool); // whether or not the player can tick nearby mobs?

	//CLASS_FIELD(mFirstPersonLatestHandOffset, 0xB24, class Vec3); // some remnants of client stuff (replaced by mEZPlayer field)
	CLASS_FIELD(mEZPlayer, 0xB24, class EZPlayer *);

	CLASS_FIELD(mCapePosOld, 0xB30, class Vec3);
	CLASS_FIELD(mCapePos, 0xB3C, class vec3);
	CLASS_FIELD(mDistanceSinceTraveledEvent, 0xB54, float);
	CLASS_FIELD(mContainerManager, 0xB60, std::shared_ptr<class IContainerManager>);
	CLASS_FIELD(mPlayerInventory, 0xB70, std::unique_ptr<class PlayerInventory>); // mInventory
	CLASS_FIELD(mSkin, 0xB78, class SerializedSkin); // use this to read and write to the player skin
	CLASS_FIELD(mCreativeItemList, 0xD48, std::vector<class ItemInstance>);
	CLASS_FIELD(mFilteredCreativeItemList, 0xD60, std::array<std::vector<class ItemGroup>, 4>);
	CLASS_FIELD(mClientSubId, 0xDC0, uint8_t); // xref: RaidBossComponent::_sendBossEvent, 1 for the other xbox splitscreen player, if not using splitscreen assume its 0
	CLASS_FIELD(mPlatformOnlineId, 0xDC8, std::string); // xref: ServerNetworkHandler::_createNewPlayer
	CLASS_FIELD(mSpawnPositionState, 0xDE8, enum Player::SpawnPositionState);
	CLASS_FIELD(mSpawnPositioningTestPosition, 0xDF0, class Vec3);
	CLASS_FIELD(mBlockRespawnUntilClientMessage, 0xDFC, bool);
	CLASS_FIELD(mRespawnChunkBuilderPolicyHandle, 0xE00, uint32_t);
	CLASS_FIELD(mCachedSpawnData, 0xE04, Player::CachedSpawnData);
	CLASS_FIELD(mSpawnBlockSource, 0xE48, std::unique_ptr<class BlockSource>);
	CLASS_FIELD(mHasSeenCredits, 0xE50, bool);
	CLASS_FIELD(mRespawnStopwatchSearching, 0xE58, class StopWatch);
	CLASS_FIELD(mRespawnOriginalPosition, 0xE88, class Vec3);
	CLASS_FIELD(mRespawnOriginalDimension, 0xE94, enum DimensionID); // AutomaticID<class Dimension, int>
	CLASS_FIELD(mRespawnReady, 0xE98, bool);
	CLASS_FIELD(mRespawnMessage, 0xEA0, std::string);
	CLASS_FIELD(mCheckBed, 0xEC0, bool); // idk what this is
	CLASS_FIELD(mIsInitialSpawnDone, 0xEC1, bool);
	CLASS_FIELD(mItemInUse, 0xEC8, class ItemStack); // why isnt this a pointer?
	CLASS_FIELD(mItemInUseSlot, 0xF58, struct PlayerInventory::SlotData);
	CLASS_FIELD(mItemInUseDuration, 0xF60, int32_t);
	CLASS_FIELD(mSleepCounter, 0xF64, int16_t);
	CLASS_FIELD(mPrevSleepCounter, 0xF66, int16_t);
	CLASS_FIELD(mInteractDataDirty, 0xF68, bool);
	CLASS_FIELD(mPreviousInteractEntity, 0xF70, struct ActorUniqueID);
	CLASS_FIELD(mPreviousCarriedItemSlot, 0xF78, int32_t);
	CLASS_FIELD(mAutoJumping, 0xF7C, bool);
	CLASS_FIELD(mEmoteTicks, 0xF80, int32_t);
	CLASS_FIELD(mPacketSender, 0xF88, class PacketSender *);
	CLASS_FIELD(mBounceStartPos, 0xF90, class BlockPos);
	CLASS_FIELD(mBounceBlock, 0xFA0, const class Block *);
	CLASS_FIELD(mFOVModifier, 0xFA8, float);
	CLASS_FIELD(mHudContainerManagerModel, 0xFB0, std::shared_ptr<class HudContainerManagerModel>);
	CLASS_FIELD(mEnderChestInventory, 0xFC0, std::unique_ptr<class EnderChestContainer>);
	CLASS_FIELD(mTrackedBossIDs, 0xFC8, std::vector<struct ActorUniqueID>);
	CLASS_FIELD(mPositionMode, 0xFE0, enum Player::PositionMode);
	CLASS_FIELD(mLastHurtBy, 0xFE4, enum ActorType);
	CLASS_FIELD(mCursorSelectedItemGroup, 0xFE8, class ItemGroup);
	CLASS_FIELD(mPlayerUIContainer, 0x1078, class PlayerUIContainer);
	CLASS_FIELD(mTransactionManager, 0x1178, class InventoryTransactionManager);
	CLASS_FIELD(mGameMode, 0x11A0, std::unique_ptr<class GameMode>);

	// this is probably 0x10 bytes smaller in the public 1.16.20 BDS (including struct alignment)
	CLASS_FIELD(mSpawnRandomizer, 0x11A8, class PlayerRespawnRandomizer);

	// note to self: shift every offset back 0x10 bytes from here and below
	CLASS_FIELD(mItemStackNetManager, 0x1BD8, std::unique_ptr<class ItemStackNetManagerBase>);
	CLASS_FIELD(mVRMoveAdjAngle, 0x1BE0, float);
	CLASS_FIELD(mUIAnimationComponent, 0x1BE8, std::shared_ptr<class AnimationComponent>);
	CLASS_FIELD(mMapAnimationComponent, 0x1BF8, std::shared_ptr<class AnimationComponent>);
	CLASS_FIELD(mPlayerRespawnPoint, 0x1C08, class Player::PlayerSpawnPoint); //  basically just the spawn position, xref: Player::setSpawnBlockRespawnPosition
	CLASS_FIELD(mUseUIAnimationComponent, 0x1C24, bool);     
	CLASS_FIELD(mListeners, 0x1C28, std::vector<class PlayerListener *>);
	CLASS_FIELD(mLastLevelUpTime, 0x1C40, int32_t);
	CLASS_FIELD(mRespawnPositionCandidate, 0x1C4C, class Vec3);
	CLASS_FIELD(mPlayerLevelChanged, 0x1C44, int32_t);
	CLASS_FIELD(mPreviousLevelRequirement, 0x1C48, int32_t);
	CLASS_FIELD(mPlayerIsSleeping, 0x1C58, bool);
	CLASS_FIELD(mDestroyingBlock, 0x1C5A, bool);
	CLASS_FIELD(mSurvivalViewerPosition, 0x1C5C, class Vec3);
	CLASS_FIELD(mOnScreenAnimationTextures, 0x1C68, std::vector<uint32_t>);
	CLASS_FIELD(mOnScreenAnimationTicks, 0x1C80, int32_t);
	CLASS_FIELD(mPlayerGameType, 0x1C84, enum GameType);
	CLASS_FIELD(mChunkRadius, 0x1C8C, uint32_t); // always mClientViewRadius + 5
	CLASS_FIELD(mMapIndex, 0x1C90, int32_t);
	CLASS_FIELD(mElytraLoop, 0x1C98, uint64_t);
	CLASS_FIELD(mElytraVolume, 0x1CA0, float);
	CLASS_FIELD(mUnderwaterLightLevel, 0x1CA4, float);
	CLASS_FIELD(mCooldowns, 0x1CA8, std::vector<int32_t>); // for item use, like chorus fruit
	CLASS_FIELD(mStartedBlockingTimeStamp, 0x1CC0, int64_t);
	CLASS_FIELD(mBlockedUsingShieldTimeStamp, 0x1CC8, int64_t);
	CLASS_FIELD(mBlockedUsingDamagedShieldTimeStamp, 0x1CD0, int64_t);
	CLASS_FIELD(mPrevBlockedUsingShield, 0x1CD8, bool);
	CLASS_FIELD(mUsedPotion, 0x1CDA, bool);
	CLASS_FIELD(mBounceHeight, 0x1CDC, int32_t);
	CLASS_FIELD(mSkinAdjustments, 0x1CE0, class SkinAdjustments);
	CLASS_FIELD(mSerializedSkin, 0x1CE8, class SerializedSkin); // mSkin (0xB78) seems to be used instead - do not use this field
	CLASS_FIELD(mScanForDolphinTimer, 0x1EB8, int32_t);
	CLASS_FIELD(mR5DataRecoverComplete, 0x1EBC, bool); // mojang...
	CLASS_FIELD(mDeviceId, 0x1EC0, std::string); // xref: ServerPlayer::ServerPlayer
	CLASS_FIELD(mFlagClientForBAIReset, 0x1EE0, bool); // idk what this is
	CLASS_FIELD(mBedHelper, 0x1EE4, class BedHelper); // last field in Player, ends at 0x1F0C (0x1EE4 + 0x28)

	// serverplayer starts here
	// offsets get kinda fuzzy here so make sure to manually verify
	CLASS_FIELD(mNetworkHandler, 0x1F10, class NetworkHandler*); // xref: ServerPlayer::ServerPlayer
	CLASS_FIELD(mNetworkIdentifier, 0x1F70, const class NetworkIdentifier); // xref: ServerPlayer::ServerPlayer, only seems to be in release bds?
	CLASS_FIELD(mInventoryMenu, 0x20D8, class InventoryMenu);
	CLASS_FIELD(mLocalPlayerInitialized, 0x2123, bool); // in response to SetLocalPlayerAsInitializedPacket, use Player::isPlayerInitialized() instead
	CLASS_FIELD(mCurrentInputMode, 0x21A8, enum InputMode);
	CLASS_FIELD(mPlayMode, 0x21AC, enum PlayMode);
	CLASS_FIELD(mContainerCounter, 0x2118, enum ContainerID);
	CLASS_FIELD(mClientViewRadius, 0x211C, int32_t); // max render distance
	CLASS_FIELD(mMovementData, 0x21B0, class PlayerMovementTelemetryData); // last field in ServerPlayer, ends at 0x21C0 (0x21B0 + 0x10)
};