#pragma once

#include "../Item/ItemStack.h"
#include "../Core/ContainerID.h"
#include "../Core/Packet.h"

class InventoryContentPacket : public Packet {
public:

    ContainerID id;                // 0x28 - mInventoryId
    std::vector<ItemStack> items;  // 0x30 - mSlots

    inline ~InventoryContentPacket() {}

    InventoryContentPacket(void);
    InventoryContentPacket(ContainerID containerId, std::vector<class ItemStack> const & items);

    MCAPI virtual MinecraftPacketIds getId() const;
    MCAPI virtual std::string getName() const;
    MCAPI virtual void write(BinaryStream &) const;
    MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(InventoryContentPacket, id) == 40);
static_assert(offsetof(InventoryContentPacket, items) == 48);