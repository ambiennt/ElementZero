#pragma once

#include <string>
#include "CommandFlag.h"
#include "CommandPermissionLevel.h"
#include "../dll.h"

class CommandRegistry;
class CommandOrigin;
class CommandOutput;
template <typename T> class CommandSelectorResults;

class Command {
protected:
	int32_t mVersion; // 0x8
	CommandRegistry *mRegistry; // 0x10
	int32_t mCommandSymbol = -1; // 0x18
	CommandPermissionLevel mPermissionLevel = CommandPermissionLevel::Internal; // 0x1C
	CommandFlagValue mFlags; // 0x1D

public:
	virtual ~Command();
	virtual void execute(CommandOrigin const &, CommandOutput &) = 0;

	MCAPI static std::string const WILDCARD_TOKEN;
	MCAPI static bool validRange(int, int, int, class CommandOutput &);
	MCAPI void run(class CommandOrigin const &, class CommandOutput &) const;

	inline int32_t getCommandSymbol() const { return this->mCommandSymbol; }

protected:
	MCAPI static bool isWildcard(class CommandSelectorBase const &);
	MCAPI bool shouldSendTelemetry(class CommandOrigin const &) const;
	MCAPI static bool isTemplateLockedAction(class CommandOrigin const &);
	MCAPI void sendTelemetry(class CommandOrigin const &, class CommandOutput const &) const;
	template <typename T> MCAPI static bool checkHasTargets(CommandSelectorResults<T> const &, CommandOutput &);
};

static_assert(sizeof(Command) == 0x20);