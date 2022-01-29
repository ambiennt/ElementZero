#pragma once

#include "../Core/Packet.h"
#include "../dll.h"

enum class PlayStatus {
	LoginSuccess = 0x0,
	LoginFailed_ClientOld = 0x1,
	LoginFailed_ServerOld = 0x2,
	PlayerSpawn = 0x3,
	LoginFailed_InvalidTenant = 0x4,
	LoginFailed_EditionMismatchEduToVanilla = 0x5,
	LoginFailed_EditionMismatchVanillaToEdu = 0x6,
	LoginFailed_ServerFullSubClient = 0x7
};

class PlayStatusPacket : public Packet {
public:

	PlayStatus mPlayStatus; // 0x28

	inline ~PlayStatusPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(mPlayStatus) == 0x28);