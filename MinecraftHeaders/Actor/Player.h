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
#include "../dll.h"

class Packet;
class ServerPlayer;
class NetworkIdentifier;
class Dimension;
enum class StructureFeatureType;
enum class GameType;
enum class CooldownType;
enum class ClientPlayMode;

enum class MovementEventType { PositionCorrected, BackInSync };

enum class AbilitiesIndex {
  Invalid              = -1,
  Build                = 0,
  Mine                 = 1,
  DoorsAndSwitches     = 2,
  OpenContainers       = 3,
  AttackPlayers        = 4,
  AttackMobs           = 5,
  OperatorCommands     = 6,
  Teleport             = 7,
  ExposedAbilityCount  = 8,
  Invulnerable         = 8,
  Flying               = 9,
  MayFly               = 10,
  Instabuild           = 11,
  Lightning            = 12,
  FlySpeed             = 13,
  WalkSpeed            = 14,
  Muted                = 15,
  WorldBuilder         = 16,
  NoClip               = 17,
  AbilityCount         = 18
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

  inline ServerPlayer *asServerPlayer() const noexcept {
    return const_cast<ServerPlayer *>(reinterpret_cast<ServerPlayer const *>(this));
  }

  enum class PositionMode : unsigned char {
    Normal       = 0,
    Respawn      = 1,
    Teleport     = 2,
    OnlyHeadRot  = 3
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
  virtual void stopSleepInBed(bool, bool);
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

  bool isInRaid(void) const;
  bool isSurvival(void) const;
  bool isInCreativeMode(void) const;
  bool isHiddenFrom(class Mob &) const;

  bool canBeSeenOnMap(void) const;
  bool canUseOperatorBlocks(void) const;
  bool canDestroy(class Block const &) const;
  bool canUseAbility(enum AbilitiesIndex) const;

  class Agent *getAgent(void) const;
  int getDirection(void) const;
  int getXpNeededForNextLevel(void) const;
  float getDestroySpeed(class Block const &) const;
  float getDestroyProgress(class Block const &) const;
  class ItemStack const &getSelectedItem(void) const;
  enum GameType getPlayerGameType(void) const;
  class ItemStack const &getCurrentActiveShield(void) const;
  class EnderChestContainer *getEnderChestContainer(void);

  void updateTeleportDestPos(void);
  void updateInventoryTransactions(void);
  void updateSkin(class SerializedSkin const &, int);

  void setAgent(class Agent *);
  void setRespawnPosition(class BlockPos const &, bool);
  void setBedRespawnPosition(class BlockPos const &);
  void setPlayerUIItem(enum PlayerUISlot, class ItemStack const &);
  void setContainerManager(class std::shared_ptr<class IContainerManager>);

  void eat(int, float);
  void startUsingItem(class ItemStack const &, int);
  void stopUsingItem(void);
  void releaseUsingItem(void);
  void stopGliding(void);
  void resetPlayerLevel(void);
  void handleJumpEffects(void);
  bool take(class Actor &, int, int);
  void updateTrackedBosses(void);
  void causeFoodExhaustion(float);
  bool checkNeedAutoJump(float, float);
  void clearRespawnPosition(void);
  void recheckSpawnPosition(void);

  inline class ItemStack const& getPlayerUIItem() {
    return CallServerClassMethod<class ItemStack const&>(
      "?getItem@SimpleContainer@@UEBAAEBVItemStack@@H@Z", &direct_access<class SimpleContainer>(this, 0x1078), PlayerUISlot::CursorSelected);
  }

  inline class PlayerSpawnPoint* getPlayerSpawnPoint() {
    return direct_access<class PlayerSpawnPoint *>(this, 0x1C18);
  }

  inline std::string getPlayerName() const {
    return direct_access<std::string>(this, 0x818);
  }

  inline class BlockSource* getRegion() {
    return direct_access<class BlockSource*>(this, 0x320);
  }

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
