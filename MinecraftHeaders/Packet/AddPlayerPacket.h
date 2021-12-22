#pragma once

#include <cstdint>
#include <vector>
#include <string>

#include "../Core/Packet.h"
#include "../Core/DataItem.h"
#include "../Core/mce.h"
#include "../Core/BuildPlatform.h"
#include "../Math/Vec3.h"
#include "../Math/Vec2.h"
#include "../Item/ItemStack.h"
#include "../Level/Abilities.h"
#include "../Actor/ActorLink.h"
#include "../Actor/ActorUniqueID.h"
#include "../Actor/ActorRuntimeID.h"
#include "../Actor/SynchedActorData.h"
#include "../dll.h"

class AddPlayerPacket : public Packet {
public:
	std::vector<ActorLink> mLinks;
	std::string mName;
	mce::UUID mUuid;
	ActorUniqueID mEntityId;
	ActorRuntimeID mRuntimeId;
	std::string mPlatformOnlineId;
	Vec3 mPos, mVelocity;
	Vec2 mRot;
	float mYHeadRot = 0.0f;
	ItemStack mSelectedItem; // mHeldItem
	std::vector<std::unique_ptr<DataItem>> mDataItems; // mUnpack
	Abilities mAbilities;
	std::string mDeviceId;
	BuildPlatform mBuildPlatform = BuildPlatform::Unknown;
	SynchedActorData *mEntityData = nullptr;

	inline ~AddPlayerPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};