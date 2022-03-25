#pragma once

#include <modutils.h>
#include "AttributeID.h"
#include "ActorUniqueID.h"
#include "../Core/HashedString.h"
#include "../Core/mce.h"

class Mob;

enum class AttributeBuffType {
	Hunger = 0x0,
	Saturation = 0x1,
	Regeneration = 0x2,
	Heal = 0x3,
	Harm = 0x4,
	Magic = 0x5,
	Wither = 0x6,
	Poison = 0x7,
	FatalPoison = 0x8,
	SelfHeal = 0x9,
	Unknown = 0xA,
	None = 0xB,
};

enum class RedefinitionMode : int8_t {
	KeepCurrent = 0x0,
	UpdateToNewDefault = 0x1
};

enum class AttributeModifierOperation {
	OPERATION_ADDITION = 0x0,
	OPERATION_MULTIPLY_BASE = 0x1,
	OPERATION_MULTIPLY_TOTAL = 0x2,
	OPERATION_CAP = 0x3,
	TOTAL_OPERATIONS = 0x4,
	OPERATION_INVALID = 0x4,
};

enum class AttributeOperands {
	OPERAND_MIN = 0x0,
	OPERAND_MAX = 0x1,
	OPERAND_CURRENT = 0x2,
	TOTAL_OPERANDS = 0x3,
	OPERAND_INVALID = 0x3,
};

class Amplifier {
public:

	virtual ~Amplifier();
	virtual float getAmount(int32_t amplification, float scale) { return 0.0f; }
	virtual bool shouldBuff(int32_t remainingDuration, int32_t amplification) { return true; }
	virtual int32_t getTickInterval(int32_t amplification) { return 1; }
};
static_assert(sizeof(Amplifier) == 0x8);

class Attribute {
public:
	RedefinitionMode mRedefinitionMode; // 0x0
	bool mSyncable; // 0x1
	uint32_t mIDValue; // 0x4
	HashedString mName; // 0x8
};
static_assert(offsetof(Attribute, mSyncable) == 0x1);
static_assert(offsetof(Attribute, mIDValue) == 0x4);
static_assert(offsetof(Attribute, mName) == 0x8);
static_assert(sizeof(Attribute) == 0x30);

struct AttributeBuffInfo {
	AttributeBuffType mType; // 0x0
	ActorUniqueID mSource; // 0x8
};
static_assert(offsetof(AttributeBuffInfo, mSource) == 0x8);
static_assert(sizeof(AttributeBuffInfo) == 0x10);

class AttributeBuff {
public:
	float mAmount; // 0x8
	struct AttributeBuffInfo mInfo; // 0x10
	std::shared_ptr<Amplifier> mValueAmplifier; // 0x20
	std::shared_ptr<Amplifier> mDurationAmplifier; // 0x30
	float mScale; // 0x40
	int32_t mAmplification; // 0x44
	uint64_t mId; // 0x48
	int32_t mOperand; // 0x50

	virtual ~AttributeBuff();
	virtual bool isInstantaneous(void) { return false; }
	virtual bool isSerializable(void) { return false; }
	virtual void setDurationAmplifier(std::shared_ptr<class Amplifier>);
};
static_assert(offsetof(AttributeBuff, mAmount) == 0x8);
static_assert(offsetof(AttributeBuff, mInfo) == 0x10);
static_assert(offsetof(AttributeBuff, mValueAmplifier) == 0x20);
static_assert(offsetof(AttributeBuff, mScale) == 0x40);
static_assert(offsetof(AttributeBuff, mId) == 0x48);
static_assert(sizeof(AttributeBuff) == 0x58);

class TemporalAttributeBuff : public AttributeBuff {
public:
	int32_t mDuration; // 0x58
	int32_t mLifeTimer; // 0x5C
	float mBaseAmount; // 0x60
	bool mIsSerializable; // 0x64
};
static_assert(offsetof(TemporalAttributeBuff, mIsSerializable) == 0x64);
static_assert(sizeof(TemporalAttributeBuff) == 0x68);

