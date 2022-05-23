#pragma once

namespace persona {
	
enum class AnimatedTextureType : int32_t {
	None        = 0,
	Face        = 1,
	Body32x32   = 2,
	Body128x128 = 3,
};

enum class PieceType : int32_t {
	Unknown          = 0,
	Skeleton         = 1,
	Body             = 2,
	Skin             = 3,
	Bottom           = 4,
	Feet             = 5,
	Dress            = 6,
	Top              = 7,
	HighPants        = 8,
	Hands            = 9,
	Outerwear        = 10,
	FacialHair       = 11,
	Mouth            = 12,
	Eyes             = 13,
	Hair             = 14,
	Back			 = 15,
	FaceAccessory    = 16,
	Head             = 17,
	Legs             = 18,
	LeftLeg          = 19,
	RightLeg         = 20,
	Arms             = 21,
	LeftArm          = 22,
	RightArm         = 23,
	Capes            = 24,
	ClassicSkin      = 25,
	Emote            = 26,
	Unsupported      = 27,
	Count            = 28,
};

} // namespace persona