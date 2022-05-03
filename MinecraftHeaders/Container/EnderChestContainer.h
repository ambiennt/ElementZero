#pragma once

#include "FillingContainer.h"
#include "../BlockActor/ChestBlockActor.h"

class EnderChestContainer : public FillingContainer {
public:
	ChestBlockActor* mActiveChest; // 0x100
};

static_assert(offsetof(EnderChestContainer, mActiveChest) == 0x100);