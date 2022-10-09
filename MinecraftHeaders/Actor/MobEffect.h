#pragma once

#include "../Core/Color.h"
#include "../Core/HashedString.h"
#include "MobEffectID.h"
#include "Attribute.h"
#include "../dll.h"

#include <vector>
#include <memory>

class Actor;
class ResourcePackManager;

class MobEffect {
public:
	const MobEffectID mId; // 0x8 - const uint32_t
	bool mIsHarmful; // 0xC
	Color mColor; // 0x10
	std::string mDescriptionId; // 0x20
	int32_t mIcon; // 0x40
	float mDurationModifier; // 0x44
	bool mIsDisabled; // 0x48
	std::string mResourceName; // 0x50
	std::string mIconName; // 0x70
	bool mEffectVisible; // 0x90
	HashedString mComponentName; // 0x98
	std::shared_ptr<Amplifier> mValueAmplifier; // 0xC0
	std::shared_ptr<Amplifier> mDurationAmplifier; // 0xD0
	std::vector<std::pair<Attribute const*, std::shared_ptr<AttributeBuff>>> mAttributeBuffs; // 0xE0
	std::vector<std::pair<Attribute const*, std::shared_ptr<AttributeModifier>>> mAttributeModifiers; // 0xF8

	MCAPI MobEffect(int32_t id, std::string const& resourceName, std::string const& locName,
		bool isHarmful, int32_t color, int32_t icon, std::string const& iconName, bool drawParticles);

	virtual ~MobEffect();
	virtual void applyEffects(Actor*, int32_t, int32_t) const;
	virtual void removeEffects(Actor*);
	virtual void applyInstantaneousEffect(Actor*, Actor*, Actor*, int32_t, float) const;
	virtual bool isInstantaneous() const;
	virtual float getAttributeModifierValue(int32_t, AttributeModifier const&) const;
	
	MCAPI void addAttributeBuff(Attribute const&, std::shared_ptr<AttributeBuff>);
	MCAPI void addAttributeModifier(Attribute const&, std::shared_ptr<AttributeModifier>);
	MCAPI static MobEffect* getById(int32_t);
	MCAPI static MobEffect* getByName(std::string const&);
	MCAPI class HashedString const& getComponentName() const;
	MCAPI std::string const& getDescriptionId() const;
	MCAPI float getDurationModifier() const;
	MCAPI uint32_t getId() const;
	MCAPI std::string const& getResourceName() const;
	MCAPI static void initEffects(ResourcePackManager*);
	MCAPI bool isHarmful() const;
	MCAPI bool isVisible() const;
	MCAPI static std::unique_ptr<MobEffect> mMobEffects;
	MCAPI void setDurationAmplifier(std::shared_ptr<Amplifier>);
	MCAPI void setValueAmplifier(std::shared_ptr<Amplifier>);
	MCAPI static void shutdownEffects();
	MCAPI std::vector<std::pair<Attribute const*, std::shared_ptr<AttributeModifier>>> const& viewAttributeModifiers() const;

	MCAPI static Color const DEFAULT_COLOR;
	MCAPI static MobEffect* ABSORPTION;
	MCAPI static MobEffect* BAD_OMEN;
	MCAPI static MobEffect* DAMAGE_BOOST;
	MCAPI static MobEffect* MOVEMENT_SLOWDOWN;
	MCAPI static MobEffect* BLINDNESS;
	MCAPI static MobEffect* CONDUIT_POWER;
	MCAPI static MobEffect* CONFUSION;
	MCAPI static MobEffect* DAMAGE_RESISTANCE;
	MCAPI static MobEffect* DIG_SLOWDOWN;
	MCAPI static MobEffect* DIG_SPEED;
	MCAPI static MobEffect* EMPTY_EFFECT;
	MCAPI static MobEffect* FATAL_POISON;
	MCAPI static MobEffect* FIRE_RESISTANCE;
	MCAPI static MobEffect* HARM;
	MCAPI static MobEffect* HEAL;
	MCAPI static MobEffect* HEALTH_BOOST;
	MCAPI static MobEffect* HERO_OF_THE_VILLAGE;
	MCAPI static MobEffect* HUNGER;
	MCAPI static MobEffect* INVISIBILITY;
	MCAPI static MobEffect* JUMP;
	MCAPI static MobEffect* LEVITATION;
	MCAPI static MobEffect* MOVEMENT_SPEED;
	MCAPI static MobEffect* NIGHT_VISION;
	MCAPI static MobEffect* POISON;
	MCAPI static MobEffect* REGENERATION;
	MCAPI static MobEffect* SATURATION;
	MCAPI static MobEffect* SLOW_FALLING;
	MCAPI static MobEffect* WATER_BREATHING;
	MCAPI static MobEffect* WEAKNESS;
	MCAPI static MobEffect* WITHER;
};

static_assert(offsetof(MobEffect, mDurationModifier) == 0x44);
static_assert(offsetof(MobEffect, mIconName) == 0x70);
static_assert(offsetof(MobEffect, mValueAmplifier) == 0xC0);
static_assert(offsetof(MobEffect, mDurationAmplifier) == 0xD0);
static_assert(offsetof(MobEffect, mAttributeBuffs) == 0xE0);
static_assert(offsetof(MobEffect, mAttributeModifiers) == 0xF8);
static_assert(sizeof(MobEffect) == 0x110);

class MobEffectInstance {
public:
	MobEffectID mId; // 0x0
	int32_t mDuration, mDurationEasy, mDurationNormal, mDurationHard, mAmplifier; // 0x4, 0x8, 0xC, 0x10, 0x14
	bool mDisplayOnScreenTextureAnimation, mAmbient, mNoCounter, mEffectVisible; // 0x18, 0x19, 0x1A, 0x1C

	MCAPI static const MobEffectInstance NO_EFFECT;
	static constexpr inline int32_t MAX_AMPLIFIER_COUNT = 5;

	MobEffectInstance(
		MobEffectID id, int32_t dur, int32_t durEasy, int32_t durNormal, int32_t durHard,
		int32_t amplifier, bool displayAnim, bool ambient, bool noCounter, bool visible) :
		mId(id), mDuration(dur), mDurationEasy(durEasy), mDurationNormal(durNormal),
		mDurationHard(durHard), mAmplifier(amplifier), mDisplayOnScreenTextureAnimation(displayAnim),
		mAmbient(ambient), mNoCounter(noCounter), mEffectVisible(visible) {}
	MobEffectInstance() : MobEffectInstance(MobEffectID::Empty, 0, 0, 0, 0, 0, false, false, false, true) {}
	MobEffectInstance(MobEffectID id) : MobEffectInstance(id, 0, 0, 0, 0, 0, false, false, false, true) {}
	MobEffectInstance(MobEffectID id, int32_t dur, int32_t amplifier, bool visible) :
		MobEffectInstance(id, dur, dur, dur, dur, amplifier, false, false, false, visible) {}

	inline bool operator==(MobEffectInstance const &rhs) const {
		return (this->mId == rhs.mId);
	}
	inline bool operator!=(MobEffectInstance const &rhs) const {
		return !(*this == rhs);
	}
};

static_assert(offsetof(MobEffectInstance, mDurationHard) == 0x10);
static_assert(offsetof(MobEffectInstance, mDisplayOnScreenTextureAnimation) == 0x18);
static_assert(offsetof(MobEffectInstance, mEffectVisible) == 0x1B);
static_assert(sizeof(MobEffectInstance) == 0x1C);