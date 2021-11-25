#pragma once

#include <vector>

#include "../Core/Packet.h"
#include "../Core/mce.h"
#include "../Core/ContainerID.h"
#include "../Item/ItemStack.h"
#include "../dll.h"

class CraftingEventPacket : public Packet {
public:
	enum class Type {
		ShapelessRecipe           = 0,
		ShapedRecipe              = 1,
		FurnaceRecipe             = 2,
		FurnaceAuxRecipe          = 3,
		MultiRecipe               = 4,
		ShulkerBoxRecipe          = 5,
		ShapelessChemistryRecipe  = 6,
		ShapedChemistryRecipe     = 7
	};

	ContainerID mContainerId = ContainerID::Invalid;
	Type mType = Type::ShapelessRecipe; // I definitively can't figure out what this field is for
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