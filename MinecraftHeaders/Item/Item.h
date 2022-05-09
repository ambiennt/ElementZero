#pragma once

#include "../Math/Vec3.h"
#include "../Core/json.h"
#include "../Core/SemVersion.h"
#include "../Core/HashedString.h"
#include "../dll.h"

#include <memory>
#include <string>
#include <functional>

struct TextureUVCoordinateSet;
class TextureAtlasItem;
class BlockLegacy;
class FoodItemComponent;
class SeedItemComponent;
class CameraItemComponent;

enum class BlockShape;

enum class InHandUpdateType {
	None   = 0,
	Update = 1,
	Swap   = 2
};

enum class CooldownType { // custom items can have custom cooldown types
	None         = -1,
	ChorusFruit  = 0,
	EnderPearl   = 1,
	IceBomb      = 2,
	Count        = 3
};

enum class UseAnimation : int8_t {
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
	virtual std::string buildDescriptionId(class ItemDescriptor const &, std::unique_ptr<class CompoundTag> const &) const;
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
	virtual enum InHandUpdateType getInHandUpdateType(class Player const &, class ItemInstance const &, class ItemInstance const &, bool, bool) const;
	virtual enum InHandUpdateType getInHandUpdateType(class Player const &, class ItemStack const &, class ItemStack const &, bool, bool) const;
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
	virtual bool _checkUseOnPermissions(class Actor &, class ItemInstance &, unsigned char const &, class BlockPos const &) const;
	virtual bool _checkUseOnPermissions(class Actor &, class ItemStack &, unsigned char const &, class BlockPos const &) const;
	virtual bool _calculatePlacePos(class ItemInstance &, class Actor &, unsigned char &, class BlockPos &) const;
	virtual bool _calculatePlacePos(class ItemStack &, class Actor &, unsigned char &, class BlockPos &) const;
	virtual bool _useOn(class ItemInstance &, class Actor &, class BlockPos, unsigned char, float, float, float) const;
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

	enum class Flags {
		mIsGlint = 1,
		mHandEquipped = 2,
		mIsStackedByData = 3,
		mRequiresWorldBuilder = 4,
		mExplodable = 5,
		mFireResistant = 6,
		mShouldDespawn = 7,
		mAllowOffhand = 8,
		mIgnoresPermissions = 9,
		mExperimental = 10
	};

	std::string mTextureAtlasFile; // 0x8
	int32_t mFrameCount; // 0x28
	bool mAnimatesInToolbar; // 0x2C
	bool mIsMirroredArt; // 0x2D
	UseAnimation mUseAnim; // 0x2E
	const char* mHoverTextColorFormat; // 0x30
	const TextureUVCoordinateSet* mIconTexture; // 0x38
	const TextureAtlasItem* mIconAtlas; // 0x40
	bool mUsesRenderingAdjustment; // 0x48
	Vec3 mRenderingAdjTrans; // 0x4C
	Vec3 mRenderingAdjRot; // 0x58
	float mRenderingAdjScale; // 0x64
	uint8_t mMaxStackSize; // 0x68
	int16_t mId; // 0x6A
	std::string mDescriptionId; // 0x70
	std::string mRawNameId; // 0x90
	std::string mNamespace; // 0xB0
	HashedString mFullName; // 0xD0
	int16_t mMaxDamage; // 0xF8
	int16_t mFlags; // 0xFA - bit flags for enum Item::Flags
	int32_t mMaxUseDuration; // 0xFC
	BaseGameVersion mMinRequiredBaseGameVersion; // 0x100
	BlockLegacy* mLegacyBlock; // 0x170
	CreativeItemCategory mCreativeCategory; // 0x178
	Item * mCraftingRemainingItem; // 0x180
	std::unique_ptr<FoodItemComponent> mFoodComponent; // 0x188
	std::unique_ptr<SeedItemComponent> mSeedComponent; // 0x190
	std::unique_ptr<CameraItemComponent> mCameraComponent; // 0x198
	std::vector<std::function<void ()>> mOnResetBAIcallbacks; // 0x1A0

	inline bool hasBitFlag(enum Item::Flags flag) {
		return (this->mFlags & (uint16_t)flag);
	}
};

static_assert(offsetof(Item, mMaxStackSize) == 0x68);
static_assert(offsetof(Item, mId) == 0x6A);
static_assert(offsetof(Item, mRawNameId) == 0x90);
static_assert(offsetof(Item, mFlags) == 0xFA);
static_assert(offsetof(Item, mLegacyBlock) == 0x170);
static_assert(sizeof(Item) == 0x1B8);