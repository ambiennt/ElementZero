#pragma once

#include <string>
#include "../dll.h"

namespace Common {
	MCAPI std::string getServerVersionString();
	MCAPI std::string getGameSemVerString();
}