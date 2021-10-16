#pragma once

#include "../Core/Packet.h"
#include "../Core/ContainerID.h"
#include "../Item/ItemStack.h"
#include "../Actor/ActorRuntimeID.h"
#include "../dll.h"

class MobEquipmentPacket : public Packet {
public:
  ActorRuntimeID runtime_id;
  ItemStack item;
  int inventory_slot                = 0;
  int hotbar_slot                   = 0;
  bool is_server_side               = false;
  ContainerID container_id          = ContainerID::Invalid;
  unsigned char slot_byte           = 0;
  unsigned char selected_slot_byte  = 0;
  unsigned char container_id_byte   = 0;

  inline ~MobEquipmentPacket() {}
  MCAPI virtual MinecraftPacketIds getId() const;
  MCAPI virtual std::string getName() const;
  MCAPI virtual void write(BinaryStream &) const;
  MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};