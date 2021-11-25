#pragma once

#include "../Core/Packet.h"
#include "../Level/LevelSettings.h"
#include "../Actor/ActorRuntimeID.h"
#include "../dll.h"

class StartGamePacket : public Packet {
public:
	LevelSettings settings;
	//TODO add rest of the fields

	inline ~StartGamePacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};