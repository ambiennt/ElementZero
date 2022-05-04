#pragma once

#include "BlockLegacy.h"

class ItemInstance;
class Random;
class BlockActor;

class ActorBlock : public BlockLegacy {
public:
	virtual ItemInstance getEntityResourceItem(Random &, BlockActor const &, int) const;
};