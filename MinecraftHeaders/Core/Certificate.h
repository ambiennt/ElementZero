#pragma once

#include "UnverifiedCertificate.h"
#include "json.h"
#include "../dll.h"

#include <memory>

class Certificate {
public:
	UnverifiedCertificate        mUnverifiedCertificate; // 0x0
	std::unique_ptr<Certificate> mParentCertificate; // 0x88
	bool                         mIsValid; // 0x90

	MCAPI Certificate(Certificate const&);
	MCAPI int64_t getExpirationDate() const;
	MCAPI Json::Value getExtraData(std::string const& key, Json::Value const& defaultValue) const;
	MCAPI std::string getIdentityPublicKey() const;
	MCAPI int64_t getNotBeforeDate() const;
	MCAPI bool isCertificateAuthority() const;
	MCAPI bool validate(int64_t currentTime);
	MCAPI ~Certificate();
};

static_assert(offsetof(Certificate, mUnverifiedCertificate) == 0x0);
static_assert(offsetof(Certificate, mParentCertificate) == 0x88);
static_assert(offsetof(Certificate, mIsValid) == 0x90);
static_assert(sizeof(Certificate) == 0x98);