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

	Action action = Action::InteractUpdate;
	ActorRuntimeID mTargetId;
	Vec3 mPos;

	inline ~InteractPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(sizeof(CraftingEventPacket) == 0x48);