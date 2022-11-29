#pragma once

#include "../dll.h"
#include <cstdint>

enum class SubChunkFormat : int8_t {
	v17_0                  = 0x0,
	v1_3_0                 = 0x1,
	v17_0_badly_converted1 = 0x2,
	v17_0_badly_converted2 = 0x3,
	v17_0_badly_converted3 = 0x4,
	v17_0_badly_converted4 = 0x5,
	v17_0_badly_converted5 = 0x6,
	v17_0_badly_converted6 = 0x7,
	v1_3_0_2               = 0x8,
};

enum class StorageVersion {
	Unknown_0 = 0x0,
	OldV1 = 0x1,
	OldV2 = 0x2,
	OldV3 = 0x3,
	LevelDB1 = 0x4,
	LevelDBSubChunks = 0x5,
	LevelDBSubChunkRawZip = 0x6,
	LevelDBPaletted1 = 0x7,
	LevelDBPalettedMultiBlockStorage = 0x8,
};

namespace SharedConstants {

//extern const int32_t StoreVersion = 1;
//extern const int32_t EduDiscoveryProtocolVersion = 0;
//extern const int32_t MaxChatLength = 100;
//extern const int32_t LevelDBCompressorID = 16;

MCAPI extern const uint32_t MajorVersion; // 1
MCAPI extern const uint32_t MinorVersion; // 16
MCAPI extern const uint32_t PatchVersion; // 20
MCAPI extern const uint32_t RevisionVersion; // 3
MCAPI extern const bool isBeta; // false
MCAPI extern const uint32_t CurrentLevelChunkFormat; // 19
MCAPI extern const enum SubChunkFormat CurrentSubChunkFormat; // SubChunkFormat::v1_3_0_2
MCAPI extern const int32_t NetworkProtocolVersion; // 408
MCAPI extern const int32_t AutomationProtocolVersion; // 1
MCAPI extern const int32_t CompanionAppProtocolVersion; // 4
MCAPI extern const enum StorageVersion CurrentStorageVersion; // StorageVersion::LevelDBPalettedMultiBlockStorage;
MCAPI extern const uint16_t NetworkDefaultGamePort; // 19132
MCAPI extern const uint16_t NetworkDefaultGamePortv6; // 19133
MCAPI extern const uint16_t NetworkEphemeralPort; // 0
MCAPI extern const int32_t NetworkDefaultMaxConnections; // 30
MCAPI extern const class GameVersion MinimumCompatibleGameVersionForLevelData;

} // namespace SharedConstants