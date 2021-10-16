#pragma once

#include "../Core/Packet.h"
#include "../Actor/ActorRuntimeID.h"
#include "../dll.h"

class MobEffectPacket : public Packet {
public:
  ActorRuntimeID runtime_id;
  int effect_duration_ticks;
  int event_id;
  int effect_id;
  int effect_amplifier;
  bool show_particles;

  inline ~MobEffectPacket() {}
  MCAPI virtual MinecraftPacketIds getId() const;
  MCAPI virtual std::string getName() const;
  MCAPI virtual void write(BinaryStream &) const;
  MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(sizeof(MobEffectPacket) == 0x48);