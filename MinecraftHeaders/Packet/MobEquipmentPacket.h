#pragma once

#include "../Core/Packet.h"
#include "../Container/ContainerID.h"
#include "../Item/ItemStack.h"
#include "../Actor/ActorRuntimeID.h"
#include "../dll.h"

class MobEquipmentPacket : public Packet {
public:
	ActorRuntimeID mRuntimeId; // 0x28
	ItemStack mItem; // 0x30
	int32_t mInventorysSlot   = 0; // 0xC0
	int32_t mSelectedSlot     = 0; // 0xC4 - hotbar slot
	bool mIsServerSide        = false; // 0xC8
	ContainerID mContainerId  = ContainerID::Invalid; // 0xC9
	uint8_t mSlotByte         = 0; // 0xCA
	uint8_t mSelectedSlotByte = 0; // 0xCB
	uint8_t mContainerIdByte  = 0; // 0xCC

	inline ~MobEquipmentPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(MobEquipmentPacket, mInventorysSlot) == 0xC0);
static_assert(offsetof(MobEquipmentPacket, mContainerIdByte) == 0xCC);
static_assert(sizeof(MobEquipmentPacket) == 0xD0);