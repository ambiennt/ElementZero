#pragma once
#include "WebToken.h"
#include "Certificate.h"

class UnverifiedCertificate {
public:
    const WebToken                         rawToken;
    std::unique_ptr<UnverifiedCertificate> parentUnverified;
};

static_assert(offsetof(UnverifiedCertificate, rawToken) == 0x0);
static_assert(offsetof(UnverifiedCertificate, parentUnverified) == 0x80);
static_assert(sizeof(UnverifiedCertificate) == 0x88);