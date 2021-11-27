#pragma once

#include <vector>

#include "../Core/Packet.h"
#include "../Core/mce.h"
#include "../Core/ContainerID.h"
#include "../Item/ItemStack.h"
#include "../Container/ContainerType.h"
#include "../dll.h"

class CraftingEventPacket : public Packet {
public:

	ContainerID mContainerId = ContainerID::Invalid;
	int32_t mContainerType = (int32_t)ContainerType::CONTAINER; // yes this is not a typo, its actually int32_t
	mce::UUID mRecipeId;
	std::vector<ItemStack> mInputItems, mOutputItems;

	inline ~CraftingEventPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(CraftingEventPacket, mInputItems) == 64);
static_assert(offsetof(CraftingEventPacket, mOutputItems) == 88);