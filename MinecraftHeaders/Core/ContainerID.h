#pragma once

enum class ContainerID : char {
	Invalid = -1,
	Inventory = 0, 
	First = 1,
	Last = 100,
	Offhand = 119,
	Armor = 120,
	SelectionSlots = 122,
	PlayerUIOnly = 124
};