#pragma once

#include <memory>
#include <string>

#include "../Core/json.h"
#include "../dll.h"

#include <hook.h>
#include <modutils.h>

enum class InHandUpdateType;

enum class CooldownType { // custom items can have custom cooldown types
  None               = -1,
  ChorusFruit        = 0,
  EnderPearl         = 1,
  IceBomb            = 2,
  CooldownTypeCount  = 3
};

enum class UseAnimation {
  None             = 0,
  Eat              = 1,
  Drink            = 2,
  Block            = 3,
  Bow              = 4,
  Camera           = 5,
  Spear            = 6,
  GlowStick        = 7,
  Sparkler         = 8,
  Crossbow         = 9
};

enum class CreativeItemCategory {
  All              = 0,
  Construction     = 1,
  Nature           = 2,
  Equipment        = 3,
  Items            = 4,
  ItemCommandOnly  = 5,
  Undefined        = 6,
  NUM_CATEGORIES   = 7
};

enum class BlockShape {
  INVISIBLE                  = -0x1,
  BLOCK                      = 0x0,
  CROSS_TEXTURE              = 0x1,
  TORCH                      = 0x2,
  FIRE                       = 0x3,
  WATER                      = 0x4,
  RED_DUST                   = 0x5,
  ROWS                       = 0x6,
  DOOR                       = 0x7,
  LADDER                     = 0x8,
  RAIL                       = 0x9,
  STAIRS                     = 0x0A,
  FENCE                      = 0x0B,
  LEVER                      = 0x0C,
  CACTUS                     = 0x0D,
  BED                        = 0x0E,
  DIODE                      = 0x0F,
  IRON_FENCE                 = 0x12,
  STEM                       = 0x13,
  VINE                       = 0x14,
  FENCE_GATE                 = 0x15,
  CHEST                      = 0x16,
  LILYPAD                    = 0x17,
  BREWING_STAND              = 0x19,
  PORTAL_FRAME               = 0x1A,
  COCOA                      = 0x1C,
  TREE                       = 0x1F,
  WALL                       = 0x20,
  DOUBLE_PLANT               = 0x28,
  FLOWER_POT                 = 0x2A,
  ANVIL                      = 0x2B,
  DRAGON_EGG                 = 0x2C,
  STRUCTURE_VOID             = 0x30,
  BLOCK_HALF                 = 0x43,
  TOP_SNOW                   = 0x44,
  TRIPWIRE                   = 0x45,
  TRIPWIRE_HOOK              = 0x46,
  CAULDRON                   = 0x47,
  REPEATER                   = 0x48,
  COMPARATOR                 = 0x49,
  HOPPER                     = 0x4A,
  SLIME_BLOCK                = 0x4B,
  PISTON                     = 0x4C,
  BEACON                     = 0x4D,
  CHORUS_PLANT               = 0x4E,
  CHORUS_FLOWER              = 0x4F,
  END_PORTAL                 = 0x50,
  END_ROD                    = 0x51,
  END_GATEWAY                = 0x52,
  SKULL                      = 0x53,
  FACING_BLOCK               = 0x54,
  COMMAND_BLOCK              = 0x55,
  TERRACOTTA                 = 0x56,
  DOUBLE_SIDE_FENCE          = 0x57,
  ITEM_FRAME                 = 0x58,
  SHULKER_BOX                = 0x59,
  DOUBLESIDED_CROSS_TEXTURE  = 0x5A,
  DOUBLESIDED_DOUBLE_PLANT   = 0x5B,
  DOUBLESIDED_ROWS           = 0x5C,
  ELEMENT_BLOCK              = 0x5D,
  CHEMISTRY_TABLE            = 0x5E,
  CORAL_FAN                  = 0x60,
  SEAGRASS                   = 0x61,
  KELP                       = 0x62,
  TRAPDOOR                   = 0x63,
  SEA_PICKLE                 = 0x64,
  CONDUIT                    = 0x65,
  TURTLE_EGG                 = 0x66,
  BUBBLE_COLUMN              = 0x69,
  BARRIER                    = 0x6A,
  SIGN                       = 0x6B,
  BAMBOO                     = 0x6C,
  BAMBOO_SAPLING             = 0x6D,
  SCAFFOLDING                = 0x6E,
  GRINDSTONE                 = 0x6F,
  BELL                       = 0x70,
  LANTERN                    = 0x71,
  CAMPFIRE                   = 0x72,
  LECTERN                    = 0x73,
  SWEET_BERRY_BUSH           = 0x74,
  CARTOGRAPHY_TABLE          = 0x75,
  COMPOSTER                  = 0x76,
  STONE_CUTTER               = 0x77,
  HONEY_BLOCK                = 0x78,
  WEEPING_VINE               = 0x79,
  TWISTING_VINE              = 0x7A,
  CHAIN                      = 0x7B
};

