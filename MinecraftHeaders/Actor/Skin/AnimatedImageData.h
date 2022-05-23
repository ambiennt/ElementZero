#pragma once

#include "persona.h"
#include "../../Core/mce.h"
#include "../../dll.h"

class AnimatedImageData {
public:
	persona::AnimatedTextureType mType;
	mce::Image mImage;
	float mFrames;

	inline AnimatedImageData(persona::AnimatedTextureType type, mce::Image const &image, float frames)
            : mType(type), mImage(image.clone()), mFrames(frames) {}

	inline AnimatedImageData &operator=(AnimatedImageData const &rhs) {
		this->mType = rhs.mType;
		this->mImage = rhs.mImage.clone();
		this->mFrames = rhs.mFrames;
		return *this;
	}
};

static_assert(offsetof(AnimatedImageData, mFrames) == 40);