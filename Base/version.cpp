#include <hook.h>
#include <string>

#include "Core/SharedConstants.h"

#ifndef EZVERSION
#  define EZVERSION ""
#endif

THook(std::string,
	"?getServerVersionString@Common@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ") {
	return original() + " protocol v" + std::to_string(SharedConstants::NetworkProtocolVersion) + " with ElementZero (" EZVERSION ")";
}