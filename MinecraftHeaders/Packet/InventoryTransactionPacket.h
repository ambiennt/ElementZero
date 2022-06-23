#pragma once

#include "../Core/Packet.h"
#include "../Inventory/InventoryTransaction.h"
#include "../dll.h"

#include <memory>
#include <unordered_map>
#include <vector>
#include <functional>

class InventoryTransactionPacket : public Packet {
public:
	SimpleClientNetId<ItemStackLegacyRequestIdTag, int32_t, 0> mLegacyRequestId;
	std::vector<std::pair<ContainerEnumName, std::vector<uint8_t>>> mLegacySetItemSlots;
	std::unique_ptr<ComplexInventoryTransaction> mTransaction;
	bool mIsClientSide = false;

	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(InventoryTransactionPacket, mLegacyRequestId) == 0x28);
static_assert(offsetof(InventoryTransactionPacket, mLegacySetItemSlots) == 0x30);
static_assert(offsetof(InventoryTransactionPacket, mTransaction) == 0x48);
static_assert(offsetof(InventoryTransactionPacket, mIsClientSide) == 0x50);