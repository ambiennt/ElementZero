#pragma once

#include "Persona.h"
#include "../../Core/mce.h"

class SerializedPersonaPieceHandle {
public:
	std::string name;
	PieceType type;
	mce::UUID uuid;
	bool flag;
	std::string data;
};