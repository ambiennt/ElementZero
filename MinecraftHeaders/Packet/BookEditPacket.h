#pragma once

#include <string>

#include "../Core/Packet.h"
#include "../dll.h"

class BookEditPacket : public Packet {
public:
	enum class Action : int8_t {
		REPLACE_PAGE  = 0,
		ADD_PAGE      = 1,
		DELETE_PAGE   = 2,
		SWAP_PAGES    = 3,
		SIGN_BOOK     = 4
	};
	
	Action mAction;
	int mBookSlot, mPageIndex1, mPageIndex2;
	std::string mText1, mText2, mText3;

	inline ~BookEditPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(BookEditPacket, mAction) == 40);
static_assert(offsetof(BookEditPacket, mBookSlot) == 44);
static_assert(offsetof(BookEditPacket, mText1) == 56);
static_assert(offsetof(BookEditPacket, mText2) == 88);
static_assert(offsetof(BookEditPacket, mText3) == 120);