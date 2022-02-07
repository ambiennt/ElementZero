#pragma once

#include "../Core/mce.h"
#include "../Core/Packet.h"
#include "../Actor/Skin/SerializedSkin.h"
#include "../dll.h"

class PlayerSkinPacket : public Packet {
public:
	mce::UUID mUUID;
	SerializedSkin mSkin;
	std::string mLocalizedNewSkinName, mLocalizedOldSkinName;

	PlayerSkinPacket(mce::UUID uuid, SerializedSkin skin, std::string newName, std::string oldName) :
		mUUID(uuid), mSkin(skin), mLocalizedNewSkinName(newName), mLocalizedOldSkinName(oldName) {}
	inline ~PlayerSkinPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(PlayerSkinPacket, mUUID) == 0x28);
static_assert(offsetof(PlayerSkinPacket, mSkin) == 0x38);
static_assert(offsetof(PlayerSkinPacket, mLocalizedNewSkinName) == 0x208);
static_assert(offsetof(PlayerSkinPacket, mLocalizedOldSkinName) == 0x228);