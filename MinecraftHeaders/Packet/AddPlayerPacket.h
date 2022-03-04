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
	std::vector<ActorLink> mLinks{};
	std::string mName{};
	mce::UUID mUUID{};
	ActorUniqueID mEntityId{};
	ActorRuntimeID mRuntimeId{};
	std::string mPlatformOnlineId{};
	Vec3 mPos = Vec3::ZERO, mVelocity = Vec3::ZERO;
	Vec2 mRot = Vec2::ZERO;
	float mYHeadRot = 0.f;
	ItemStack mSelectedItem = ItemStack::EMPTY_ITEM; // mHeldItem
	std::vector<std::unique_ptr<DataItem>> mDataItems{}; // mUnpack - seems to be left empty in favor of mEntityData
	Abilities mAbilities{};
	std::string mDeviceId{};
	BuildPlatform mBuildPlatform = BuildPlatform::Unknown;
	SynchedActorData *mEntityData = nullptr;

	MCAPI AddPlayerPacket(Player &);
	inline ~AddPlayerPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};