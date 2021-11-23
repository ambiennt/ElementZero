#pragma once

inline namespace persona {
  
  enum class AnimatedTextureType {
    none                      = 0,
    face                      = 1,
    animation_frames_32x32    = 2,
    animation_frames_128x128  = 3
  };

  enum class PieceType { //this may be wrong - enums dont line up in 1.14.60 and 1.17.30
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
    Back             = 11,
    FacialHair       = 12,
    Mouth            = 13,
    Eyes             = 14,
    Hair             = 15,
    FaceAccessory    = 16,
    Head             = 17,
    Legs             = 18,
    LeftLeg          = 19,
    RightLeg         = 20,
    Arms             = 21,
    LeftArm          = 22,
    RightArm         = 23,
    Capes            = 24,
    ClassicSkin      = 25
  };

} // namespace persona