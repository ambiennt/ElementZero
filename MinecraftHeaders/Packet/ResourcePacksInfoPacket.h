#pragma once

#include "../Core/Packet.h"
#include "../Core/PackIdVersion.h"
#include "../dll.h"

#include <modutils.h>

struct ResourcePackInfoData {
	BUILD_ACCESS_MUT(struct PackIdVersion, mPackIdVersion, 0x0);
	BUILD_ACCESS_MUT(uint64_t, mPackSize, 0x88);
	BUILD_ACCESS_MUT(std::string, mContentKey, 0x90);
	BUILD_ACCESS_MUT(std::string, mSubpackName, 0xB0);
	BUILD_ACCESS_MUT(class ContentIdentity, mContentIdentity, 0xD0);
	BUILD_ACCESS_MUT(bool, mHasScripts, 0xE8); // client scripts
	// whether client will be forced to download the resource pack or not (this differs from mTexturePackRequired in ResourcePacksInfoData
	// because the clien't can still use their own texture packs alongside the forced one from the server
	BUILD_ACCESS_MUT(bool, mForceServerPacks, 0xE9); // mHasExceptions
};

struct ResourcePacksInfoData {
	BUILD_ACCESS_MUT(bool, mTexturePackRequired, 0x0);
	BUILD_ACCESS_MUT(bool, mHasScripts, 0x1);
	BUILD_ACCESS_MUT(bool, mForceServerPacks, 0x2); // mHasExceptions
	BUILD_ACCESS_MUT(std::vector<struct ResourcePackInfoData>, mAddOnPacks, 0x8); // behaviors
	BUILD_ACCESS_MUT(std::vector<struct ResourcePackInfoData>, mTexturePacks, 0x20); // resources
};

class ResourcePacksInfoPacket : public Packet {
public:
	ResourcePacksInfoData mData;

	inline ~ResourcePacksInfoPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(ResourcePacksInfoPacket, mData) == 0x28);