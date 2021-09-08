#pragma once

#include "../Core/Packet.h"
#include "../Math/Vec3.h"
#include "../Actor/ActorRuntimeID.h"
#include "../dll.h"

class MoveActorAbsolutePacket : public Packet {
public:

  enum struct Flags : uint8_t { 
    GROUND = 0x01, 
    TELEPORT = 0x02, 
    FORCE_MOVE = 0x04
  };

  ActorRuntimeID rid;
  uint8_t flags = 0x01;
  Vec3 pos;
  uint8_t pitch = 0, head_yaw = 0, yaw = 0;

  inline ~MoveActorAbsolutePacket() {}
  MCAPI virtual MinecraftPacketIds getId() const;
  MCAPI virtual std::string getName() const;
  MCAPI virtual void write(BinaryStream &) const;
  MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};