#pragma once

#include <cstdint>
#include <vector>
#include <memory>

#include "../Core/Packet.h"
#include "../Core/DataItem.h"
#include "../Math/Vec3.h"
#include "../Actor/ActorUniqueID.h"
#include "../Actor/ActorRuntimeID.h"
#include "../Item/ItemStack.h"
#include "../Actor/SynchedActorData.h"
#include "../dll.h"

class AddItemActorPacket : public Packet {
public:
	std::vector<std::unique_ptr<DataItem>> mData;
	SynchedActorData* mEntityData = nullptr;
	ActorUniqueID mId;
	ActorRuntimeID mRuntimeId;
	ItemStack mItem;
	Vec3 mPos, mVelocity;
	bool mIsFromFishing = false;

	inline ~AddItemActorPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(AddItemActorPacket, mEntityData) == 0x40);
static_assert(offsetof(AddItemActorPacket, mIsFromFishing) == 0x100);