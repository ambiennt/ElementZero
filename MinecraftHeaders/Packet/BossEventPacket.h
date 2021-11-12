#pragma once

#include <cstdint>
#include <string>

#include "../Core/Packet.h"
#include "../Math/BlockPos.h"
#include "../Actor/ActorUniqueID.h"
#include "../dll.h"

enum class BossBarColor {
  PINK    = 0,
  BLUE    = 1,
  RED     = 2,
  GREEN   = 3,
  YELLOW  = 4,
  PURPLE  = 5,
  WHITE   = 6
};

enum class BossBarOverlay {
  Progress    = 0,
  Notched_6   = 1,
  Notched_10  = 2,
  Notched_12  = 3,
  Notched_20  = 4
};

enum class BossEventUpdateType {
  SHOW              = 0, // add
  REGISTER_PLAYER   = 1, // player added
  UPDATE            = 1,
  HIDE              = 2, // remove
  UNREGISTER_PLAYER = 3, // player removed
  HEALTH_PERCENT    = 4, // update percent
  TITLE             = 5, // update name
  TOGGLE_FOG        = 6, // update properties
  TEXTURE           = 7  // update style
};

class BossEventPacket : public Packet {
public:
  int FLAG_DARKEN = 1;
  int FLAG_FOG = 2;
  ActorUniqueID owner, player;
  BossEventUpdateType type;
  std::string name;
  float percent  = 0.0f;
  unsigned color = 0, overlay = 0; // enum BossBarColor, enum BossBarOverlay
  bool darken_sky = false, fog = false;

  inline ~BossEventPacket() {}
  MCAPI virtual MinecraftPacketIds getId() const;
  MCAPI virtual std::string getName() const;
  MCAPI virtual void write(BinaryStream &) const;
  MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(BossEventPacket, owner) == 48);
static_assert(offsetof(BossEventPacket, name) == 72);
static_assert(offsetof(BossEventPacket, percent) == 104);
static_assert(offsetof(BossEventPacket, color) == 108);
static_assert(offsetof(BossEventPacket, overlay) == 112);
static_assert(offsetof(BossEventPacket, darken_sky) == 116);
static_assert(offsetof(BossEventPacket, fog) == 117);