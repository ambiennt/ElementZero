#pragma once

#include <vector>
#include <string>
#include <functional>

#include "GameRulesIndex.h"
#include "../dll.h"

class GameRule {
public:

	struct ValidationError {
		bool mSuccess; // 0x0
		std::string mErrorDescription; // 0x8
		std::vector<std::string> mErrorParameters; // 0x28
	};

	enum class Type : int8_t {
		Invalid = 0,
		Boolean = 1,
		Integer = 2,
		Float   = 3
	};

	union Value {
		bool val_bool;
		int val_int;
		float val_float;
	};

	bool saved = false; // 0x0
	Type type  = Type::Invalid; // 0x1
	Value value{}; // 0x4
	std::string name; // 0x8
	bool use_in_command = false; // 0x28
	bool default_set    = false; // 0x29
	bool requires_cheat = false; // 0x2A
	std::function<void (GameRule &)> mTagNotFoundCallback; // 0x30
	std::function<bool (GameRule::Value const &, GameRule::ValidationError *)> mValidateValueCallback; // 0x70
};

class GameRules {
public:
	std::vector<GameRule> rules; // 0x0

	MCAPI GameRules();
	MCAPI ~GameRules();

	MCAPI class GameRule& _registerRule(void);
	MCAPI void _registerRules(void);
	/*MCAPI void _setRule(
		int32_t* ruleType, union GameRule::Value value, enum GameRule::Type type, bool returnPacket,
		bool *pValueValidated, bool *pValueChanged, struct GameRule::ValidationError *errorOutput);*/
	MCAPI std::unique_ptr<class GameRulesChangedPacket> createAllGameRulesPacket(void);
	MCAPI void deserializeRules(struct GameRulesChangedPacketData const &ruleData);
	//MCAPI bool getBool(int32_t* ruleType);
	//MCAPI int32_t getInt(int32_t* ruleType);
	//MCAPI const class GameRule* getRule(int32_t* ruleType);
	MCAPI void getTagData(class CompoundTag const& tag);
	MCAPI int32_t nameToGameRuleIndex(std::string const& name); // returns struct GameRuleId but just use enum GameRulesIndex
	MCAPI void setMarketplaceOverrides(void); // BLOAT
	MCAPI void setTagData(class CompoundTag const& tag);

	MCAPI static int32_t const MAX_FUNCTIONCOMMANDLIMIT = 10000;
	static uint32_t const DEFAULT_PLAYER_SPAWN_RADIUS   = 5;
	static uint32_t const MIN_PLAYER_SPAWN_RADIUS       = 0;
	static uint32_t const MAX_PLAYER_SPAWN_RADIUS       = 128;
	static int32_t const MAX_RANDOMTICKSPEED            = 4096;
	static int32_t const DEFAULT_RANDOMTICKSPEED        = 1;

	inline bool getBool(GameRulesIndex id) {
		return CallServerClassMethod<bool>("?getBool@GameRules@@QEBA_NUGameRuleId@@@Z", this, &id);
	}

	inline bool hasRule(GameRulesIndex id) {
		return ((((int) id) >= 0) && (((int) id) < (int)(&this->rules.back() - &this->rules.front())));
	}
};

static_assert(offsetof(GameRule, value) == 0x4);
static_assert(offsetof(GameRule, name) == 0x8);
static_assert(offsetof(GameRule, use_in_command) == 0x28);
static_assert(offsetof(GameRule, mTagNotFoundCallback) == 0x30);
static_assert(offsetof(GameRule, mValidateValueCallback) == 0x70);

static_assert(sizeof(GameRule) == 0xB0);
static_assert(sizeof(GameRules) == 0x18);