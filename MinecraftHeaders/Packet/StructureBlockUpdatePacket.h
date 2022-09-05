#pragma once

#include "../Core/Packet.h"
#include "../Actor/ActorUniqueID.h"
#include "../Math/BlockPos.h"
#include "../Math/Vec3.h"
#include "../dll.h"
#include <string>

enum class StructureRedstoneSaveMode : int8_t {
    SavesToMemory = 0x0,
    SavesToDisk = 0x1,
};

enum class StructureBlockType : int32_t {
    Data = 0x0,
    Save = 0x1,
    Load = 0x2,
    Corner = 0x3,
    Invalid = 0x4,
    Export = 0x5,
    Count = 0x6,
};

struct StructureSettings {
    std::string mPaletteName; // 0x0
    bool mIgnoreEntities, mReloadActorEquipment, mIgnoreBlocks, mIgnoreJigsawBlocks; // 0x20, 0x21, 0x22, 0x23
    BlockPos mStructureSize, mStructureOffset; // 0x24, 0x30
    Vec3 mPivot; // 0x3C
    ActorUniqueID mLastTouchedByPlayer; // 0x48
    int8_t mRotation, mMirror; // 0x50, 0x51 - idk what this is
    float mIntegrityValue; // 0x54
    uint32_t mIntegritySeed; // 0x58
};

struct StructureEditorData {
    std::string mStructureName, mDataField; // 0x0, 0x20
    bool mIncludePlayers, mShowBoundingBox; // 0x40, 0x41
    StructureRedstoneSaveMode mRedstoneSaveMode; // 0x42
    StructureBlockType mType; // 0x44
    StructureSettings mSettings; // 0x48
};

class StructureBlockUpdatePacket : public Packet {
public:
    BlockPos mBlockPos; // 0x28
    StructureEditorData mData; // 0x38
    bool mTrigger; // 0xE0

	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(sizeof(StructureSettings) == 0x60);
static_assert(sizeof(StructureEditorData) == 0xA8);
static_assert(sizeof(StructureBlockUpdatePacket) == 0xE8);