enum class ItemUseMethod {
  Unknown          = -1,
  EquipArmor       = 0,
  Eat              = 1,
  Attack           = 2,
  Consume          = 3,
  Throw            = 4,
  Shoot            = 5,
  Place            = 6,
  FillBottle       = 7,
  FillBucket       = 8,
  PourBucket       = 9,
  UseTool          = 10,
  Interact         = 11,
  Retrieved        = 12,
  Dyed             = 13,
  Traded           = 14
};

class Item {
public:
  virtual ~Item();
  virtual void tearDown();
  virtual int getMaxUseDuration(class ItemInstance const *) const;
  virtual int getMaxUseDuration(class ItemStack const *) const;
  virtual bool isExperimental(class ItemDescriptor const *) const;
  virtual bool isMusicDisk() const;
  virtual class Item &setMaxStackSize(unsigned char);
  virtual class Item &setCategory(enum CreativeItemCategory);
  virtual class Item &setStackedByData(bool);
  virtual class Item &setMaxDamage(int);
  virtual class Item &setHandEquipped(void);
  virtual class Item &setUseAnimation(enum UseAnimation);
  virtual class Item &setMaxUseDuration(int);
  virtual class Item &setRequiresWorldBuilder(bool);
  virtual class Item &setExplodable(bool);
  virtual class Item &setFireResistant(bool);
  virtual class Item &setIsGlint(bool);
  virtual class Item &setShouldDespawn(bool);
  virtual enum BlockShape getBlockShape() const;
  virtual bool canBeDepleted() const;
  virtual bool canDestroySpecial(class Block const &) const;
  virtual int getLevelDataForAuxValue(int) const;
  virtual bool isStackedByData() const;
  virtual short getMaxDamage() const;
  virtual int getAttackDamage() const;
  virtual bool isHandEquipped() const;
  virtual bool isArmor() const;
  virtual bool isDye() const;
  virtual bool isFertilizer(int) const;
  virtual bool isGlint(class ItemStackBase const &) const;
  virtual bool isThrowable() const;
  virtual bool isPattern() const;
  virtual bool showsDurabilityInCreative() const;
  virtual bool isWearableThroughLootTable(std::unique_ptr<class CompoundTag> const &) const;
  virtual bool canDestroyInCreative() const;
  virtual bool isDestructive(int) const;
  virtual bool isLiquidClipItem(int) const;
  virtual bool requiresInteract() const;
  virtual void appendFormattedHovertext(class ItemStackBase const &, class Level &, std::string &, bool) const;
  virtual bool isValidRepairItem(class ItemInstance const &, class ItemInstance const &) const;
  virtual int getEnchantSlot() const;
  virtual int getEnchantValue() const;
  virtual int getArmorValue() const;
  virtual bool isComplex() const;
  virtual bool isValidAuxValue(int) const;
  virtual int getDamageChance(int) const;
  virtual bool uniqueAuxValues() const;
  virtual bool isMultiColorTinted(class ItemStack const &) const;
  virtual class Color getColor(std::unique_ptr<class CompoundTag> const &, class ItemDescriptor const &) const;
  virtual class Color getBaseColor(class ItemStack const &) const;
  virtual class Color getSecondaryColor(class ItemStack const &) const;
  virtual void saveAdditionalData(class ItemStackBase const &, class CompoundTag &) const;
  virtual void readAdditionalData(class ItemStackBase &, class CompoundTag const &) const;
  virtual bool isTintable() const;
  virtual int buildIdAux(short, class CompoundTag const *) const;
  virtual class ItemDescriptor buildDescriptor(short, class CompoundTag const *) const;
  virtual class ItemStack &use(class ItemStack &, class Player &) const;
  virtual bool dispense(class BlockSource &, class Container &, int, class Vec3 const &, unsigned char) const;
  virtual enum ItemUseMethod useTimeDepleted(class ItemStack &, class Level *, class Player *) const;
  virtual void releaseUsing(class ItemStack &, class Player *, int) const;
  virtual float getDestroySpeed(class ItemInstance const &, class Block const &) const;
  virtual void hurtEnemy(class ItemInstance &, class Mob *, class Mob *) const;
  virtual void hurtEnemy(class ItemStack &, class Mob *, class Mob *) const;
  virtual bool mineBlock(class ItemInstance &, class Block const &, int, int, int, class Actor *) const;
  virtual bool mineBlock(class ItemStack &, class Block const &, int, int, int, class Actor *) const;
  virtual std::string
  buildDescriptionId(class ItemDescriptor const &, std::unique_ptr<class CompoundTag> const &) const;
  virtual std::string buildDescriptionId(class ItemDescriptor const &, class CompoundTag const *) const;
  virtual std::string buildEffectDescriptionName(class ItemStackBase const &) const;
  virtual std::string buildCategoryDescriptionName(void) const;
  virtual void readUserData(class ItemStackBase &, class IDataInput &, class ReadOnlyBinaryStream &) const;
  virtual void writeUserData(class ItemStackBase const &, class IDataOutput &) const;
  virtual unsigned char getMaxStackSize(class ItemDescriptor const &) const;
  virtual bool inventoryTick(class ItemStack &, class Level &, class Actor &, int, bool) const;
  virtual void refreshedInContainer(class ItemStackBase &, class Level &) const;
  virtual enum CooldownType getCooldownType() const;
  virtual int getCooldownTime() const;
  virtual void fixupOnLoad(class ItemStackBase &) const;
  virtual void fixupOnLoad(class ItemStackBase &, class Level &) const;
  virtual short getDamageValue(std::unique_ptr<class CompoundTag> const &) const;
  virtual void setDamageValue(class ItemStackBase &, short) const;
  virtual enum InHandUpdateType
  getInHandUpdateType(class Player const &, class ItemInstance const &, class ItemInstance const &, bool, bool) const;
  virtual enum InHandUpdateType
  getInHandUpdateType(class Player const &, class ItemStack const &, class ItemStack const &, bool, bool) const;
  virtual bool isSameItem(class ItemStackBase const &, class ItemStackBase const &) const;
  virtual std::string getInteractText(class Player const &) const;
  virtual int getAnimationFrameFor(class Mob *, bool, class ItemStack const *, bool) const;
  virtual struct Brightness getLightEmission(int) const;
  virtual struct TextureUVCoordinateSet const &getIcon(class ItemStackBase const &, int, bool) const;
  virtual int getIconYOffset() const;
  virtual class Item &setIcon(std::string const &, int);
  virtual class Item &setIcon(struct TextureUVCoordinateSet const &);
  virtual class Item &setIconAtlas(std::string const &, int);
  virtual bool canBeCharged() const;
  virtual void playSoundIncrementally(class ItemInstance const &, class Mob &) const;
  virtual void playSoundIncrementally(class ItemStack const &, class Mob &) const;
  virtual std::string getAuxValuesDescription() const;
  virtual bool
  _checkUseOnPermissions(class Actor &, class ItemInstance &, unsigned char const &, class BlockPos const &) const;
  virtual bool
  _checkUseOnPermissions(class Actor &, class ItemStack &, unsigned char const &, class BlockPos const &) const;
  virtual bool _calculatePlacePos(class ItemInstance &, class Actor &, unsigned char &, class BlockPos &) const;
  virtual bool _calculatePlacePos(class ItemStack &, class Actor &, unsigned char &, class BlockPos &) const;
  virtual bool
  _useOn(class ItemInstance &, class Actor &, class BlockPos, unsigned char, float, float, float) const;
  virtual bool _useOn(class ItemStack &, class Actor &, class BlockPos, unsigned char, float, float, float) const;

