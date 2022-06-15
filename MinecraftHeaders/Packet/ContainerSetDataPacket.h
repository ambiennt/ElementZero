#pragma once

#include "../Core/Packet.h"
#include "../Core/ContainerID.h"
#include "../dll.h"

class ContainerSetDataPacket : public Packet {
public:
	enum class Property : int32_t {
		FuranceTickCount       = 0,
		FuranceLitTime         = 1,
		FuranceLitDuration     = 2,
		FuranceLitStoredXP     = 3,

		BrewingStandBrewTime   = 0,
		BrewingStandFuelAmount = 1,
		BrewingStandFuelTotal  = 2,
	};

	Property mProperty; // int32_t in BDS
	int32_t mValue;
	ContainerID mContainerId = ContainerID::Invalid;

	ContainerSetDataPacket() {}
	ContainerSetDataPacket(ContainerSetDataPacket::Property property, int32_t value, ContainerID id)
		: mProperty(property), mValue(value), mContainerId(id) {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};