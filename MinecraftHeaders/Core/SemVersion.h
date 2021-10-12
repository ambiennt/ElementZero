#pragma once

#include <string>

struct SemVersion {
  unsigned short major{}, minor{}, patch{};     // 0, 2, 4
  std::string pre_release, build_meta, full_version_string;  // 8, 40, 72
  bool valid_version{}, any_version{};          // 104, 105
};

static_assert(sizeof(SemVersion) == 0x70);