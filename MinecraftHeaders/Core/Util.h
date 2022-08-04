#pragma once

#include <string>
#include "../dll.h"

namespace Util {

MCAPI std::string const EMPTY_GUID;

MCAPI std::string base64_decode(std::string const &strToDecode);
MCAPI std::string base64url_decode(std::string strToDecode);

MCAPI std::string base64_encode(uint8_t *bytesToEncode, uint32_t inLength, bool pad = true);
MCAPI std::string base64url_encode(std::string strToEncode);
inline std::string base64_encode(std::string const &strToEncode, bool pad = true) {
    return base64_encode((uint8_t *)strToEncode.c_str(), strToEncode.length(), pad);
}

} // namespace Util