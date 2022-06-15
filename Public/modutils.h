#pragma once

#include <type_traits>
#include "../Base/include/base/base.h"

template <typename F> auto IIFE(F f) { return f(); }

template <class T> struct remove_cvref { typedef std::remove_cv_t<std::remove_reference_t<T>> type; };

template <class T> using remove_cvref_t = typename remove_cvref<T>::type;

template <typename Ret, typename Type> Ret &direct_access(Type *type, size_t offset) {
  union {
    size_t raw;
    Type *source;
    Ret *target;
  } u;
  u.source = type;
  u.raw += offset;
  return *u.target;
}






// use BUILD_ACCESS_MUT as a macro for a mutable instance of a field (like you would with direct_access)
// its useful so you don't have to worry about padding when filling in fields from classes
// if your class is small and/or has mostly primitive types then I would suggest defining fields normally

#define AS_FIELD(type, name, fn) __declspec(property(get = fn)) type name
#define DEF_FIELD_RW(type, name) __declspec(property(get = get##name, put = set##name)) type name

// read only getter that returns a copy
#define BUILD_ACCESS(type, name, offset)                                                                               \
  AS_FIELD(type, name, get##name);                                                                                     \
  type get##name() const { return direct_access<type>(this, offset); }

// read and write getter/setter that returns a reference
#define BUILD_ACCESS_MUT(type, name, offset)                                                                           \
  DEF_FIELD_RW(type, name);                                                                                            \
  type &get##name() const { return direct_access<type>(this, offset); }                                                \
  template<typename T>void set##name(T const &value) { direct_access<type>(this, offset) = value; }

#define BUILD_ACCESS_COMPAT(type, name)                                                                                \
  AS_FIELD(type, name, get##name);                                                                                     \
  BASEAPI type get##name() const;