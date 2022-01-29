#pragma once

#include "../Core/Packet.h"
#include "../Level/GameRules.h"
#include "../dll.h"

struct GameRulesChangedPacketData {
	std::vector<GameRule> mRules;
};

class GameRulesChangedPacket : public Packet {
public:

	GameRulesChangedPacketData mRuleData; // 0x28

	inline ~GameRulesChangedPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(sizeof(GameRulesChangedPacket) == 0x40);