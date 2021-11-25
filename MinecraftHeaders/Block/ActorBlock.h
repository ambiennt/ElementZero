#pragma once

#include "BlockLegacy.h"

enum class BlockActorRendererId {
	DEFAULT_RENDERER       = 0,
	CHEST_RENDERER         = 1,
	SIGN_RENDERER          = 2,
	MOBSPAWNER_RENDERER    = 3,
	SKULL_RENDERER         = 4,
	ENCHANTER_RENDERER     = 5,
	PISTONARM_RENDERER     = 6,
	ITEMFRAME_RENDERER     = 7,
	MOVINGBLOCK_RENDERER   = 8,
	CHALKBOARD_RENDERER    = 9,
	BEACON_RENDERER        = 10,
	ENDGATEWAY_RENDERER    = 11,
	ENDERCHEST_RENDERER    = 12,
	SHULKERBOX_RENDERER    = 13,
	COMMANDBLOCK_RENDERER  = 14,
	BED_RENDERER           = 15,
	BANNER_RENDERER        = 16,
	CONDUIT_RENDERER       = 17,
	LECTERN_RENDERER       = 18,
	BELL_RENDERER          = 19,
	CAMPFIRE_RENDERER      = 20
};

class ActorBlock : public BlockLegacy {
public:
	MCAPI virtual class ItemInstance getEntityResourceItem(class Random &, class BlockActor const &, int) const;
};