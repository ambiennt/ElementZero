#pragma once

#include "../dll.h"

class CommandItem {
public:
	
	int32_t mVersion; // 0x0
	int32_t mId; // 0x4

	ItemStackBase* createInstance(ItemStackBase *is, int count, int aux, CommandOutput &output, bool exactAux) {
        return CallServerClassMethod<ItemStackBase *>(
            "?createInstance@CommandItem@@QEBA?AV?$optional@VItemInstance@@@std@@HHPEAVCommandOutput@@_N@Z", this, is,
        	count, aux, &output, exactAux);
    }
};