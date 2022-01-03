#pragma once

#include <chrono>
#include <memory>
#include <vector>
#include <string>

#include "../Level/Tick.h"
#include "../Core/json.h"
#include "../Core/NBT.h"
#include "ItemStackNetIdVariant.h"
#include "../dll.h"

#include <hook.h>
#include <modutils.h>

class Item;
class Block;
class BlockLegacy;
class CompoundTag;
class IDataOutput;
class IDataInput;
class ItemInstance;
class ItemEnchants;

class ItemStackBase {
public:
	static std::string const TAG_LORE;
	static std::string const TAG_DISPLAY;
	static std::string const TAG_ENCHANTS;
	static std::string const TAG_CAN_DESTROY;
	static std::string const TAG_REPAIR_COST;
	static std::string const TAG_CAN_PLACE_ON;
	static std::string const TAG_DISPLAY_NAME;

protected:
	static std::string const TAG_CHARGED_ITEM;
	static std::string const TAG_STORE_CAN_DESTROY;
	static std::string const TAG_STORE_CAN_PLACE_ON;

public:

	Item* mItem; // 0x8 - WeakPtr<Item>
	std::unique_ptr<CompoundTag> mUserData; // 0x10
	const Block* mBlock; // 0x18
	uint16_t mAuxValue; // 0x20
	uint8_t mCount; // 0x22
	bool mValid; // 0x23
	std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<int64_t, std::ratio<1, 1000000000>>> mPickupTime; // 0x28
	bool mShowPickUp; // 0x30
	bool mWasPickedUp; // 0x31
	std::vector<BlockLegacy *> mCanPlaceOn; // 0x38
	uint64_t mCanPlaceOnHash; // 0x50
	std::vector<BlockLegacy *> mCanDestroy; // 0x58
	uint64_t mCanDestroyHash; // 0x70
	Tick mBlockingTick; // 0x78
	std::unique_ptr<class ItemInstance> mChargedItem; // 0x80

	// causing crashes for some reason
	/*BUILD_ACCESS_MUT(class Item*, mItem, 0x8); // class WeakPtr<class Item>
	BUILD_ACCESS_MUT(std::unique_ptr<class CompoundTag>, mUserData, 0x10);
	BUILD_ACCESS_MUT(const class Block*, mBlock, 0x18);
	BUILD_ACCESS_MUT(uint16_t, mAuxValue, 0x20);
	BUILD_ACCESS_MUT(uint8_t, mCount, 0x22);
	BUILD_ACCESS_MUT(bool, mValid, 0x23);

	using pickupTime1000000000 = std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<int64_t, std::ratio<1, 1000000000>>>;
	BUILD_ACCESS_MUT(pickupTime1000000000, mPickupTime, 0x28);

	BUILD_ACCESS_MUT(bool, mShowPickUp, 0x30);
	BUILD_ACCESS_MUT(bool, mWasPickedUp, 0x31);
	BUILD_ACCESS_MUT(std::vector<class BlockLegacy *>, mCanPlaceOn, 0x38);
	BUILD_ACCESS_MUT(uint64_t, mCanPlaceOnHash, 0x50);
	BUILD_ACCESS_MUT(std::vector<class BlockLegacy *>, mCanDestroy, 0x58);
	BUILD_ACCESS_MUT(uint64_t, mCanDestroyHash, 0x70);
	BUILD_ACCESS_MUT(struct Tick, mBlockingTick, 0x78);
	BUILD_ACCESS_MUT(std::unique_ptr<class ItemInstance>, mChargedItem, 0x80);*/

	MCAPI virtual ~ItemStackBase();

	MCAPI bool isNull(void) const;
	MCAPI bool isBlock(void) const;
	MCAPI bool isDamaged(void) const;
	MCAPI bool isEnchanted(void) const;
	MCAPI bool isPotionItem(void) const;
	MCAPI bool isExperimental(void) const;
	MCAPI bool isWearableItem(void) const;
	MCAPI bool isStackedByData(void) const;
	MCAPI bool isHorseArmorItem(void) const;
	MCAPI bool isStackable(class ItemStackBase const &) const;

	MCAPI std::string toString(void) const;

	MCAPI short getId(void) const;
	MCAPI int getIdAux(void) const;
	MCAPI class Item const *getItem(void) const;
	MCAPI short getAuxValue(void) const;
	MCAPI class ItemDescriptor getDescriptor(void) const;
	MCAPI unsigned char getMaxStackSize(void) const;
	MCAPI class ItemEnchants constructItemEnchantsFromUserData(void) const;
	MCAPI std::string getName(void) const;
	MCAPI std::string getHoverName(void) const;
	MCAPI std::string getRawNameId(void) const;
	MCAPI std::string getCustomName(void) const;
	MCAPI std::string getDescriptionId(void) const;
	MCAPI std::unique_ptr<class CompoundTag> getNetworkUserData(void) const;

	MCAPI bool hasCustomHoverName(void) const;
	MCAPI bool hasSameAuxValue(class ItemStackBase const &) const;
	MCAPI bool hasSameUserData(class ItemStackBase const &) const;

