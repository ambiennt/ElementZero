#pragma once

#include "../dll.h"
#include "../Actor/MobEffect.h"

class Potion {
public:

	enum class PotionVariant {
		MOVESLOW = 0x0,
		MOVESPEED = 0x1,
		DIGSLOW = 0x2,
		DIGSPEED = 0x3,
		DAMAGEBOOST = 0x4,
		HEAL = 0x5,
		HARM = 0x6,
		JUMP = 0x7,
		CONFUSION = 0x8,
		REGEN = 0x9,
		RESISTANCE = 0xA,
		FIRERESISTANCE = 0xB,
		WATERBREATH = 0xC,
		INVISIBILITY = 0xD,
		BLINDNESS = 0xE,
		NIGHTVISION = 0xF,
		HUNGER = 0x10,
		WEAKNESS = 0x11,
		POISON = 0x12,
		WITHER = 0x13,
		HEALTHBOOST = 0x14,
		ABSORPTION = 0x15,
		SATURATION = 0x16,
		LEVITATION = 0x17,
		TURTLEMASTER = 0x18,
		SLOWFALL = 0x19,
		BASE = 0x1A,
	};

	int32_t mId; // 0x0
	std::string mNameId; // 0x8
	std::string mPrefix; // 0x28
	std::vector<MobEffectInstance> mEffects; // 0x48
	std::vector<std::string> mDescriptionIds; // 0x60
	uint8_t mVar[4]; // 0x78

	MCAPI static int32_t mLastId;

	inline static int32_t getLastId() { return mLastId; }
};

static_assert(offsetof(Potion, mId) == 0x0);
static_assert(offsetof(Potion, mNameId) == 0x8);
static_assert(offsetof(Potion, mPrefix) == 0x28);
static_assert(offsetof(Potion, mEffects) == 0x48);
static_assert(offsetof(Potion, mDescriptionIds) == 0x60);
static_assert(offsetof(Potion, mVar) == 0x78);
static_assert(sizeof(Potion) == 0x80);