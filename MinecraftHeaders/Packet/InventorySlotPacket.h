#pragma once

#include "../Core/Packet.h"
#include "../Item/ItemStack.h"
#include "../Core/ContainerID.h"
#include "../dll.h"

class InventorySlotPacket : public Packet {
public:
	ContainerID mContainerId = ContainerID::Invalid; // 0x28
	uint32_t mSlot = 0; // 0x2C
	ItemStack mItem; // 0x30

	inline ~InventorySlotPacket() {}

	MCAPI InventorySlotPacket(enum ContainerID containerId, uint32_t slot, ItemStack const &item);

	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(InventorySlotPacket, mContainerId) == 0x28);
static_assert(offsetof(InventorySlotPacket, mSlot) == 0x2C);
static_assert(offsetof(InventorySlotPacket, mItem) == 0x30);