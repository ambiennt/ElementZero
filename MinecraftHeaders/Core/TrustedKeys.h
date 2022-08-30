#pragma once

#include "../dll.h"
#include <string>

namespace TrustedKeys {

// https://github.com/Nukkit/Nukkit/blob/feb254f995c9fe3ca936f0677c69cb3857c2009d/src/main/java/cn/nukkit/utils/ClientChainData.java#L35
MCAPI extern std::string const AuthServicePublicKey;

} // namespace TrustedKeys