#pragma once

#include "../dll.h"

#include <string>
#include <cstdint>
#include <vector>

struct TextureUVCoordinateSet { // const struct
    float weight;
    float _u0, _v0, _u1, _v1;
    uint16_t _texSizeW, _texSizeH;
    //ResourceLocation sourceFileLocation;
    //IsotropicFaceData mIsotropicFaceData;
    uint8_t pad[0x40];
};

static_assert(sizeof(TextureUVCoordinateSet) == 0x58);

class TextureAtlasItem { // const class
public:
	std::string mName; // 0x0
	int32_t mParsedNodeIndex; // 0x20
	std::vector<std::vector<TextureUVCoordinateSet>> mTextureUVs; // 0x28
};

static_assert(sizeof(TextureAtlasItem) == 0x40);