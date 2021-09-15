#pragma once

enum class PlayerPermissionLevel : unsigned char {
  Visitor  = 0,
  Member   = 1,
  Operator = 2,
  Custom   = 3,
};