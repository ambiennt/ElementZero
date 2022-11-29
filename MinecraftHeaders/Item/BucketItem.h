#pragma once

#include "Item.h"
#include "TextureAtlasItem.h"
#include "../dll.h"

// corresponds to the itemstack aux value
enum class BucketFillType : int16_t {
	Unknown = -0x1,
	Empty = 0x0,
	Milk = 0x1,
	Fish = 0x2,
	Salmon = 0x3,
	Tropicalfish = 0x4,
	Pufferfish = 0x5,
	Water = 0x8,
	Lava = 0xA,
};

class BucketItem : public Item {
public:
	TextureUVCoordinateSet mUVBucketEmpty;
	TextureUVCoordinateSet mUVBucketLava;
	TextureUVCoordinateSet mUVBucketMilk;
	TextureUVCoordinateSet mUVBucketWater;
	TextureUVCoordinateSet mUVBucketFish;
	TextureUVCoordinateSet mUVBucketSalmon;
	TextureUVCoordinateSet mUVBucketTropical;
	TextureUVCoordinateSet mUVBucketPuffer;
};

static_assert(sizeof(BucketItem) == 0x478);