#pragma once

#include "../Core/Packet.h"
#include "../Item/ItemStack.h"
#include "../Core/ContainerID.h"
#include "../dll.h"

class InventorySlotPacket : public Packet {
public:
    char container = 0;
    unsigned int slot = 0;
    ItemStack itemStack;

    inline ~InventorySlotPacket() {}

    MCAPI InventorySlotPacket(enum ContainerID containerId, unsigned int slot, ItemStack const &itemStack);

    MCAPI virtual MinecraftPacketIds getId() const;
    MCAPI virtual std::string getName() const;
    MCAPI virtual void write(BinaryStream &) const;
    MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};