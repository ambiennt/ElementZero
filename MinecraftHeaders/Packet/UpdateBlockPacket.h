#pragma once

#include "../Core/BinaryStream.h"
#include "../Core/Packet.h"
#include "../Math/NetworkBlockPosition.h"
#include "../Math/BlockPos.h"
#include "../dll.h"

class UpdateBlockPacket : public Packet {
public:

	enum class UpdateFlags : uint8_t {
		NONE       = 0x0,
		NEIGHBORS  = 0x1,
		NETWORK    = 0x2,
		NO_GRAPHIC = 0x3,
		PRIORITY   = 0x4
	};

	enum class LayerIds : uint32_t {
		NORMAL = 0,
		LIQUID = 1
	};

	BlockPos mPos; // 0x28
	LayerIds mDataLayerId; // 0x34
	UpdateFlags mUpdateFlags =| UpdateFlags::NETWORK; // 0x38
	uint32_t mRuntimeId; // 0x3C - block runtime ID

	inline ~UpdateBlockPacket() {}

	MCAPI UpdateBlockPacket(void);
	MCAPI UpdateBlockPacket(BlockPos const &pos, uint32_t dataLayerId, class Block const &block, uint8_t flags);

	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(UpdateBlockPacket, mDataLayerId) == 0x34);
static_assert(offsetof(UpdateBlockPacket, mUpdateFlags) == 0x38);
static_assert(offsetof(UpdateBlockPacket, mRuntimeId) == 0x3C);