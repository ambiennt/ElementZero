#pragma once

#include <vector>

#include "../Core/Packet.h"
#include "../Core/HashedString.h"
#include "../Actor/ActorRuntimeID.h"
#include "../dll.h"

class UpdateAttributesPacket : public Packet {
public:
	struct AttributeData {
		float value = 0.0f, min = 0.0f, max = 0.0f, def = 0.0f;
		HashedString name; // 0x10
	};

	ActorRuntimeID rid; // 0x28
	std::vector<AttributeData> data; // 0x30

	inline ~UpdateAttributesPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(UpdateAttributesPacket::AttributeData, name) == 0x10);
static_assert(offsetof(UpdateAttributesPacket, data) == 0x30);