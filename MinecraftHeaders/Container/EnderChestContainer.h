#pragma once

#include "FillingContainer.h"
#include "../BlockActor/ChestBlockActor.h"

class EnderChestContainer : public FillingContainer {
public:
	ChestBlockActor* mActiveChest; // 0x100

	MCAPI virtual void startOpen(Player &) override;
	MCAPI virtual void stopOpen(Player &) override;
};

static_assert(offsetof(EnderChestContainer, mActiveChest) == 0x100);