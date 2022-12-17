#pragma once

#include "../Core/Packet.h"
#include "../Math/BlockPos.h"
#include "../Actor/ActorRuntimeID.h"
#include "../dll.h"

enum class PlayerActionType : int32_t {
	START_BREAK              = 0,
	ABORT_BREAK              = 1,
	STOP_BREAK               = 2,
	GET_UPDATED_BLOCK        = 3,
	DROP_ITEM                = 4,
	START_SLEEPING           = 5,
	STOP_SLEEPING            = 6,
	RESPAWN                  = 7,
	JUMP                     = 8,
	START_SPRINT             = 9,
	STOP_SPRINT              = 10,
	START_SNEAK              = 11,
	STOP_SNEAK               = 12,
	DIMENSION_CHANGE_REQUEST = 13, // sent when dying in a different dimension
	DIMENSION_CHANGE_ACK     = 14, // sent when spawning in a different dimension to tell the server we spawned
	START_GLIDE              = 15,
	STOP_GLIDE               = 16,
	BUILD_DENIED             = 17,
	CONTINUE_BREAK           = 18,
	CHANGE_SKIN              = 19,
	SET_ENCHANTMENT_SEED     = 20, // sent by client if ItemStackNetManager is disabled
	START_SWIMMING           = 21,
	STOP_SWIMMING            = 22,
	START_SPIN_ATTACK        = 23,
	STOP_SPIN_ATTACK         = 24,
	INTERACT_BLOCK           = 25,
};

class PlayerActionPacket : public Packet {
public:
	BlockPos mPos;
	int32_t mFace; // block face
	PlayerActionType mAction;
	ActorRuntimeID mRuntimeId;

	inline ~PlayerActionPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(PlayerActionPacket, mFace) == 52);
static_assert(offsetof(PlayerActionPacket, mRuntimeId) == 64);