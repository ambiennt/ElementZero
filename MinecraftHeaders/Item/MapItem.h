#pragma once

#include "TextureAtlasItem.h"
#include "ComplexItem.h"
#include "../dll.h"
#include <string>
#include <vector>
#include <memory>

class Level;
class Dimension;
class Actor;
class MapItemSavedData;
class Packet;
class MapItemTrackedActor;
class ItemStack;
class CompoundTag;
class ItemInstance;
class BlockSource;
struct MapSample;
struct ActorUniqueID;

class EmptyMapItem : public ComplexItem {
public:
    MCAPI static void addPlayerMarker(ItemInstance &map); // just adds the TAG_MAP_PLAYER_DISPLAY compound tag to the itemstack
};

class MapItem : public ComplexItem {
    MCAPI void _makeNewExplorationMap(ItemStack &, Level &, Actor *, std::string &) const;
public:
    TextureAtlasItem mUVTextureItem; // 0x1B8

    MCAPI static std::string const TAG_MAP_INIT;
    MCAPI static std::string const TAG_MAP_NAME_INDEX;
    MCAPI static std::string const TAG_MAP_PLAYER_DISPLAY;
    MCAPI static std::string const TAG_MAP_SCALE;
    MCAPI static std::string const TAG_MAP_SCALING;
    MCAPI static std::string const TAG_MAP_UUID;

    virtual std::unique_ptr<Packet> getUpdatePacket(const ItemStack &, Level &, Actor &) const;
    MCAPI void update(Level &, Actor &, MapItemSavedData &) const;
    MCAPI static void serializeMapData(const std::vector<MapSample> &, std::string &);
    MCAPI static ActorUniqueID getMapId(CompoundTag const *);
    MCAPI static void setItemInstanceInfo(ItemInstance &, MapItemSavedData &);
    MCAPI static void renderBiomePreviewMap(Dimension &, MapItemSavedData &);

    // 128 x 128 for maps, 16 x 16 for /getchunkdata
    MCAPI static void sampleMapData(BlockSource &region, int32_t blocksPerTexel, const BlockPos &worldOrigin, const BlockPos &updateOrigin,
        int32_t imageWidth, int32_t imageHeight, std::vector<MapSample> *optionalOutput, MapItemSavedData *mapData, MapItemTrackedActor *unk = nullptr);
};

static_assert(offsetof(MapItem, mUVTextureItem) == 0x1B8);