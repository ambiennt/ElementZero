#pragma once

#include <memory>
#include <array>

#include "../Command/CommandPermissionLevel.h"
#include "PlayerPermissionLevel.h"

class PermissionsHandler {
public:
  CommandPermissionLevel mCommandPermissionsLevel;
  PlayerPermissionLevel mPlayerPermissions;
};

class Ability {
public:
  enum class Type : char {
    Invalid  = 0,
    Unset    = 1,
    Boolean  = 2,
    Float    = 3
  };

  enum class Options : char {
    None                         = 0,
    NoSave                       = 1,
    CommandExposed               = 2,
    PermissionsInterfaceExposed  = 4,
    WorldbuilderOverrides        = 8
  };
  
  union Value {
    bool val_bool;
    float val_float;
    Value(bool flag) { val_bool = flag; }
    Value(float val) { val_float = val; }
    Value() {}
  };
  Type type = Type::Invalid;
  Value value{};
  Options opts = Options::None;
};

class Abilities {
public:
  std::unique_ptr<PermissionsHandler> mPermissionsHandler;
  std::array<Ability, 18> Abilities;
  std::array<Ability, 8> CustomAbilities;
};