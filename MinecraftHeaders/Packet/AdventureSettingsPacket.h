#pragma once

#include "../Core/Packet.h"
#include "../Command/CommandPermissionLevel.h"
#include "../Level/PlayerPermissionLevel.h"
#include "../Actor/ActorUniqueID.h"
#include "../dll.h"

struct AdventureSettings;
class Abilities;

class AdventureSettingsPacket : public Packet {
public:

	enum class Flags : uint32_t {
		WorldImmutable = 0x1,
		NoPvM = 0x2,
		NoMvP = 0x4,
		Unused = 0x8,
		ShowNameTags = 0x10,
		AutoJump = 0x20,
		PlayerMayFly = 0x40,
		PlayerNoClip = 0x80,
		PlayerWorldBuilder = 0x100,
		PlayerFlying = 0x200,
		PlayerMuted = 0x400
	};

	enum class PermissionsFlags : uint32_t {
		Mine = 0x1,
		DoorsAndSwitches = 0x2,
		OpenContainers = 0x4,
		AttackPlayers = 0x8,
		AttackMobs = 0x10,
		OP = 0x20,
		Teleport = 0x80,
		Build = 0x100,
		DefaultLevelPermissions = 0x200
	};

	uint32_t mFlags; // bit flag
	CommandPermissionLevel mUserPermissions;
	uint32_t mPermissionsFlags; // bit flag
	PlayerPermissionLevel mPlayerPermissions;
	ActorUniqueID mSyncPlayerId;
	bool mDefaultLevelAbilities;
	uint32_t mCustomAbilityCache; // idk what this is

	MCAPI AdventureSettingsPacket(
		AdventureSettings const& settings, Abilities const& abilities, ActorUniqueID playerIdToSync, bool defaultLevelSettings);
	inline ~AdventureSettingsPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(AdventureSettingsPacket, mFlags) == 0x28);
static_assert(offsetof(AdventureSettingsPacket, mUserPermissions) == 0x2C);
static_assert(offsetof(AdventureSettingsPacket, mPermissionsFlags) == 0x30);
static_assert(offsetof(AdventureSettingsPacket, mPlayerPermissions) == 0x34);
static_assert(offsetof(AdventureSettingsPacket, mSyncPlayerId) == 0x38);
static_assert(offsetof(AdventureSettingsPacket, mDefaultLevelAbilities) == 0x40);
static_assert(offsetof(AdventureSettingsPacket, mCustomAbilityCache) == 0x44);