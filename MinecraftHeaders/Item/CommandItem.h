#pragma once

#include "../dll.h"
#include "../Item/ItemStack.h"
#include "../Command/CommandOutput.h"

class CommandItem {
public:
	
	int32_t mVersion; // 0x0
	int32_t mId; // 0x4

	inline ItemStackBase* createInstance(ItemStackBase *is, int count, int aux, CommandOutput &output, bool requireExactAux) {
        return CallServerClassMethod<ItemStackBase *>(
            "?createInstance@CommandItem@@QEBA?AV?$optional@VItemInstance@@@std@@HHPEAVCommandOutput@@_N@Z", this, is,
        	count, aux, &output, requireExactAux);
    }

    inline ItemStackBase* createInstanceWithoutCommand(ItemStackBase *is, int count, int aux, bool requireExactAux) {
        return CallServerClassMethod<ItemStackBase *>(
            "?createInstance@CommandItem@@QEBA?AV?$optional@VItemInstance@@@std@@HHPEAVCommandOutput@@_N@Z", this, is,
        	count, aux, nullptr, requireExactAux);
    }
};