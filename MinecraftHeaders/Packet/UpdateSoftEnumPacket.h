#pragma once

#include "../Core/Packet.h"
#include "../dll.h"

enum class SoftEnumUpdateType : int8_t {
	Add = 0x0,
	Remove = 0x1,
	Replace = 0x2,
};

class UpdateSoftEnumPacket : public Packet {
public:
	std::string mEnumName; // 0x28
	std::vector<std::string> mValues; // 0x48
	SoftEnumUpdateType mType; // 0x60

	UpdateSoftEnumPacket(std::string const &name, std::vector<std::string> const &vals, SoftEnumUpdateType type)
		: mEnumName(name), mValues(vals), mType(type) {}
	inline ~UpdateSoftEnumPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(sizeof(UpdateSoftEnumPacket) == 0x68);