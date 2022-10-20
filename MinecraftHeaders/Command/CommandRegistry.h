#pragma once

#include <vector>
#include <memory>
#include <string>

#include "CommandFlag.h"
#include "CommandVersion.h"
#include "CommandPermissionLevel.h"
#include "../Core/type_id.h"
#include "../dll.h"

class Command;
class CommandOrigin;
class HardNonTerminal;
struct CommandParameterData;

enum class SemanticConstraint : int8_t {
	None = 0x0,
	RequiresCheatsEnabled = 0x1,
	RequiresElevatedPermissions = 0x2,
	RequiresHostPermissions = 0x4,
	VALUE_MASK = 0x7,
};

class CommandRegistry {
public:

	class Symbol {
	public:
		int32_t val;
	};

	struct ParseToken {
		std::unique_ptr<CommandRegistry::ParseToken> child, next; // 0x0, 0x8
		CommandRegistry::ParseToken *parent; // 0x10
		const char *text; // 0x18
		uint32_t length; // 0x20
		CommandRegistry::Symbol type; // 0x24
	};

	struct Overload {
		using FactoryFn = std::unique_ptr<Command>(*)(void);
		CommandVersion version;                   // 0
		FactoryFn factory;                        // 8
		std::vector<CommandParameterData> params; // 16
		int versionOffset;                        // 40

		Overload(CommandVersion version, FactoryFn factory, std::vector<CommandParameterData> &&args)
			: version(version), factory(factory), params(std::move(args)), versionOffset(0xFF) {}
	};

	struct Signature {
		std::string name;                                 // 0
		std::string desc;                                 // 32
		std::vector<CommandRegistry::Overload> overloads; // 64
		CommandPermissionLevel perm;                      // 88
		CommandRegistry::Symbol main_symbol;              // 92
		CommandRegistry::Symbol alt_symbol;               // 96
		CommandFlag flag;                                 // 100
		int firstRule;
		int firstRuleFactorization;
		int firstOptional;
		bool runnable;

		Signature(const std::string& name, const std::string& desc, CommandPermissionLevel perm,
			const CommandRegistry::Symbol& symbol, CommandFlag flag)
			: name(name), desc(desc), perm(perm), main_symbol(symbol), flag(flag) {}
	};

	struct SoftEnum {
		std::string name;              // 0
		std::vector<std::string> list; // 32
	};

	MCAPI void registerCommand(std::string const &, char const *, CommandPermissionLevel, CommandFlag, CommandFlag);
	MCAPI std::string getCommandName(const std::string &commandLine) const;
	MCAPI void registerAlias(std::string name, std::string alias);
	MCAPI int32_t addSoftEnum(std::string const &enumName, std::vector<std::string> values);
	MCAPI int32_t addEnumValues(std::string const &enumName, std::vector<std::string> const &values);
	MCAPI void addSoftEnumValues(std::string const &enumName, std::vector<std::string> values);
	MCAPI void setSoftEnumValues(std::string const &enumName, std::vector<std::string> values);
	MCAPI void removeSoftEnumValues(std::string const &enumName, std::vector<std::string> values);
	MCAPI void addEnumValueConstraints(std::string const &enumName, std::vector<std::string> const &values, SemanticConstraint constraints);

private:
	MCAPI Signature const *findCommand(std::string const &) const;
	MCAPI void registerOverloadInternal(Signature &, Overload &);
	MCAPI std::string symbolToString(CommandRegistry::Symbol symbol) const;

	template <typename Type>
	MCAPI bool parse(void *storage, ParseToken const &token, CommandOrigin const &origin, int32_t version,
		std::string &error, std::vector<std::string> &errorParams) const;

	MCAPI Symbol addEnumValuesInternal(std::string const &, std::vector<std::pair<uint64_t, uint64_t>> const &, typeid_t<CommandRegistry>,
		bool (CommandRegistry::*)(void *, CommandRegistry::ParseToken const &,
		CommandOrigin const &, int32_t, std::string &,std::vector<std::string> &) const);

	MCAPI Symbol addEnumValuesInternal(std::string const &, std::vector<std::pair<std::string, uint64_t>> const &, typeid_t<CommandRegistry>,
		bool (CommandRegistry::*)(void *, CommandRegistry::ParseToken const &, CommandOrigin const &,
		int32_t, std::string &, std::vector<std::string> &) const);

	MCAPI uint64_t getEnumData(CommandRegistry::ParseToken const &) const;

public:
	uint8_t pad[0x2A8];

	template <typename T> inline static auto getParseFn() { return &CommandRegistry::parse<T>; }

	template <typename Type>
	bool fakeparse(void *storage, ParseToken const &token, CommandOrigin const &origin,
		int32_t version, std::string &error, std::vector<std::string> &errorParams) const {
		return false;
	}

	template <typename Type> struct DefaultIdConverter {
		template <typename Target, typename Source>
		static Target convert(Source source) {
			return (Target)source;
		}
		uint64_t operator()(Type value) const { return convert<uint64_t, Type>(value); }
		Type operator()(uint64_t value) const { return convert<Type, uint64_t>(value); }
	};

	template <typename Type, typename IDConverter = CommandRegistry::DefaultIdConverter<Type>>
	bool parseEnum(void *target, CommandRegistry::ParseToken const &token, CommandOrigin const &,
		int32_t, std::string &, std::vector<std::string> &) const {
		auto data = this->getEnumData(token);
		*reinterpret_cast<Type*>(target) = IDConverter{}(data);
		return true;
	}

	template <typename Type, typename IDConverter = CommandRegistry::DefaultIdConverter<Type>>
	uint32_t addEnumValues(std::string const &name, typeid_t<CommandRegistry> tid, std::vector<std::pair<std::string, Type>> const &values) {
		std::vector<std::pair<std::string, uint64_t>> converted;
		IDConverter converter;
		for (auto &value : values) {
			converted.emplace_back(value.first, converter(value.second));
		}
		return this->addEnumValuesInternal(name, converted, tid, &CommandRegistry::parseEnum<Type, IDConverter>).val;
	}

	template <typename T> inline static std::unique_ptr<Command> allocateCommand() {
		return std::make_unique<T>();
	}

	inline void registerOverload(std::string const &name, Overload::FactoryFn factory, std::vector<CommandParameterData> &&args) {
		Signature *signature = const_cast<Signature *>(this->findCommand(name));
		auto &overload       = signature->overloads.emplace_back(CommandVersion{}, factory, std::move(args));
		this->registerOverloadInternal(*signature, overload);
	}

	template <typename T, typename... Params>
	inline void registerOverload(std::string const &name, Params... params) {
		this->registerOverload(name, &allocateCommand<T>, {params...});
	}
};

static_assert(sizeof(CommandRegistry) == 0x2A8);