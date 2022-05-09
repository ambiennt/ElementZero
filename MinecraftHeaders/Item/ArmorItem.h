#pragma once

#include "Item.h"
#include "TextureAtlasItem.h"
#include "../dll.h"

enum class ArmorSlot : int32_t;

class ArmorItem : public Item {
public:

	enum class Tier : int32_t {
		TIER_LEATHER   = 0x0,
		TIER_CHAIN     = 0x1,
		TIER_IRON      = 0x2,
		TIER_DIAMOND   = 0x3,
		TIER_GOLD      = 0x4,
		TIER_ELYTRA    = 0x5,
		TIER_TURTLE    = 0x6,
		TIER_NETHERITE = 0x7,
	};

	struct ArmorMaterial {
		int32_t mDurabilityMultiplier;
		int32_t mSlotProtections[4];
		int32_t mEnchantmentValue;
		float mKnockbackResistance;
	};

	ArmorSlot mSlot; // const - 0x1B8
	int32_t mDefense; // const - 0x1BC
	int32_t mModelIndex; // const - 0x1C0
	const ArmorMaterial* mArmorType; // 0x1C8
	TextureAtlasItem mUvTextureItem; // 0x1D0

	virtual float getArmorKnockbackResistance() const;
};

static_assert(offsetof(ArmorItem, mSlot) == 0x1B8);
static_assert(offsetof(ArmorItem, mUvTextureItem) == 0x1D0);
static_assert(sizeof(ArmorItem::ArmorMaterial) == 0x1C);
static_assert(sizeof(ArmorItem) == 0x210);