#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "../FakeGSL/span.h"
#include "../dll.h"

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#pragma comment(lib, "bcrypt.lib")

namespace mce {

class UUID {
public:
	uint64_t mostSig, leastSig;

	UUID() : mostSig(0), leastSig(0) {}
	UUID(uint64_t mostSig, uint64_t leastSig) : mostSig(mostSig), leastSig(leastSig) {}
	UUID(UUID const &rhs) : mostSig(rhs.mostSig), leastSig(rhs.leastSig) {}

	static inline boost::uuids::random_generator UUID_GENERATOR{};

	inline bool operator==(UUID const &rhs) const {
		return ((this->mostSig == rhs.mostSig) && (this->leastSig == rhs.leastSig));
	}
	inline UUID &operator=(UUID const &rhs) {
		this->mostSig = rhs.mostSig;
		this->leastSig = rhs.leastSig;
		return *this;
	}
	inline operator const char*() const { return reinterpret_cast<const char*>(this); }

	inline bool empty() const { return ((this->mostSig == 0) && (this->leastSig == 0)); }
	MCAPI std::string asString() const;
	MCAPI static UUID fromString(std::string const &source);
	MCAPI static UUID EMPTY;

	static UUID generateUUID() {
		return fromString(boost::lexical_cast<std::string>(UUID_GENERATOR()));
	}
	static std::string generateUUIDAsString() {
		return boost::lexical_cast<std::string>(UUID_GENERATOR());
	}
};

class Blob {
public:
	std::unique_ptr<uint8_t[]> buffer;
	size_t length;

	Blob() : length(0) {}
	Blob(Blob &&rhs) : buffer(std::move(rhs.buffer)), length(rhs.length) { rhs.length = 0; }
	Blob(size_t input_length) : buffer(std::make_unique<uint8_t[]>(input_length)), length(input_length) {}
	Blob(uint8_t const *input, size_t input_length) : Blob(input_length) {
		memcpy(this->buffer.get(), input, input_length);
	}

	Blob &operator=(Blob &&rhs) {
		if (&rhs != this) {
			buffer     = std::move(rhs.buffer);
			length     = rhs.length;
			rhs.length = 0;
		}
		return *this;
	}

	inline Blob clone() const { return {this->data(), this->size()}; }
	inline uint8_t *begin() { return this->buffer.get(); }
	inline uint8_t *end() { return this->buffer.get() + this->length; }
	inline uint8_t const *cbegin() const { return this->buffer.get(); }
	inline uint8_t const *cend() const { return this->buffer.get() + this->length; }
	inline uint8_t *data() { return this->buffer.get(); }
	inline uint8_t const *data() const { return this->buffer.get(); }
	inline bool empty() const { return (this->length == 0); }
	inline size_t size() const { return this->length; }
	inline auto getSpan() const { return gsl::make_span(this->data(), this->size()); }
};

enum class ImageFormat {
	NONE    = 0,
	RGB     = 1,
	RGBA    = 2
};

enum class ImageUsage : int8_t {
	unknown = 0,
	sRGB    = 1,
	data    = 2
};

inline uint32_t numChannels(ImageFormat format) {
	switch (format) {
		case ImageFormat::RGB:  return 3;
		case ImageFormat::RGBA: return 4;
		default:                return 0;
	}
}

struct Image {

	ImageFormat format; // 0x0
	uint32_t width, height; // 0x4, 0x8
	ImageUsage usage; // 0xC
	Blob data; // 0x10

	Image() : format(ImageFormat::NONE), width(0), height(0), usage(ImageUsage::unknown) {}
	Image(ImageFormat format, uint32_t width, uint32_t height, ImageUsage usage, Blob &&data)
		: format(format), width(width), height(height), usage(usage), data(std::move(data)) {}
	Image(Blob &&data) : data(std::move(data)) {}
	Image(uint32_t width, uint32_t height, ImageFormat format, ImageUsage usage)
		: format(format), width(width), height(height), usage(usage) {}

	Image &operator=(Image &&rhs) {
		this->format = rhs.format;
		this->width  = rhs.width;
		this->height = rhs.height;
		this->usage  = rhs.usage;
		this->data   = std::move(rhs.data);
		return *this;
	}

	inline Image clone() const { return {this->format, this->width, this->height, this->usage, this->data.clone()}; }
	inline void copyRawImage(Blob const &blob) { this->data = blob.clone(); }
	inline bool isEmpty() const { return this->data.empty(); }
	inline void resizeImageBytesToFitImageDescription() { this->data = Blob{this->width * this->height * numChannels(this->format)}; }
	inline void setImageDescription(uint32_t width, uint32_t height, ImageFormat format, ImageUsage usage) {
		this->width  = width;
		this->height = height;
		this->format = format;
		this->usage  = usage;
	}
	inline void setRawImage(Blob &&buffer) { this->data = std::move(buffer); }
};

static_assert(offsetof(Image, data) == 0x10);
static_assert(offsetof(Image, format) == 0x0);
static_assert(offsetof(Image, usage) == 0xC);
static_assert(sizeof(Image) == 0x20);

} // namespace mce