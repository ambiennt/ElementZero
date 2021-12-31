#pragma once

#include "Item.h"
#include "ItemInstance.h"
#include "Actor/Actor.h"
#include "../dll.h"

#include  <modutils.h>

class ArmorItem : public Item {
public:

	enum class Tier {
		TIER_LEATHER   = 0x0,
		TIER_CHAIN     = 0x1,
		TIER_IRON      = 0x2,
		TIER_DIAMOND   = 0x3,
		TIER_GOLD      = 0x4,
		TIER_ELYTRA    = 0x5,
		TIER_TURTLE    = 0x6,
		TIER_NETHERITE = 0x7
	};

	struct ArmorMaterial {
		int32_t mDurabilityMultiplier;
		int32_t mSlotProtections[4];
		int32_t mEnchantmentValue;
		float mKnockbackResistance;
	};

	BUILD_ACCESS_MUT(const enum ArmorSlot, mSlot, 0x1B8);
	BUILD_ACCESS_MUT(const int32_t, mDefense, 0x1BC);
	BUILD_ACCESS_MUT(const int32_t, mModelIndex, 0x1C0);
	BUILD_ACCESS_MUT(const struct ArmorMaterial, mArmorType, 0x1C8);
	BUILD_ACCESS_MUT(class TextureAtlasItem, m_uvTextureItem, 0x1D0);

	// todo: more funcs
	MCAPI virtual bool isFlyEnabled(class ItemInstance const& item);
};