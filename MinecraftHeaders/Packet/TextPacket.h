#pragma once

#include <string>
#include <vector>

#include <hook.h>

#include "../Core/Packet.h"
#include "../TextObject/TextObjectRoot.h"
#include "../TextObject/TextObjectLocalizedTextWithParams.h"
#include "../dll.h"

enum class TextPacketType : int8_t {
	Raw               = 0,
	Chat              = 1,
	Translate         = 2,
	Popup             = 3,
	JukeboxPopup      = 4,
	Tip               = 5,
	SystemMessage     = 6,
	Whisper           = 7,
	Announcement      = 8,
	TextObjectWhisper = 9,
	TextObject        = 10
};

class TextPacket : public Packet {
public:
	TextPacketType mType;
	std::string mAuthor;
	std::string mMessage;
	std::vector<std::string> mParams;
	bool mLocalize; // translate the text message to the client's language
	std::string mXuid;
	std::string mPlatformId;

	template <TextPacketType type, bool translated = true>
	static inline TextPacket createTextPacket(std::string const &msg) {
		TextPacket pkt;
		pkt.mType      = type;
		pkt.mMessage   = msg;
		pkt.mLocalize = translated;
		return pkt;
	}
	template <TextPacketType type, bool translated = true>
	static inline TextPacket createTextPacket(std::string const &author, std::string const &msg) {
		TextPacket pkt;
		pkt.mType      = type;
		pkt.mAuthor    = author;
		pkt.mMessage   = msg;
		pkt.mLocalize = translated;
		return pkt;
	}
	template <TextPacketType type, bool translated = false>
	static inline TextPacket createTextPacket(std::string const &author, std::string const &msg, std::string const &xuid) {
		TextPacket pkt;
		pkt.mType      = type;
		pkt.mAuthor    = author;
		pkt.mMessage   = msg;
		pkt.mLocalize = translated;
		pkt.mXuid      = xuid;
		return pkt;
	}
	MCAPI static TextPacket createTextObjectMessage(TextObjectRoot const &);
	static inline TextPacket createTranslatedMessageWithParams(std::string const &msg, std::initializer_list<std::string> args = {}) {
		TextObjectRoot root;
		root.addChild(TextObjectLocalizedTextWithParams::build(msg, args));
		return createTextObjectMessage(root);
	}
	inline TextPacket() {}
	inline ~TextPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(TextPacket, mType) == 0x28);
static_assert(offsetof(TextPacket, mAuthor) == 0x30);
static_assert(offsetof(TextPacket, mMessage) == 0x50);
static_assert(offsetof(TextPacket, mParams) == 0x70);
static_assert(offsetof(TextPacket, mPlatformId) == 0xB0);