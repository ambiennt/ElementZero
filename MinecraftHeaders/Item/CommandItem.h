#pragma once

#include "../Item/ItemStack.h"
#include "../Item/ItemInstance.h"
#include "../dll.h"

#include <optional>

class CommandOutput;

class CommandItem {
public:
	int32_t mVersion, mId;

	CommandItem(int32_t id) : mVersion(0), mId(id) {}
	CommandItem(int32_t vers, int32_t id) : mVersion(vers), mId(id) {}

	MCAPI std::optional<ItemInstance> createInstance(int32_t count, int32_t aux, CommandOutput *output, bool requireExactAux) const;

	inline std::optional<ItemInstance> createInstance(int32_t count, int32_t aux, bool requireExactAux) const {
		return this->createInstance(count, aux, nullptr, requireExactAux);
	}
};