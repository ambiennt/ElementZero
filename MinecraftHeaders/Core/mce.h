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
	uint64_t a = 0, b = 0;

	UUID() {}
	UUID(uint64_t a, uint64_t b) : a(a), b(b) {}
	UUID(UUID const &rhs) : a(rhs.a), b(rhs.b) {}

	inline bool operator==(UUID const &rhs) const noexcept { return ((this->a == rhs.a) && (this->b == rhs.b)); }
	inline operator char const *() const { return (char const *)this; }
	UUID &operator=(UUID const &rhs) {
		this->a = rhs.a;
		this->b = rhs.b;
		return *this;
	}

	MCAPI std::string asString() const;
	MCAPI static UUID fromString(std::string const &source);
	MCAPI static UUID EMPTY;

	static UUID generateUUID() {
		static boost::uuids::random_generator uuidGen;
		return fromString(boost::lexical_cast<std::string>(uuidGen()));
	}
	static std::string generateUUIDAsString() {
		static boost::uuids::random_generator uuidGen;
		return boost::lexical_cast<std::string>(uuidGen());
	}

	inline bool empty() const noexcept { return ((this->a == 0) && (this->b == 0)); }
};

class Blob {
public:
	std::unique_ptr<uint8_t[]> buffer;
	size_t length = 0;

	inline Blob() {}
	inline Blob(Blob &&rhs) : buffer(std::move(rhs.buffer)), length(rhs.length) { rhs.length = 0; }
	inline Blob(size_t input_length) : buffer(std::make_unique<uint8_t[]>(input_length)), length(input_length) {}
	inline Blob(uint8_t const *input, size_t input_length) : Blob(input_length) {
		memcpy(this->buffer.get(), input, input_length);
	}

	inline Blob &operator=(Blob &&rhs) {
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

class Image {
	inline Image(ImageFormat format, uint32_t width, uint32_t height, ImageUsage usage, Blob &&data)
		: format(format), width(width), height(height), usage(usage), data(std::move(data)) {}

public:
	ImageFormat format{}; // 0x0
	uint32_t width{}, height{}; // 0x4, 0x8
	ImageUsage usage{}; // 0xC
	Blob data; // 0x10

	inline Image() {}
	inline Image(Blob &&data) : data(std::move(data)) {}
	inline Image(uint32_t width, uint32_t height, ImageFormat format, ImageUsage usage) : format(format), width(width), height(height), usage(usage) {}

	inline Image &operator=(Image &&rhs) {
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