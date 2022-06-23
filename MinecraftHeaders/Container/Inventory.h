#pragma once

#include "FillingContainer.h"

class Inventory : public FillingContainer {
	MCAPI void setupDefault();
public:
	MCAPI Inventory(Player *);
	
	virtual int getFirstEmptySlot();
	virtual void setContainerSize(int32_t size);
	
	MCAPI void tick(int32_t selectedSlot);
};