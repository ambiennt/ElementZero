#pragma once

#include "../dll.h"
#include "CommandSelector.h"

class CommandMessage {
public:

	struct MessageComponent {
		std::string mString; // 0x0
		std::unique_ptr<CommandSelector<Actor>> mSelection; // 0x20
	};

	std::vector<MessageComponent> mData; // 0x0

	MCAPI std::string getMessage(CommandOrigin const &) const;
};

static_assert(sizeof(CommandMessage::MessageComponent) == 0x28);
static_assert(sizeof(CommandMessage) == 0x18);