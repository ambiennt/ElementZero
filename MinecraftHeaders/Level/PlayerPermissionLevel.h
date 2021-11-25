#pragma once

enum class PlayerPermissionLevel : int8_t {
	Visitor  = 0,
	Member   = 1,
	Operator = 2,
	Custom   = 3
};