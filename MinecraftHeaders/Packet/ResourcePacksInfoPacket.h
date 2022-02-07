#pragma once

#include "../Core/Packet.h"
#include "../Core/PackIdVersion.h"
#include "../Core/ContentIdentity.h"

#include "../dll.h"
#include <modutils.h>

struct ResourcePackInfoData {
	PackIdVersion mPackIdVersion; // 0x0
	uint64_t mPackSize; // 0x88
	std::string mContentKey; // 0x90
	std::string mSubpackName; // 0xB0
	ContentIdentity mContentIdentity; // 0xD0
	bool mHasScripts; // 0xE8 - client scripts with the Legacy Scripting API
	// whether client will be forced to download the resource pack or not (this differs from mTexturePackRequired in ResourcePacksInfoData
	// because the clien't can still use their own texture packs alongside the forced one from the server
	bool mForceServerPacks; // 0xE9 - mHasExceptions
};

struct ResourcePacksInfoData {
	bool mTexturePackRequired; // 0x0
	bool mHasScripts; // 0x1
	bool mForceServerPacks; // 0x2 - mHasExceptions
	std::vector<ResourcePackInfoData> mAddOnPacks; // 0x8 - behaviors
	std::vector<ResourcePackInfoData> mTexturePacks; // 0x20 - resources
};

class ResourcePacksInfoPacket : public Packet {
public:
	ResourcePacksInfoData mData; // 0x28

	inline ~ResourcePacksInfoPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(ResourcePacksInfoPacket, mData) == 0x28);
static_assert(offsetof(ResourcePacksInfoData, mForceServerPacks) == 0x2);

static_assert(sizeof(ResourcePackInfoData) == 0xF0);
static_assert(sizeof(ResourcePacksInfoData) == 0x38);
static_assert(sizeof(ResourcePacksInfoPacket) == 0x60);