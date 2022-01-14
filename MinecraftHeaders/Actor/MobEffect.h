#pragma once

#include <string>
#include <memory>
#include <vector>
#include "Actor.h"
#include "../Core/Color.h"
#include "../Core/HashedString.h"
#include "MobEffectIds.h"
#include "../dll.h"

class AttributeBuff;
class AttributeModifier;

class MobEffect {
public:

	const MobEffectIds mId; // 0x8 (actually a uint32_t)
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
	std::shared_ptr<class Amplifier> mValueAmplifier; // 0xC0
	std::shared_ptr<class Amplifier> mDurationAmplifier; // 0xD0
	std::vector<std::pair<class Attribute const*, std::shared_ptr<class AttributeBuff>>> mAttributeBuffs; // 0xE0
	std::vector<std::pair<class Attribute const*, std::shared_ptr<class AttributeModifier>>> mAttributeModifiers; // 0xF8

	MCAPI MobEffect(int32_t id, std::string const& resourceName, std::string const& locName,
		bool isHarmful, int32_t color, int32_t icon, std::string const& iconName, bool drawParticles);

	virtual ~MobEffect(void);
	virtual void applyEffects(class Actor*, int, int) const;
	virtual void removeEffects(class Actor*);
	virtual void applyInstantaneousEffect(class Actor*, class Actor*, class Actor*, int, float) const;
	virtual bool isInstantaneous(void) const;
	virtual float getAttributeModifierValue(int, class AttributeModifier const&) const;
	
	MCAPI void addAttributeBuff(class Attribute const&, std::shared_ptr<class AttributeBuff>);
	MCAPI void addAttributeModifier(class Attribute const&, std::shared_ptr<class AttributeModifier>);
	MCAPI static class MobEffect* getById(int);
	MCAPI static class MobEffect* getByName(std::string const&);
	MCAPI class HashedString const& getComponentName(void) const;
	MCAPI std::string const& getDescriptionId(void) const;
	MCAPI float getDurationModifier(void) const;
	MCAPI unsigned int getId(void) const;
	MCAPI std::string const& getResourceName(void) const;
	MCAPI static void initEffects(class ResourcePackManager*);
	MCAPI bool isHarmful(void) const;
	MCAPI bool isVisible(void) const;
	MCAPI static std::unique_ptr<class MobEffect> mMobEffects;
	MCAPI void setDurationAmplifier(std::shared_ptr<class Amplifier>);
	MCAPI void setValueAmplifier(std::shared_ptr<class Amplifier>);
	MCAPI static void shutdownEffects(void);
	MCAPI class std::vector<std::pair<class Attribute const*, std::shared_ptr<class AttributeModifier>>> const& viewAttributeModifiers(void) const;

	// MCAPI static class mce::Color const DEFAULT_COLOR;
	MCAPI static class MobEffect* ABSORPTION;
	MCAPI static class MobEffect* BAD_OMEN;
	MCAPI static class MobEffect* DAMAGE_BOOST;
	MCAPI static class MobEffect* MOVEMENT_SLOWDOWN;
	MCAPI static class MobEffect* BLINDNESS;
	MCAPI static class MobEffect* CONDUIT_POWER;
	MCAPI static class MobEffect* CONFUSION;
	MCAPI static class MobEffect* DAMAGE_RESISTANCE;
	MCAPI static class MobEffect* DIG_SLOWDOWN;
	MCAPI static class MobEffect* DIG_SPEED;
	MCAPI static class MobEffect* EMPTY_EFFECT;
	MCAPI static class MobEffect* FATAL_POISON;
	MCAPI static class MobEffect* FIRE_RESISTANCE;
	MCAPI static class MobEffect* HARM;
	MCAPI static class MobEffect* HEAL;
	MCAPI static class MobEffect* HEALTH_BOOST;
	MCAPI static class MobEffect* HERO_OF_THE_VILLAGE;
	MCAPI static class MobEffect* HUNGER;
	MCAPI static class MobEffect* INVISIBILITY;
	MCAPI static class MobEffect* JUMP;
	MCAPI static class MobEffect* LEVITATION;
	MCAPI static class MobEffect* MOVEMENT_SPEED;
	MCAPI static class MobEffect* NIGHT_VISION;
	MCAPI static class MobEffect* POISON;
	MCAPI static class MobEffect* REGENERATION;
	MCAPI static class MobEffect* SATURATION;
	MCAPI static class MobEffect* SLOW_FALLING;
	MCAPI static class MobEffect* WATER_BREATHING;
	MCAPI static class MobEffect* WEAKNESS;
	MCAPI static class MobEffect* WITHER;
};

static_assert(offsetof(MobEffect, mDurationModifier) == 0x44);
static_assert(offsetof(MobEffect, mIconName) == 0x70);
static_assert(offsetof(MobEffect, mValueAmplifier) == 0xC0);
static_assert(offsetof(MobEffect, mDurationAmplifier) == 0xD0);
static_assert(offsetof(MobEffect, mAttributeBuffs) == 0xE0);
static_assert(offsetof(MobEffect, mAttributeModifiers) == 0xF8);

class MobEffectInstance {
public:
	MobEffectIds mId        = MobEffectIds::Empty; // 0x0 (actually a uint32_t)
	int32_t mDuration       = 0; // 0x4 - in ticks
	int32_t mDurationEasy   = 0; // 0x8 - in ticks
	int32_t mDurationNormal = 0; // 0xC - in ticks
	int32_t mDurationHard   = 0; // 0x10 - in ticks
	int32_t mAmplifier      = 0; // 0x14
	bool mDisplayOnScreenTextureAnimation = false; // 0x18 - ex: hero of the village animation
	bool mAmbient           = false; // 0x19 - not sure what this does
	bool mNoCounter         = false; // 0x1A - unlimited duration? needs testing
	bool mEffectVisible     = true; // 0x1C - show effect particle

	MCAPI static MobEffectInstance NO_EFFECT;
	static const int32_t MAX_AMPLIFIER_COUNT = 5;

	MobEffectInstance(
		MobEffectIds id, int32_t dur, int32_t durEasy, int32_t durNormal, int32_t durHard,
		int32_t amplifier, bool displayAnim, bool ambient, bool noCounter, bool visible) :
		mId(id), mDuration(dur), mDurationEasy(durEasy), mDurationNormal(durNormal), mDurationHard(durHard), mAmplifier(amplifier),
		mDisplayOnScreenTextureAnimation(displayAnim), mAmbient(ambient), mNoCounter(noCounter), mEffectVisible(visible) {}
	MobEffectInstance(MobEffectIds id, int32_t dur, int32_t amplifier, bool visible) {
		mId = id;
		mDuration = mDurationEasy = mDurationNormal = mDurationHard = dur;
		mAmplifier = amplifier;
		mEffectVisible = visible;
	}
	MobEffectInstance(MobEffectIds id) : mId(id) {}
};

static_assert(offsetof(MobEffectInstance, mDurationHard) == 0x10);
static_assert(offsetof(MobEffectInstance, mDisplayOnScreenTextureAnimation) == 0x18);
static_assert(offsetof(MobEffectInstance, mEffectVisible) == 0x1B);
static_assert(sizeof(MobEffectInstance) == 0x1C);