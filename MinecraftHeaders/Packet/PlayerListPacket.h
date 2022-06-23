#pragma once

#include <vector>

#include "../Core/Packet.h"
#include "../Core/mce.h"
#include "../Core/BuildPlatform.h"
#include "../Actor/ActorUniqueID.h"
#include "../Actor/Skin/SerializedSkin.h"
#include "../dll.h"

class PlayerListEntry {
public:
	ActorUniqueID mId; // 0x0
	mce::UUID mUUID; // 0x8
	std::string mName, mXUID, mPlatformOnlineId; // 0x18, 0x38, 0x58
	BuildPlatform mBuildPlatform; // 0x78
	SerializedSkin mSkin; // 0x80
	bool mIsTeacher, mIsHost; // 0x250, 0x251

	MCAPI void write(BinaryStream &) const;
	MCAPI StreamReadResult read(ReadOnlyBinaryStream &);
};

// note to self, byte actions like these can either be signed or unsigned if you know their values will be withing 0-127
// but generally I would assume it to be unsigned in low level
// so if you dont have the vanilla enum, use uint8_t
enum PlayerListPacketType : int8_t {
	Add    = 0x0,
	Remove = 0x1
};

class PlayerListPacket : public Packet {
public:

	std::vector<PlayerListEntry> mEntries; // 0x28
	PlayerListPacketType mAction; // 0x40

	PlayerListPacket(std::vector<PlayerListEntry> const& entries, PlayerListPacketType action) : mEntries(entries), mAction(action) {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(PlayerListEntry, mBuildPlatform) == 0x78);