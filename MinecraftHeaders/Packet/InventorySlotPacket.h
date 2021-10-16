#pragma once

#include "../Core/Packet.h"
#include "../Item/ItemStack.h"
#include "../Core/ContainerID.h"
#include "../dll.h"

class InventorySlotPacket : public Packet {
public:
    ContainerID container_id = ContainerID::Invalid;
    unsigned int slot = 0;
    ItemStack item;

    inline ~InventorySlotPacket() {}

    MCAPI InventorySlotPacket(enum ContainerID container_id, unsigned int slot, ItemStack const &item);

    MCAPI virtual MinecraftPacketIds getId() const;
    MCAPI virtual std::string getName() const;
    MCAPI virtual void write(BinaryStream &) const;
    MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(sizeof(InventorySlotPacket) == 0xC0);