#pragma once

#include "Certificate.h"
#include "WebToken.h"
#include "UnverifiedCertificate.h"
#include "ExtendedCertificate.h"
#include "../dll.h"

#include "../Actor/Skin/persona.h"
#include <unordered_map>

class ConnectionRequest {
public:
	std::unique_ptr<UnverifiedCertificate> mCertificateData;
	std::unique_ptr<Certificate>           mCertificate;
	std::unique_ptr<WebToken>              mRawToken;
	uint8_t                                mClientSubId;

	MCAPI ConnectionRequest(class ConnectionRequest const&);
	MCAPI static class ConnectionRequest fromString(std::string const&);
	MCAPI std::vector<class AnimatedImageData> getAnimatedImageData(void) const;
	MCAPI std::string getArmSize(void) const;
	MCAPI std::vector<uint8_t> getCapeData(void) const;
	MCAPI std::string getCapeId(void) const;
	MCAPI std::string getClientPlatformId(void) const;
	MCAPI std::string getClientPlatformOfflineId(void) const;
	MCAPI std::string getClientPlatformOnlineId(void) const;
	MCAPI uint64_t getClientRandomId(void) const;
	MCAPI std::string getClientThirdPartyName(void) const;
	MCAPI std::string getDeviceId(void) const;
	MCAPI std::vector<class SerializedPersonaPieceHandle> getPersonaPieces(void) const;
	MCAPI std::string getSelfSignedId(void) const;
	MCAPI std::string getSkinAnimationData(void) const;
	MCAPI class Color getSkinColor(void) const;
	MCAPI std::vector<uint8_t> getSkinData(void) const;
	MCAPI std::string getSkinGeometry(void) const;
	MCAPI std::string getSkinId(void) const;
	MCAPI std::string getSkinResourcePatch(void) const;
	MCAPI std::string getTenantId(void) const;
	MCAPI bool isPersonaSkin(void) const;
	MCAPI std::string toString(void);
	MCAPI bool verify(class std::vector<std::string> const& trustedKeys, int64_t currentTime);
	MCAPI bool verifySelfSigned(void);
	MCAPI std::unordered_map<enum persona::PieceType, class TintMapColor> getPieceTintColors(void) const;
	MCAPI ~ConnectionRequest(void);

	inline uint32_t getTitleId(void) {
		// make as a string first because asUInt() seems to always fail
		std::string const& titleIdStr = this->mCertificate->getExtraData("titleId", "").asString("");
		if (titleIdStr.empty()) return 0;
		for (const char& c : titleIdStr) {
			if (!std::isdigit(c)) return 0;
		}
		return (uint32_t)(std::stoull(titleIdStr));
	}

	inline uint64_t getXuidAsUInt64(void) const {
		std::string const& xuidStr = ExtendedCertificate::getXuid(*this->mCertificate.get());
		return (xuidStr.empty() ? 0 : std::stoull(xuidStr));
	}
};

static_assert(sizeof(ConnectionRequest) == 32);

class SubClientConnectionRequest {
public:
	std::unique_ptr<UnverifiedCertificate> mCertificateData;
	std::unique_ptr<Certificate>           mCertificate;
	std::unique_ptr<WebToken>              mRawToken;
};

static_assert(sizeof(SubClientConnectionRequest) == 24);