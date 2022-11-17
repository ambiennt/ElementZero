#pragma once

#include "../Level/DimensionID.h"
#include "../Actor/ActorUniqueID.h"
#include "../Math/Vec3.h"
#include "../Math/BlockPos.h"
#include "../Core/Color.h"
#include "../Core/AutomaticID.h"
#include "../dll.h"
#include <cstdint>
#include <memory>
#include <vector>
#include <utility>
#include <string>

class ChunkViewSource;

class MapDecoration { // probably for item frames
public:

    enum class Type : int8_t {
        MarkerWhite = 0x0,
        MarkerGreen = 0x1,
        MarkerRed = 0x2,
        MarkerBlue = 0x3,
        XWhite = 0x4,
        TriangleRed = 0x5,
        SquareWhite = 0x6,
        MarkerSign = 0x7,
        MarkerPink = 0x8,
        MarkerOrange = 0x9,
        MarkerYellow = 0xA,
        MarkerTeal = 0xB,
        TriangleGreen = 0xC,
        SmallSquareWhite = 0xD,
        Mansion = 0xE,
        Monument = 0xF,
        NoDraw = 0x10,
        Count = 0x11,
        Player = 0x0,
        PlayerOffMap = 0x6,
        PlayerOffLimits = 0xD,
        PlayerHidden = 0x10,
        ItemFrame = 0x1,
    };

    std::string mLabel; // 0x0
    int8_t mImage; // 0x20
    int8_t mX, mY; // 0x21, 0x22
    int8_t mRotation; // 0x23
    Color mColor; // 0x24
};

static_assert(sizeof(MapDecoration) == 0x38);

class MapItemTrackedActor {
public:

    enum class Type : int32_t {
        Entity = 0,
        BlockEntity = 1,
        Other = 2,
    };

    class UniqueId {
    public:
        MapItemTrackedActor::Type mType; // 0x0
        ActorUniqueID mKeyEntityId; // 0x8
        BlockPos mKeyBlockPos; // 0x10
    };

    MapItemTrackedActor::UniqueId mUniqueId; // 0x0
    int32_t mStep; // 0x20
    bool mNeedsResend; // 0x24
    uint32_t mMinDirtyX, mMinDirtyY, mMaxDirtyX, mMaxDirtyY; // 0x28, 0x2C, 0x30, 0x34
    int32_t mTick; // 0x38
    float mLastRotation; // 0x3C
    MapDecoration::Type mDecorationType; // 0x40
    DimensionID mDimensionId; // 0x44 - AutomaticID<Dimension,int>
    std::unique_ptr<ChunkViewSource> mChunkViewSource; // 0x48
};

static_assert(sizeof(MapItemTrackedActor::UniqueId) == 0x20);
static_assert(sizeof(MapItemTrackedActor) == 0x50);

namespace MapConstants {
    MCAPI extern const Vec3 VERT_MAP_LEFTHAND_POS;
    MCAPI extern const Vec3 VERT_MAP_RIGHTHAND_POS;
    MCAPI extern const Vec3 VERT_MINI_MAP_OFFHAND_POS;
    MCAPI extern const Vec3 VERT_SPLIT_SCREEN_OFFSET;
    MCAPI extern const Vec3 VERT_MAINHAND_MAP_POS;
    MCAPI extern const Vec3 VERT_OFFHAND_MAP_POS;
    MCAPI extern const Vec3 MINI_MAP_RIGHTHAND_ROT;
    MCAPI extern const Vec3 MINI_MAP_LEFTHAND_ROT;
    MCAPI extern const Vec3 MINI_MAP_LEFTHAND_POS;
    MCAPI extern const Vec3 MINI_MAP_RIGHTHAND_POS;
    MCAPI extern const Vec3 MINI_MAP_SWING_POS_SCALE;
    MCAPI extern const Vec3 MINI_MAP_NORMAL;
    MCAPI extern const Vec3 MINI_MAP_OFFHAND_POS;
    MCAPI extern const Vec3 MINI_MAP_MAINHAND_POS;
    MCAPI extern const Vec3 MINI_MAP_HANDS_POS;
    MCAPI extern const Vec3 MINI_MAP_HANDS_ROT;
    MCAPI extern const Vec3 MAP_SWING_ROT;
    MCAPI extern const Vec3 MAP_GLOBAL_ROT;
    MCAPI extern const Vec3 MAP_LEFTHAND_POS;
    MCAPI extern const Vec3 MAP_RIGHTHAND_ROT;
    MCAPI extern const Vec3 MAP_RIGHTHAND_POS;
    MCAPI extern const Vec3 MAP_GLOBAL_POS;
    MCAPI extern const Vec3 MAP_HANDS_ROT;
    MCAPI extern const Vec3 MAP_NORMAL;
    MCAPI extern const Vec3 MAP_SWING_POS_SCALE;
    MCAPI extern const Vec3 MAP_HANDS_POS;
    MCAPI extern const Vec3 MAP_LEFTHAND_ROT;
    MCAPI extern const int32_t DEFAULT_SCALE;
    MCAPI extern const int32_t DEFAULT_SCALE_STARTING_MAP;
    MCAPI extern const int32_t SPLIT_SCREEN_ADJUST;
    MCAPI extern const int32_t HALF_MAP_SIZE;
    MCAPI extern const int32_t MAX_SCALE;
    MCAPI extern const int32_t MAP_SIZE;
    MCAPI extern const int32_t DEFAULT_SCALE_LEGACY_STARTING_MAP;
}

class MapItemSavedData {
public:
    uint64_t mUpdateInterval; // 0x0
    ActorUniqueID mMapId, mParentMapId; // 0x8, 0x10
    bool mIsFullyExplored, mPreviewIncomplete; // 0x18,  0x19
    BlockPos mOrigin; // 0x1C
    DimensionID mDimensionId; // 0x28 - AutomaticID<Dimension,int>
    int8_t mScale; // 0x2C
    std::vector<uint32_t> mPixels; // 0x30
    std::vector<std::shared_ptr<MapItemTrackedActor>> mTrackedEntities; // 0x48
    bool mUnlimitedTracking, mDirtyForSave, mDirtyPixelData, mLocked; // 0x60, 0x61, 0x62, 0x63
    std::vector<std::pair<MapItemTrackedActor::UniqueId, std::shared_ptr<MapDecoration>>> mDecorations; // 0x68

    MCAPI void setOrigin(Vec3 origin, int32_t mapScale, AutomaticID<Dimension, int32_t> dimension, bool isLegacyLevel, bool isCentered, const BlockPos &worldCenter);

    inline void enableUnlimitedTracking() {
        if (!this->mUnlimitedTracking) {
            this->mUnlimitedTracking = true;
            this->mDirtyForSave = true;
        }
    }
};

static_assert(offsetof(MapItemSavedData, mPreviewIncomplete) == 0x19);
static_assert(offsetof(MapItemSavedData, mUnlimitedTracking) == 0x60);
static_assert(sizeof(MapItemSavedData) == 0x80);