#pragma once

#include "BlockLegacy.h"

enum class BlockActorRendererId {
  TR_DEFAULT_RENDERER       = 0,
  TR_CHEST_RENDERER         = 1,
  TR_SIGN_RENDERER          = 2,
  TR_MOBSPAWNER_RENDERER    = 3,
  TR_SKULL_RENDERER         = 4,
  TR_ENCHANTER_RENDERER     = 5,
  TR_PISTONARM_RENDERER     = 6,
  TR_ITEMFRAME_RENDERER     = 7,
  TR_MOVINGBLOCK_RENDERER   = 8,
  TR_CHALKBOARD_RENDERER    = 9,
  TR_BEACON_RENDERER        = 10,
  TR_ENDGATEWAY_RENDERER    = 11,
  TR_ENDERCHEST_RENDERER    = 12,
  TR_SHULKERBOX_RENDERER    = 13,
  TR_COMMANDBLOCK_RENDERER  = 14,
  TR_BED_RENDERER           = 15,
  TR_BANNER_RENDERER        = 16,
  TR_CONDUIT_RENDERER       = 17,
  TR_LECTERN_RENDERER       = 18,
  TR_BELL_RENDERER          = 19,
  TR_CAMPFIRE_RENDERER      = 20
};

class ActorBlock : public BlockLegacy {
public:
  MCAPI virtual class ItemInstance getEntityResourceItem(class Random &, class BlockActor const &, int) const;
};