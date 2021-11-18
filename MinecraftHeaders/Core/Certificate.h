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
    MCAPI __int64 getExpirationDate(void) const;
    MCAPI class Json::Value getExtraData(std::string const&, class Json::Value const&) const;
    MCAPI std::string getIdentityPublicKey(void) const;
    MCAPI __int64 getNotBeforeDate(void) const;
    MCAPI bool isCertificateAuthority(void) const;
    MCAPI bool validate(__int64);
    MCAPI ~Certificate(void);
};