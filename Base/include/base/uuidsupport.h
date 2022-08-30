#pragma once

#include <cstdint>
#include <functional>

#include <boost/functional/hash.hpp>

#include <Core/mce.h>

namespace std {

template <> struct hash<mce::UUID> {
  constexpr size_t operator()(const mce::UUID &val) const { return val.mostSig ^ val.leastSig; }
};

} // namespace std

namespace boost {

template <> struct hash<mce::UUID> {
  constexpr size_t operator()(const mce::UUID &val) const { return val.mostSig ^ val.leastSig; }
};

} // namespace boost