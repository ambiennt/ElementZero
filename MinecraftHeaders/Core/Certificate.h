#pragma once

#include "UnverifiedCertificate.h"
#include "json.h"
#include "../dll.h"

#include <memory>

class Certificate {
public:
	UnverifiedCertificate        unverified;
	std::unique_ptr<Certificate> parent;
	bool                         isValid;

	MCAPI Certificate(class Certificate const&);
	MCAPI int64_t getExpirationDate(void) const;
	MCAPI class Json::Value getExtraData(std::string const& key, class Json::Value const& defaultValue) const;
	MCAPI std::string getIdentityPublicKey(void) const;
	MCAPI int64_t getNotBeforeDate(void) const;
	MCAPI bool isCertificateAuthority(void) const;
	MCAPI bool validate(int64_t currentTime);
	MCAPI ~Certificate(void);
};