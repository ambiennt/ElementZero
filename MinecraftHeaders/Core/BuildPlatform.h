#pragma once

enum class BuildPlatform {
    Unknown      = -1,
    Android      = 1, // google
    iOS          = 2,
    OSX          = 3,
    Amazon       = 4,
    GearVR       = 5,
    UWP          = 7,
    Win32        = 8,
    Dedicated    = 9,  // bds
    PS4          = 10, // orbis
    Nintendo     = 11, // nx
    Xbox         = 12,
    WindowsPhone = 13
};