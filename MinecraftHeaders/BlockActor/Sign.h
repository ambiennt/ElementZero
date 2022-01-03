#pragma once

#include "../TextObject/TextObjectRoot.h"
#include "BlockActor.h"
#include "../dll.h"

#include <modutils.h>

class SignBlockActor : public BlockActor {
public:
	char pad[352];
	
	enum class SignType {
		Oak                  = 0,
		Spruce               = 1,
		Birch                = 2,
		Jungle               = 3,
		Acacia               = 4,
		DarkOak              = 5,
		RedBigNetherShroom   = 6,
		BlueBigNetherShroom  = 7
	};

	struct CachedLineData {
		BUILD_ACCESS_MUT(std::string, mText, 0x0);
		BUILD_ACCESS_MUT(int32_t, mLineLength, 0x20);
	};

	struct CachedMessageData {

		using lineDataArr4 = struct SignBlockActor::CachedLineData[4];
		BUILD_ACCESS_MUT(lineDataArr4, mLineData, 0x0);

		BUILD_ACCESS_MUT(uint32_t, mNumLines, 0xA0);
		BUILD_ACCESS_MUT(std::string, mFilteredMessage, 0xA8);
		BUILD_ACCESS_MUT(const void*, mCachedFontCompare, 0xC8); // no clue what this is
		BUILD_ACCESS_MUT(bool, mDirty, 0xD0);
	};

	BUILD_ACCESS_MUT(std::string, mOwnerID, 0xD0);
	BUILD_ACCESS_MUT(std::string, mMessage, 0xF0);
	BUILD_ACCESS_MUT(std::string, mTextObjectString, 0x110);
	BUILD_ACCESS_MUT(class TextObjectRoot, mTextObjectMessage, 0x130);
	BUILD_ACCESS_MUT(struct SignBlockActor::CachedMessageData, mCachedMessage, 0x150);
	BUILD_ACCESS_MUT(enum SignBlockActor::SignType, mType, 0x228);

	MCAPI SignBlockActor(class BlockPos const &);
	MCAPI virtual void load(class Level &, class CompoundTag const &, class DataLoadHelper &) override;
	MCAPI virtual bool save(class CompoundTag &) const override;
	MCAPI virtual void onChanged(class BlockSource &) override;
	MCAPI virtual float getShadowRadius(class BlockSource &) const override;
	MCAPI virtual std::string getImmersiveReaderText(class BlockSource &) override;

	MCAPI void setMessage(TextObjectRoot text, std::string owner);
	MCAPI void setMessage(std::string text, std::string owner);

protected:
	MCAPI virtual void _onUpdatePacket(class CompoundTag const &, class BlockSource &) override;
};

static_assert(sizeof(SignBlockActor) == 560);