#pragma once

#include <string>
#include <vector>
#include "../Core/type_id.h"
#include "CommandRegistry.h"

enum class CommandParameterOption : int8_t {
	None                      = 0,
	EnumAutocompleteExpansion = 1,
	HasSemanticConstraint     = 2,
};

enum class CommandParameterDataType : int32_t {
	NORMAL   = 0,
	ENUM     = 1,
	SOFTENUM = 2,
	POSTFIX  = 3,
};

struct CommandParameterData {
	using ParseFn = bool(CommandRegistry::*)(void *, const CommandRegistry::ParseToken &,
		const CommandOrigin &, int32_t, std::string &, std::vector<std::string> &) const;

	typeid_t<CommandRegistry> mTypeIndex; // 0x0
	ParseFn mParser; // 0x8
	std::string mName; // 0x10
	const char *mEnumNameOrPostfix; // 0x30
	int32_t mEnumOrPostfixSymbol; // 0x38
	CommandParameterDataType mParamType; // 0x3C
	int32_t mOffset; // 0x40
	int32_t mSetOffset; // 0x44
	bool mIsOptional; // 0x48
	CommandParameterOption mOptions; // 0x49

	CommandParameterData(typeid_t<CommandRegistry> typeIndex, ParseFn parser, std::string name,
		CommandParameterDataType paramType, const char *enumNameOrPostfix, int32_t offset, bool optional, int32_t setOffset)
		: mTypeIndex(typeIndex), mParser(parser), mName(name), mEnumNameOrPostfix(enumNameOrPostfix),
		mEnumOrPostfixSymbol(-1), mParamType(paramType), mOffset(offset),
		mSetOffset(setOffset), mIsOptional(optional), mOptions(CommandParameterOption::None) {}
};

static_assert(sizeof(CommandParameterData) == 0x50);
static_assert(sizeof(CommandParameterData::mParser) == 0x8);