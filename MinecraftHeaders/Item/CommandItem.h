#pragma once

#include "../Item/ItemStack.h"
#include "../Item/ItemInstance.h"
#include "../Command/CommandOutput.h"
#include "../dll.h"

#include <optional>

class CommandItem {
public:

	int32_t mVersion; // 0x0
	int32_t mId; // 0x4

	CommandItem() {}
	CommandItem(int32_t id) : mVersion(0), mId(id) {}
	CommandItem(int32_t vers, int32_t id) : mVersion(vers), mId(id) {}

	MCAPI std::optional<ItemInstance> createInstance(int32_t count, int32_t aux, CommandOutput *output, bool requireExactAux) const;

	inline std::optional<ItemInstance> createInstance(int32_t count, int32_t aux, bool requireExactAux) const {
		return this->createInstance(count, aux, nullptr, requireExactAux);
	}

    // to create an ItemStack instance, default construct an ItemStack then pass in its address as the result
    inline ItemStackBase* createInstance(ItemStackBase *result, int32_t count, int32_t aux, bool requireExactAux) {
        return CallServerClassMethod<ItemStackBase*>(
            "?createInstance@CommandItem@@QEBA?AV?$optional@VItemInstance@@@std@@HHPEAVCommandOutput@@_N@Z",
            this, result, count, aux, nullptr, requireExactAux);
    }
};