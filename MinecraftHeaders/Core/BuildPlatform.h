#pragma once

enum class BuildPlatform {
	Unknown      = -1,
	Android      = 1,  // google
	iOS          = 2,
	OSX          = 3,
	Amazon       = 4,
	GearVR       = 5,
	Hololens     = 6,  // DEPRECATED
	UWP          = 7,  // windows 10
	Win32        = 8,
	Dedicated    = 9,  // bds
	Tvos         = 10, // DEPRECATED
	PS4          = 11, // orbis
	Nintendo     = 12, // nx
	Xbox         = 13,
	WindowsPhone = 14
};