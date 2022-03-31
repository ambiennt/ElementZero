#pragma once

#include "../dll.h"
#include "../Core/Color.h"

enum class MaterialType {
	Air                  = 0,
	Dirt                 = 1,
	Wood                 = 2,
	Stone                = 3,
	Metal                = 4,
	Water                = 5,
	Lava                 = 6,
	Leaves               = 7,
	Plant                = 8,
	ReplaceablePlant     = 9,
	Sponge               = 10,
	Cloth                = 11,
	Bed                  = 12,
	Fire                 = 13,
	Sand                 = 14,
	Decoration           = 15,
	Glass                = 16,
	Explosive            = 17,
	Ice                  = 18,
	PackedIce            = 19,
	TopSnow              = 20,
	Snow                 = 21,
	Cactus               = 22,
	Clay                 = 23,
	Vegetable            = 24,
	Portal               = 25,
	Cake                 = 26,
	Web                  = 27,
	RedstoneWire         = 28,
	Carpet               = 29,
	BuildableGlass       = 30,
	Slime                = 31,
	Piston               = 32,
	Allow                = 33,
	Deny                 = 34,
	Netherwart           = 35,
	StoneDecoration      = 36,
	Bubble               = 37,
	Egg                  = 38,
	Barrier              = 39,
	DecorationFlammable  = 40,
	SurfaceTypeTotal     = 41,
	Any                  = 42
};
class Material {
public:
	
	MaterialType mType;
	bool mFlammable;
	bool mNeverBuildable;
	bool mAlwaysDestroyable;
	bool mReplaceable;
	bool mLiquid;
	float mTranslucency;
	bool mBlocksMotion;
	bool mBlocksPrecipitation;
	bool mSolid;
	bool mSuperHot;
	Color mMaterialColor;
};

static_assert(sizeof(Material) == 0x24);