#pragma once

#include "persona.h"
#include "../../Core/mce.h"
#include "../../dll.h"

class SerializedPersonaPieceHandle {
public:
	std::string mPieceId;
	persona::PieceType mPieceType;
	mce::UUID mPackId;
	bool mIsDefaultPiece;
	std::string mProductId;
};

static_assert(sizeof(SerializedPersonaPieceHandle) == 0x60);