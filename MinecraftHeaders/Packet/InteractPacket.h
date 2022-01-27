#pragma once

#include "../Core/Packet.h"
#include "../Math/Vec3.h"
#include "../Actor/ActorRuntimeID.h"
#include "../dll.h"

class InteractPacket : public Packet {
public:

	enum class Action : int8_t {
		StopRiding     = 3,
		InteractUpdate = 4, // mouse
		NpcOpen        = 5,
		OpenInventory  = 6
	};

	Action mAction = Action::InteractUpdate; // 0x28
	ActorRuntimeID mTargetId; // 0x30
	Vec3 mPos; // 0x38

	inline ~InteractPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(InteractPacket, mTargetId) == 0x30);
static_assert(offsetof(InteractPacket, mPos) == 0x38);
static_assert(sizeof(InteractPacket) == 0x48);