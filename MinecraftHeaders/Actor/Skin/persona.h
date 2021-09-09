#pragma once

inline namespace persona {
  
enum class AnimatedTextureType {
  none = 0,
  face = 1,
  animation_frames_32x32 = 2,
  animation_frames_128x128 = 3
};

enum class PieceType {
  Unknown          = 0,
  Skeleton_0       = 1,
  Body_0           = 2,
  Skin             = 3,
  Bottom           = 4,
  Feet_1           = 5,
  Dress            = 6,
  Top              = 7,
  High_Pants       = 8,
  Hands_0          = 9,
  Outerwear        = 10,
  Back             = 11,
  FacialHair       = 12,
  Mouth_0          = 13,
  Eyes_0           = 14,
  Hair             = 15,
  FaceAccessory    = 16,
  Head_1           = 17,
  Legs_0           = 18,
  LeftLeg          = 19,
  RightLeg         = 20,
  Arms             = 21,
  LeftArm          = 22,
  RightArm         = 23,
  Capes            = 24,
  ClassicSkin      = 25
};

} // namespace persona