#pragma once

#include <string>
#include "../dll.h"

class Certificate;
namespace mce {
class UUID;
}

class ExtendedCertificate {
public:
	static MCAPI std::string getXuid(Certificate const &);
	static MCAPI mce::UUID getIdentity(Certificate const &);
	static MCAPI std::string getIdentityName(Certificate const &);
};