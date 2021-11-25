#pragma once

#include "ActorUniqueID.h"

struct ActorLink {
	ActorUniqueID from, to;
};

enum class ActorLinkType {
	None       = 0,
	Riding     = 1,
	Passenger  = 2
};