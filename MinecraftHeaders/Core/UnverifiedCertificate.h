#pragma once

#include "WebToken.h"
#include "Certificate.h"
#include "../dll.h"

#include <memory>

class UnverifiedCertificate {
public:
	const WebToken                         mRawToken;
	std::unique_ptr<UnverifiedCertificate> mParentUnverifiedCertificate;
};

static_assert(offsetof(UnverifiedCertificate, mRawToken) == 0x0);
static_assert(offsetof(UnverifiedCertificate, mParentUnverifiedCertificate) == 0x80);
static_assert(sizeof(UnverifiedCertificate) == 0x88);