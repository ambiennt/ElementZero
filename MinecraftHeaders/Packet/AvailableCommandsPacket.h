#pragma once

#include "../Core/Packet.h"
#include "../Command/CommandPermissionLevel.h"
#include "../dll.h"

class AvailableCommandsPacket : public Packet {
public:

	struct ParamData {
		std::string mName;
		uint32_t mParseSymbol;
		bool mOptional;
		uint8_t mParamOptions;
	};

	struct EnumData {
		std::string mName;
		std::vector<uint32_t> mValues;
	};

	struct OverloadData {
		std::vector<ParamData> mParams;
	};

	struct CommandData {
		std::string mName;
		std::string mDescription;
		uint8_t mFlags;
		CommandPermissionLevel mPermission;
		std::vector<OverloadData> mOverloads;
		int32_t mAliasEnum;
	};

	struct SoftEnumData {
		std::string mName;
		std::vector<std::string> mValues;
	};

	struct ConstrainedValueData {
		uint32_t mEnumValueSymbol;
		uint32_t mEnumSymbol;
		std::vector<uint8_t> mConstraints;
	};

	std::vector<std::string> mEnumValues; // 0x28
	std::vector<std::string> mPostfixes; // 0x40
	std::vector<EnumData> mEnums; // 0x58
	std::vector<CommandData> mCommands; // 0x70
	std::vector<SoftEnumData> mSoftEnums; // 0x88
	std::vector<ConstrainedValueData> mConstraints; // 0xA0

	inline ~AvailableCommandsPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(sizeof(AvailableCommandsPacket::ParamData) == 0x28);
static_assert(sizeof(AvailableCommandsPacket::EnumData) == 0x38);
static_assert(sizeof(AvailableCommandsPacket::OverloadData) == 0x18);
static_assert(sizeof(AvailableCommandsPacket::CommandData) == 0x68);
static_assert(sizeof(AvailableCommandsPacket::SoftEnumData) == 0x38);
static_assert(sizeof(AvailableCommandsPacket::ConstrainedValueData) == 0x20);
static_assert(sizeof(AvailableCommandsPacket) == 0xB8);