#pragma once

#include "../Core/Packet.h"
#include "../Actor/ActorUniqueID.h"
#include "../dll.h"

// useless packet, used for client telemetry
class EventPacket : public Packet {
public:
	
	enum class Type {
		Achievement = 0x0,
		Interaction = 0x1,
		PortalCreated = 0x2,
		PortalUsed = 0x3,
		MobKilled = 0x4,
		CauldronUsed = 0x5,
		PlayerDied = 0x6,
		BossKilled = 0x7,
		AgentCommand = 0x8,
		AgentCreated = 0x9,
		PatternRemoved = 0xA,
		SlashCommand = 0xB,
		FishBucketed = 0xC,
		MobBorn = 0xD,
		PetDied = 0xE,
		POICauldronUsed = 0xF,
		ComposterUsed = 0x10,
		BellUsed = 0x11,
		ActorDefinition = 0x12,
		RaidUpdate = 0x13,
		PlayerMovementAnomaly = 0x14,
		PlayerMovementCorrected = 0x15,
		HoneyHarvested = 0x16,
		TargetBlockHit = 0x17,
		PiglinBarter = 0x18,
	};

	enum class AgentResult {
		ActionFail = 0x0,
		ActionSuccess = 0x1,
		QueryResultFalse = 0x2,
		QueryResultTrue = 0x3,
	};

	struct Data {
		Type mType; // 0x0
		uint8_t mUsePlayerID; // 0x4
		char unknownUnion[0x24];
		std::string mEntityName; // 0x28
		std::string mCommandName; // 0x48
		std::string mResultKey; // 0x68
		std::string mResultString; // 0x88
		std::string mErrorList; // 0xA8
	};

	ActorUniqueID mPlayerId; // 0x28
	Data mEventData; // 0x30

	inline ~EventPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(sizeof(EventPacket::Data) == 0xC8);
static_assert(sizeof(EventPacket) == 0xF8);