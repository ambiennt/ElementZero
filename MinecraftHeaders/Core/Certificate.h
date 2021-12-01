#pragma once

#include "UnverifiedCertificate.h"
#include "json.h"
#include "../dll.h"

#include <memory>

class Certificate {
public:
	UnverifiedCertificate        mUnverifiedCertificate;
	std::unique_ptr<Certificate> mParentCertificate;
	bool                         mIsValid;

	MCAPI Certificate(class Certificate const&);
	MCAPI int64_t getExpirationDate(void) const;
	MCAPI class Json::Value getExtraData(std::string const& key, class Json::Value const& defaultValue) const;
	MCAPI std::string getIdentityPublicKey(void) const;
	MCAPI int64_t getNotBeforeDate(void) const;
	MCAPI bool isCertificateAuthority(void) const;
	MCAPI bool validate(int64_t currentTime);
	MCAPI ~Certificate(void);
};

static_assert(offsetof(Certificate, mUnverifiedCertificate) == 0x0);
static_assert(offsetof(Certificate, mParentCertificate) == 0x88);
static_assert(offsetof(Certificate, mIsValid) == 0x90);
static_assert(sizeof(Certificate) == 0x98);