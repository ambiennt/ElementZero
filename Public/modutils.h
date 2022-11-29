#pragma once

#include <cstdint>
#include <type_traits>
#include "../Base/include/base/base.h"

template <typename F> auto IIFE(F f) { return f(); }

template <class T> struct remove_cvref { typedef std::remove_cv_t<std::remove_reference_t<T>> type; };

template <class T> using remove_cvref_t = typename remove_cvref<T>::type;

// obtains a reference to a class field at the given offset
template <typename TreatAs, typename Pointer>
constexpr inline TreatAs &directAccess(Pointer ptr, ptrdiff_t offset) {
	return *reinterpret_cast<TreatAs *>(reinterpret_cast<uintptr_t>(ptr) + offset);
}

// allows the assigning of fake fields to a class with a given offset, without the need for padding
// if your class is small and/or has mostly primitive types then I would suggest defining fields normally
#define CLASS_FIELD(name, offset, ...)																					\
	__declspec(property(get = GET_FIELD_##name, put = SET_FIELD_##name)) __VA_ARGS__ name;								\
	__VA_ARGS__ &GET_FIELD_##name() const { return directAccess<__VA_ARGS__>(this, offset); }							\
	template <typename T> void SET_FIELD_##name(const T &value) { directAccess<__VA_ARGS__>(this, offset) = value; }