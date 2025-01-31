#pragma once

#include <string>
#include <vector>
#include <memory>

#include <modutils.h>

#include "CommandOutputType.h"
#include "CommandOutputParameter.h"
#include "CommandPropertyBag.h"
#include "CommandOutputMessage.h"
#include "../dll.h"

class Actor;

class CommandOutput {
public:
	CommandOutputType type;
	std::unique_ptr<CommandPropertyBag> property_bag;
	std::vector<CommandOutputMessage> messages;
	int32_t successCount;

	MCAPI CommandOutput(CommandOutputType);
	BASEAPI void success();
	MCAPI void success(std::string const &, std::vector<CommandOutputParameter> const &params = {});
	MCAPI void error(std::string const &, std::vector<CommandOutputParameter> const &params = {});
	MCAPI void addToResultList(std::string const &, Actor const &);
	inline void addToResultList(std::string const &key, std::string const &value) {
		if (this->type == CommandOutputType::WithJson) {
			this->property_bag->addToResultList(key, value);
		}
	}
	template <typename T> MCAPI void set(char const *name, T value);

	inline bool wantsData() const {
		return (this->type == CommandOutputType::WithJson);
	}
};

static_assert(sizeof(CommandOutput) == 0x30);