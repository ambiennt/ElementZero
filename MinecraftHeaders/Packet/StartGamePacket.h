#pragma once

#include "../Core/Packet.h"
#include "../Level/LevelSettings.h"
#include "../Actor/ActorRuntimeID.h"
#include "../Actor/ActorUniqueID.h"
#include "../Item/ItemData.h"
#include "../Math/Vec3.h"
#include "../Math/Vec2.h"
#include "../Core/ContentIdentity.h"

#include "../dll.h"

class BlockPalette;
class Tag;

class StartGamePacket : public Packet {
public:
	LevelSettings mLevelSettings; // 0x28
	ActorUniqueID mEntityId; // 0x3C0
	ActorRuntimeID mRuntimeId; // 0x3C8
	GameType mEntityGameType; // 0x3D0
	Vec3 mPos; // 0x3D4
	Vec2 mRot; // 0x3E0
	std::string mLevelId, mLevelName; // 0x3E8, 0x408
	ContentIdentity mTemplateContentIdentity; // 0x428
	bool mIsTrial, mIsServerAuthoritativeMovement; // 0x440, 0x441
	uint64_t mLevelCurrentTime; // 0x448
	int32_t mEnchantmentSeed; // 0x450
	std::string mMultiplayerCorrelationId; // 0x458
	const BlockPalette *mBlockPalette; // 0x478
	std::unique_ptr<Tag> mBlockPaletteList; // 0x480
	std::vector<ItemData> mItemData; // 0x488
	bool mEnableItemStackNetManager; // 0x4A0

	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};
static_assert(sizeof(StartGamePacket) == 0x4A8);