#pragma once

enum class CommandPermissionLevel : int8_t {
  Any         = 0,
  GameMasters = 1, // operator
  Admin       = 2,
  Host        = 3,
  Owner       = 4,
  Internal    = 5
};