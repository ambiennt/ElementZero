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
	alignas(8) TextPacketType type;
	std::string source, content;
	std::vector<std::string> args;
	bool translated;
	std::string xuid;
	std::string platformId;

	template <TextPacketType type, bool translated = true>
	static inline TextPacket createTextPacket(std::string content) {
		TextPacket pkt;
		pkt.type       = type;
		pkt.translated = translated;
		pkt.content    = content;
		return pkt;
	}
	template <TextPacketType type, bool translated = true>
	static inline TextPacket createTextPacket(std::string source, std::string content) {
		TextPacket pkt;
		pkt.type       = type;
		pkt.translated = translated;
		pkt.source     = source;
		pkt.content    = content;
		return pkt;
	}
	template <TextPacketType type, bool translated = false>
	static inline TextPacket createTextPacket(std::string source, std::string content, std::string xuid) {
		TextPacket pkt;
		pkt.type       = type;
		pkt.translated = translated;
		pkt.source     = source;
		pkt.content    = content;
		pkt.xuid       = xuid;
		return pkt;
	}
	MCAPI static TextPacket createTextObjectMessage(TextObjectRoot const &);

	static inline TextPacket
	createTranslatedMessageWithParams(std::string const &text, std::initializer_list<std::string> args = {}) {
		TextObjectRoot root;
		root.addChild(TextObjectLocalizedTextWithParams::build(text, args));
		return createTextObjectMessage(root);
	}
	inline TextPacket() {}
	inline ~TextPacket() {}
	MCAPI virtual MinecraftPacketIds getId() const;
	MCAPI virtual std::string getName() const;
	MCAPI virtual void write(BinaryStream &) const;
	MCAPI virtual StreamReadResult read(ReadOnlyBinaryStream &);
};

static_assert(offsetof(TextPacket, type) == 0x28);
static_assert(offsetof(TextPacket, source) == 0x30);
static_assert(offsetof(TextPacket, args) == 0x70);
static_assert(offsetof(TextPacket, platformId) == 0xB0);