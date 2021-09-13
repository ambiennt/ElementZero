#pragma once

enum class PlayerPermissions : unsigned char { //PlayerPermissionLevel
  Visitor  = 0,
  Member   = 1,
  Operator = 2,
  Custom   = 3,
};