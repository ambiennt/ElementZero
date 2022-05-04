#pragma once

#include "../TextObject/TextObjectRoot.h"
#include "BlockActor.h"
#include "../dll.h"

class SignBlockActor : public BlockActor {
public:

	enum class SignType : int32_t {
		Oak                  = 0,
		Spruce               = 1,
		Birch                = 2,
		Jungle               = 3,
		Acacia               = 4,
		DarkOak              = 5,
		RedBigNetherShroom   = 6,
		BlueBigNetherShroom  = 7,
	};

	struct CachedLineData {
		std::string mText; // 0x0
		int32_t mLineLength; // 0x20
	};

	struct CachedMessageData {
		CachedLineData[4] mLineData; // 0x0
		uint32_t mNumLines; // 0xA0
		std::string mFilteredMessage; // 0xA8
		const void* mCachedFontCompare; // 0xC8
		bool mDirty; // 0xD0
	};

	std::string mOwnerID; // 0xD0
	std::string mMessage; // 0xF0
	std::string mTextObjectString; // 0x110
	TextObjectRoot mTextObjectMessage; // 0x130
	CachedMessageData mCachedMessage; // 0x150
	SignType mType; // 0x228

	MCAPI SignBlockActor(class BlockPos const &);
	MCAPI void setMessage(TextObjectRoot text, std::string owner);
	MCAPI void setMessage(std::string text, std::string owner);
};

static_assert(sizeof(SignBlockActor) == 0x230);