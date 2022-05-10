#pragma once

#include <chrono>
#include <memory>
#include <vector>
#include <string>

#include "../Level/Tick.h"
#include "../Core/json.h"
#include "../Core/NBT.h"
#include "../Core/WeakPtr.h"
#include "../Block/LegacyBlockID.h"
#include "../Block/Block.h"
#include "../Block/BlockLegacy.h"
#include "ItemStackNetIdVariant.h"
#include "ItemRuntimeID.h"
#include "../dll.h"

#include <hook.h>
#include <modutils.h>

class Item;
class Block;
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

	WeakPtr<Item> mItem; // 0x8
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
	std::unique_ptr<ItemInstance> mChargedItem; // 0x80

	MCAPI virtual ~ItemStackBase();

	MCAPI bool isNull() const;
	MCAPI bool isBlock() const;
	MCAPI bool isDamaged() const;
	MCAPI bool isEnchanted() const;
	MCAPI bool isPotionItem() const;
	MCAPI bool isExperimental() const;
	MCAPI bool isWearableItem() const;
	MCAPI bool isStackedByData() const;
	MCAPI bool isHorseArmorItem() const;
	MCAPI bool isStackable(class ItemStackBase const &) const;

	MCAPI std::string toString() const;

	MCAPI short getId() const; // item id
	MCAPI int getIdAux() const; // assume item id x 65536
	MCAPI class Item const *getItem() const;
	MCAPI short getAuxValue() const; // example: dye has aux values 0-15 (same as mAuxValue)
	MCAPI class ItemDescriptor getDescriptor() const;
	MCAPI unsigned char getMaxStackSize() const;
	MCAPI class ItemEnchants constructItemEnchantsFromUserData() const;
	MCAPI std::string getName() const;
	MCAPI std::string getHoverName() const;
	MCAPI std::string getRawNameId() const;
	MCAPI std::string getCustomName() const;
	MCAPI std::string getDescriptionId() const;
	MCAPI std::unique_ptr<class CompoundTag> getNetworkUserData() const;

	MCAPI bool hasCustomHoverName() const;
	MCAPI bool hasSameAuxValue(class ItemStackBase const &) const;
	MCAPI bool hasSameUserData(class ItemStackBase const &) const;

	MCAPI void set(const int32_t amount);
	MCAPI void setNull();
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

	MCAPI std::unique_ptr<class CompoundTag> save() const;

	MCAPI bool sameItem(int, int) const;
	MCAPI bool matches(class ItemStackBase const &) const;
	MCAPI void setRepairCost(int);
	MCAPI void clearChargedItem();
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
	inline bool operator!=(ItemStackBase const &rhs) const {
		return !(*this == rhs);
	}

	inline bool isBlockItem() const {
		return (this->mBlock && this->mBlock->mLegacyBlock);
	}

	inline ItemRuntimeID getIdAsEnum() const {
		return (ItemRuntimeID)this->getId();
	}

	inline uint16_t toBlockId() const {
		if (!this->isBlockItem()) return 0;
		return this->mBlock->mLegacyBlock->mId;
	}

	inline LegacyBlockID toBlockIdAsEnum() const {
		return (LegacyBlockID)this->toBlockId();
	}

};
class ItemStack : public ItemStackBase {
public:

	ItemStackNetIdVariant mNetIdVariant; // 0x88

	MCAPI static ItemStack const EMPTY_ITEM;

	MCAPI ItemStack();
	MCAPI ItemStack(ItemStack const& rhs);
	MCAPI ItemStack(Item const &item);
	MCAPI ItemStack(Item const &item, int count);
	MCAPI ItemStack(Item const &item, int count, int auxValue);
	MCAPI ItemStack(Block const &block, int count, CompoundTag const *userData);
	MCAPI ItemStack(BlockLegacy const &block, int count);
	MCAPI ~ItemStack();
	MCAPI static ItemStack fromTag(CompoundTag const &userData);
	MCAPI void reinit(Item const &item, int count, int auxValue);
	MCAPI void reinit(BlockLegacy const &block, int count);
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