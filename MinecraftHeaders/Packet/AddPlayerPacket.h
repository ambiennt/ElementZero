#pragma once

#include <cstdint>

#include "../Core/Packet.h"
#include "../Core/mce.h"
#include "../Math/Vec3.h"
#include "../Math/Vec2.h"
#include "../Item/ItemStack.h"
#include "../Level/Abilities.h"
#include "../Actor/ActorLink.h"
#include "../Actor/ActorUniqueID.h"
#include "../Actor/ActorRuntimeID.h"
#include "../dll.h"

class DataItem;
class SynchedActorData;
enum class BuildPlatform : int32_t;

class AddPlayerPacket : public Packet {
public:
	std::vector<ActorLink> mLinks; // 0x28
	std::string mName; // 0x40
	mce::UUID mUUID; // 0x60
	ActorUniqueID mEntityId; // 0x70
	ActorRuntimeID mRuntimeId; // 0x78
	std::string mPlatformOnlineId; // 0x80
	Vec3 mPos, mVelocity; // 0xA0, 0xAC
	Vec2 mRot; // 0xB8
	float mYHeadRot; // 0xC0
	ItemStack mSelectedItem; // mHeldItem - 0xC8
	std::vector<std::unique_ptr<DataItem>> mDataItems; // mUnpack - seems to be left empty in favor of mEntityData - 0x158
	Abilities mAbilities; // 0x170
	std::string mDeviceId; // 0x2B0
	BuildPlatform mBuildPlatform; // 0x2D0
	SynchedActorData *mEntityData; // 0x2D8

	MCAPI AddPlayerPacket(Player &);
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(sizeof(AddPlayerPacket) == 0x2E0);