#pragma once

#include "../Core/Packet.h"
#include "../Core/ContainerID.h"
#include "../dll.h"

class PlayerHotbarPacket : public Packet {
public:
  unsigned int slot = 0;
  bool selected = false;
  ContainerID container_id = ContainerID::Invalid;

  inline ~PlayerHotbarPacket() {}
  MCAPI virtual MinecraftPacketIds getId() const;
  MCAPI virtual std::string getName() const;
  MCAPI virtual void write(BinaryStream &) const;
  MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};