  MCAPI class Item &setAllowOffhand(bool);
  MCAPI class Item &setIsMirroredArt(bool);
  MCAPI bool initServer(class Json::Value &);
  MCAPI bool useOn(class ItemStack &, class Actor &, int, int, int, unsigned char, float, float, float) const;
  MCAPI class Item &setMinRequiredBaseGameVersion(class BaseGameVersion const &);
  MCAPI bool updateCustomBlockEntityTag(class BlockSource &, class ItemStack &, class BlockPos &) const;
  MCAPI std::string const &getCommandName() const;
  MCAPI std::string getSerializedName() const;
  MCAPI std::string buildDescriptionName(class ItemStackBase const &) const;

  BASEAPI bool getAllowOffhand() const;
  DEF_FIELD_RW(bool, AllowOffhand);
  BUILD_ACCESS(short, Id, 112);
  BUILD_ACCESS(std::string, RawNameId, 152);
  BUILD_ACCESS(class HashedString *, FullItemName, 216);
  BUILD_ACCESS(class BlockLegacy *, LegacyBlock, 376);
  BUILD_ACCESS(enum CreativeItemCategory, CreativeCategory, 384);
  BUILD_ACCESS(class FoodItemComponent *, Food, 400);
  BUILD_ACCESS(class SeedItemComponent *, Seed, 408);
  BUILD_ACCESS(class CameraItemComponent *, Camera, 416);
};