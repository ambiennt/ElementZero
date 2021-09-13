#pragma once

#include "mce.h"
#include "SemVersion.h"

enum struct PackType : char {
  Invalid          = 0,
  Addon            = 1,
  Cached           = 2,
  CopyProtected    = 3,
  Behavior         = 4,
  PersonaPiece     = 5,
  Resources        = 6,
  Skins            = 7,
  WorldTemplate    = 8,
  PackTypeCount    = 9
};

struct PackIdVersion {
  mce::UUID uuid;
  SemVersion version;
  PackType type;
};