	MCAPI void set(int);
	MCAPI void setNull(void);
	MCAPI void setChargedItem(class ItemInstance const &, bool);
	MCAPI void setCustomName(std::string const &);
	MCAPI void setUserData(std::unique_ptr<class CompoundTag>);
	MCAPI void setCustomLore(std::vector<std::string> const &);

	MCAPI void saveEnchantsToUserData(class ItemEnchants const &);
	MCAPI void addCustomUserData(class BlockActor &, class BlockSource &);

	MCAPI bool hasComponent(std::string const &) const;
	MCAPI bool addComponents(class Json::Value const &, std::string &);
	MCAPI bool updateComponent(std::string const &, class Json::Value const &);

	MCAPI void serializeComponents(class IDataOutput &) const;
	MCAPI void deserializeComponents(class IDataInput &);

	MCAPI std::unique_ptr<class CompoundTag> save(void) const;

	MCAPI bool sameItem(int, int) const;
	MCAPI bool matches(class ItemStackBase const &) const;
	MCAPI void setRepairCost(int);
	MCAPI void clearChargedItem(void);
	MCAPI bool matchesItem(class ItemStackBase const &) const;
	MCAPI bool sameItemAndAux(class ItemStackBase const &) const;
	MCAPI void _write(class BinaryStream &) const;
	MCAPI void hurtAndBreak(int, class Actor *);
	MCAPI void _read(class ReadOnlyBinaryStream &);

	inline uint8_t getStackSize() const { return mCount; }

	inline std::vector<std::string> getCustomLore() const {
		std::vector<std::string> ret;
		if (mUserData && mUserData->contains(TAG_DISPLAY, Tag::Compound)) {
			auto disp = mUserData->getCompound(TAG_DISPLAY);
			if (disp->contains(TAG_LORE, Tag::List)) {
				auto list = disp->getList(TAG_LORE);
				for (auto &item : list->value) ret.emplace_back(static_cast<StringTag *>(item.get())->value);
			}
		}
		return ret;
	}

	MCAPI bool operator!=(ItemStackBase const &rhs) const;
	MCAPI operator bool() const;

protected:
	virtual void reinit(Item const &, int, int) = 0;
	MCAPI ItemStackBase();
	MCAPI ItemStackBase(Item const &item);
	MCAPI ItemStackBase(Item const &ite, int);
	MCAPI ItemStackBase(Item const &ite, int, int);
	MCAPI ItemStackBase(Item const &ite, int, int, CompoundTag const *);
	MCAPI ItemStackBase(BlockLegacy const &, int);
	MCAPI ItemStackBase(Block const &, int, CompoundTag const *);
	MCAPI ItemStackBase(ItemStackBase const &rhs);
	MCAPI ItemStackBase &operator=(ItemStackBase const &rhs);

public:
	virtual void reinit(BlockLegacy const &, int) = 0;

	inline bool operator==(ItemStackBase const &rhs) const {
		return this->matchesItem(rhs);
	}

};
class ItemStack : public ItemStackBase {
public:

	class ItemStackNetIdVariant mNetIdVariant; // 0x88
	//BUILD_ACCESS_MUT(class ItemStackNetIdVariant, mNetIdVariant, 0x88);

	MCAPI static ItemStack const EMPTY_ITEM;

	MCAPI ItemStack();
	ItemStack(Item const &item) : ItemStackBase(item) {}
	MCAPI ItemStack(Item const &, int);
	ItemStack(Item const &item, int a, int b) : ItemStackBase(item, a, b) {}
	ItemStack(Item const &item, int a, int b, CompoundTag const *tag) : ItemStackBase(item, a, b, tag) {}
	ItemStack(BlockLegacy const &block, int a) : ItemStackBase(block, a) {}
	ItemStack(Block const &block, int a, CompoundTag const *tag) : ItemStackBase(block, a, tag) {}
	ItemStack(ItemStack const &rhs) : ItemStackBase(rhs) {}
	MCAPI ~ItemStack();
	MCAPI static ItemStack fromTag(CompoundTag const &);
	MCAPI void reinit(Item const &, int, int);
	MCAPI void reinit(BlockLegacy const &, int);
};

static_assert(offsetof(ItemStackBase, mItem) == 0x8);
static_assert(offsetof(ItemStackBase, mAuxValue) == 0x20);
static_assert(offsetof(ItemStackBase, mPickupTime) == 0x28);
static_assert(offsetof(ItemStackBase, mShowPickUp) == 0x30);
static_assert(offsetof(ItemStackBase, mCanPlaceOnHash) == 0x50);
static_assert(offsetof(ItemStackBase, mCanDestroy) == 0x58);
static_assert(offsetof(ItemStackBase, mCanDestroyHash) == 0x70);
static_assert(offsetof(ItemStackBase, mChargedItem) == 0x80);

static_assert(offsetof(ItemStack, mNetIdVariant) == 0x88);

static_assert(sizeof(ItemStackBase) == 0x88);
static_assert(sizeof(ItemStack) == 0x90);