#pragma once

#include "FillingContainer.h"

class Inventory : public FillingContainer {
	MCAPI void setupDefault();
public:
	MCAPI Inventory(Player *);
	
	virtual int getFirstEmptySlot();
	virtual void setContainerSize(int);
	
	MCAPI void tick(int);
};