class AttributeModifier {
public:
	float mAmount; // 0x8
	AttributeModifierOperation mOperation; // 0xC
	AttributeOperands mOperand; // 0x10
	std::string mName; // 0x18
	mce::UUID mId; // 0x38
	bool mSerialize; // 0x48

	virtual ~AttributeModifier();
	virtual bool isInstantaneous(void) { return 0; }
};
static_assert(offsetof(AttributeModifier, mAmount) == 0x8);
static_assert(offsetof(AttributeModifier, mOperation) == 0xC);
static_assert(offsetof(AttributeModifier, mOperand) == 0x10);
static_assert(offsetof(AttributeModifier, mName) == 0x18);
static_assert(offsetof(AttributeModifier, mId) == 0x38);
static_assert(offsetof(AttributeModifier, mSerialize) == 0x48);
static_assert(sizeof(AttributeModifier) == 0x50);

class AttributeInstanceHandle {
public:
	uint32_t mAttributeID; // 0x0
	class BaseAttributeMap* mAttributeMap; // 0x8
};
static_assert(offsetof(AttributeInstanceHandle, mAttributeMap) == 0x8);
static_assert(sizeof(AttributeInstanceHandle) == 0x10);

class AttributeInstanceDelegate {
public:
	AttributeInstanceHandle mAttributeHandle; // 0x8

	virtual ~AttributeInstanceDelegate();
	virtual void tick(void);
	virtual void notify(void);
	virtual void change(float oldValue, float newValue, struct AttributeBuffInfo);
	virtual void getBuffValue(class AttributeBuff const&);
};
static_assert(offsetof(AttributeInstanceDelegate, mAttributeHandle) == 0x8);
static_assert(sizeof(AttributeInstanceDelegate) == 0x18);

class AttributeInstance { // I think ida says the wrong class size, this class disassembles weird
public:
	BaseAttributeMap *mAttributeMap; // 0x8
	const Attribute *mAttribute; // 0x10
	std::vector<AttributeModifier> mModifierList; // 0x18
	std::vector<TemporalAttributeBuff> mTemporalBuffs; // 0x30
	std::vector<AttributeInstanceHandle> mListeners; // 0x48
	std::shared_ptr<AttributeInstanceDelegate> mDelegate; // 0x60
private:
	char unknownGarbage[0x14]; // 0x70
public:
	float mCurrentVal; // 0x84
	float mMin; // 0x88
	float mMax; // 0x8C
	float mDefaultVal; // 0x90

	virtual ~AttributeInstance();
	virtual void tick(void);
};
static_assert(offsetof(AttributeInstance, mAttributeMap) == 0x8);
static_assert(offsetof(AttributeInstance, mAttribute) == 0x10);
static_assert(offsetof(AttributeInstance, mModifierList) == 0x18);
static_assert(offsetof(AttributeInstance, mTemporalBuffs) == 0x30);
static_assert(offsetof(AttributeInstance, mListeners) == 0x48);
static_assert(offsetof(AttributeInstance, mDelegate) == 0x60);
static_assert(offsetof(AttributeInstance, mCurrentVal) == 0x84);

class BaseAttributeMap {
public:
	std::unordered_map<uint32_t, AttributeInstance> mInstanceMap; // 0x0
	std::vector<AttributeInstanceHandle> mDirtyAttributes; // 0x40

	MCAPI AttributeInstance* getMutableInstance(uint32_t id);
};
static_assert(offsetof(BaseAttributeMap, mDirtyAttributes) == 0x40);
static_assert(sizeof(BaseAttributeMap) == 0x58);

class HealthAttributeDelegate : public AttributeInstanceDelegate {
public:
	uint32_t mTickCounter; // 0x18
	Mob* mMob; // 0x20
 };
static_assert(offsetof(HealthAttributeDelegate, mTickCounter) == 0x18);
static_assert(offsetof(HealthAttributeDelegate, mMob) == 0x20);
static_assert(sizeof(HealthAttributeDelegate) == 0x28);