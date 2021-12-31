#pragma once

#include <memory>
#include <string>

#include "../Core/json.h"
#include "../dll.h"

#include <hook.h>
#include <modutils.h>

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

	BASEAPI bool getAllowOffhand() const;
	DEF_FIELD_RW(bool, AllowOffhand);

	BUILD_ACCESS_MUT(std::string, m_textureAtlasFile, 0x8);
	BUILD_ACCESS_MUT(int32_t, m_frameCount, 0x28);
	BUILD_ACCESS_MUT(bool, m_animatesInToolbar, 0x2C);
	BUILD_ACCESS_MUT(bool, mIsMirroredArt, 0x2D);
	BUILD_ACCESS_MUT(enum UseAnimation, mUseAnim, 0x2E);
	BUILD_ACCESS_MUT(const char*, mHoverTextColorFormat, 0x30);
	BUILD_ACCESS_MUT(const struct TextureUVCoordinateSet*, mIconTexture, 0x38);
	BUILD_ACCESS_MUT(const class TextureAtlasItem*, mIconAtlas, 0x40);
	BUILD_ACCESS_MUT(bool, mUsesRenderingAdjustment, 0x48);
	BUILD_ACCESS_MUT(class Vec3, mRenderingAdjTrans, 0x4C);
	BUILD_ACCESS_MUT(class Vec3, mRenderingAdjRot, 0x58);
	BUILD_ACCESS_MUT(float, mRenderingAdjScale, 0x64);
	BUILD_ACCESS_MUT(uint8_t, m_maxStackSize, 0x68);
	BUILD_ACCESS_MUT(int16_t, mId, 0x6A);
	BUILD_ACCESS_MUT(std::string, mDescriptionId, 0x70);
	BUILD_ACCESS_MUT(std::string, mRawNameId, 0x90);
	BUILD_ACCESS_MUT(std::string, mNamespace, 0xB0);
	BUILD_ACCESS_MUT(class HashedString, mFullName, 0xD0);
	BUILD_ACCESS_MUT(int16_t, mMaxDamage, 0xF8);
	//BUILD_ACCESS_MUT(int16_t, _bf_fa, 0xFA); // some random bit flags about the item, like fire resistant or is glint, idk?
	BUILD_ACCESS_MUT(int32_t, mMaxUseDuration, 0xFC);
	BUILD_ACCESS_MUT(class BaseGameVersion, mMinRequiredBaseGameVersion, 0x100);
	BUILD_ACCESS_MUT(class BlockLegacy*, mLegacyBlock, 0x170);
	BUILD_ACCESS_MUT(enum CreativeItemCategory, mCreativeCategory, 0x178);
	BUILD_ACCESS_MUT(class Item *, mCraftingRemainingItem, 0x180);
	BUILD_ACCESS_MUT(std::unique_ptr<class FoodItemComponent>, mFoodComponent, 0x188);
	BUILD_ACCESS_MUT(std::unique_ptr<class SeedItemComponent>, mSeedComponent, 0x190);
	BUILD_ACCESS_MUT(std::unique_ptr<class CameraItemComponent>, mCameraComponent, 0x198);
	BUILD_ACCESS_MUT(std::vector<std::function<void __cdecl(void)>>, mOnResetBAIcallbacks, 0x1A0);
};