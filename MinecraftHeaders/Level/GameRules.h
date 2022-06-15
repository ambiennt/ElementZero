#pragma once

#include <vector>
#include <string>
#include <functional>

#include "GameRulesIndex.h"
#include "../dll.h"

class GameRulesChangedPacket;
class CompoundTag;
struct GameRulesChangedPacketData;

// annoying bloat
struct GameRuleId {
	int32_t mId; // NewType<int>
	GameRuleId() : mId(0) {}
	GameRuleId(int32_t id) : mId(id) {}
};

class GameRule {
public:

	struct ValidationError {
		bool mSuccess; // 0x0
		std::string mErrorDescription; // 0x8
		std::vector<std::string> mErrorParameters; // 0x28
	};

	enum class Type : int8_t {
		Invalid     = 0,
		BooleanType = 1,
		IntegerType = 2,
		FloatType   = 3
	};

	union Value {
		bool mBoolVal;
		int32_t mIntVal;
		float mFloatVal;
	};

	bool mShouldSave = false; // 0x0
	Type mType = Type::Invalid; // 0x1
	Value mValue{}; // 0x4
	std::string mName; // 0x8
	bool mAllowUseInCommand = false; // 0x28
	bool mIsDefaultSet      = false; // 0x29
	bool mRequiresCheats    = false; // 0x2A
	std::function<void (GameRule &)> mTagNotFoundCallback; // 0x30
	std::function<bool (GameRule::Value const &, GameRule::ValidationError *)> mValidateValueCallback; // 0x70
};

class GameRules {
	MCAPI std::unique_ptr<GameRulesChangedPacket> _setRule(GameRuleId ruleType, GameRule::Value value,
	 	GameRule::Type type, bool returnPacket, bool *pValueValidated, bool *pValueChanged, GameRule::ValidationError *errorOutput);
public:
	std::vector<GameRule> mGameRules; // 0x0

	MCAPI GameRules();
	MCAPI ~GameRules();

	MCAPI GameRule& _registerRule();
	MCAPI void _registerRules();
	MCAPI std::unique_ptr<GameRulesChangedPacket> createAllGameRulesPacket();
	MCAPI void deserializeRules(GameRulesChangedPacketData const &ruleData);
	MCAPI bool getBool(GameRuleId ruleType) const;
	MCAPI int32_t getInt(GameRuleId ruleType) const;
	MCAPI const GameRule* getRule(GameRuleId ruleType) const;
	MCAPI void getTagData(CompoundTag const& tag);
	MCAPI GameRuleId nameToGameRuleIndex(std::string const& name) const; // returns struct GameRuleId but just use enum GameRulesIndex
	MCAPI void setMarketplaceOverrides(); // BLOAT
	MCAPI void setTagData(CompoundTag const& tag);

	MCAPI static int32_t const MAX_FUNCTIONCOMMANDLIMIT = 10000;
	static uint32_t const DEFAULT_PLAYER_SPAWN_RADIUS   = 5;
	static uint32_t const MIN_PLAYER_SPAWN_RADIUS       = 0;
	static uint32_t const MAX_PLAYER_SPAWN_RADIUS       = 128;
	static int32_t const MAX_RANDOMTICKSPEED            = 4096;
	static int32_t const DEFAULT_RANDOMTICKSPEED        = 1;

	inline bool hasRule(GameRulesIndex id) const {
		return ((((int32_t)id) >= 0) && (((int32_t)id) < (int32_t)(this->mGameRules.size())));
	}

	template <typename T> T getGameRuleValue(GameRulesIndex index) const {
		if (!this->hasRule(index)) return T{};
		const auto& rule = this->mGameRules[(int32_t)index];
		switch (rule.mType) {
			case GameRule::Type::BooleanType:
				return static_cast<T>(rule.mValue.mBoolVal);
			case GameRule::Type::IntegerType:
				return static_cast<T>(rule.mValue.mIntVal);
			case GameRule::Type::FloatType:
				return static_cast<T>(rule.mValue.mFloatVal);
			default: return T{};
		}
		return T{};
	}
};

static_assert(offsetof(GameRule, mValue) == 0x4);
static_assert(offsetof(GameRule, mName) == 0x8);
static_assert(offsetof(GameRule, mAllowUseInCommand) == 0x28);
static_assert(offsetof(GameRule, mTagNotFoundCallback) == 0x30);
static_assert(offsetof(GameRule, mValidateValueCallback) == 0x70);

static_assert(sizeof(GameRule) == 0xB0);
static_assert(sizeof(GameRules) == 0x18);