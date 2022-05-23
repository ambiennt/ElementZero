#pragma once

#include <memory>
#include <functional>

#include "../Core/HashedString.h"
#include "../dll.h"

class CommandContext;
class CommandOutputSender;
class CommandRegistry;
class Minecraft;
class Command;

struct MCRESULT;

enum class CommandPermissionLevel : int8_t;

class MinecraftCommands {
public:
	std::unique_ptr<CommandOutputSender> mOutputSender; // 0x0
	std::unique_ptr<CommandRegistry> mRegistry; // 0x8
	CommandPermissionLevel mOpPermissionLevel; // 0x10
	Minecraft *mMinecraft; // 0x18
	std::function<bool()> mChatPermissionsCallback; // 0x20
	std::unordered_map<HashedString, std::unique_ptr<Command>> mCompiledCommandMap; // 0x60
	bool mExperimentalGameplay; // 0xA0

	MCAPI MCRESULT executeCommand(std::shared_ptr<CommandContext> context, bool suppressOutput) const;
};

static_assert(offsetof(MinecraftCommands, mRegistry) == 0x8);
static_assert(sizeof(MinecraftCommands) == 0xA8);