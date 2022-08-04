#pragma once

#include "Certificate.h"
#include "WebToken.h"
#include "UnverifiedCertificate.h"
#include "ExtendedCertificate.h"
#include "../Actor/Skin/persona.h"
#include "../dll.h"

#include <unordered_map>

class AnimatedImageData;
class SerializedPersonaPieceHandle;
class Color;
class TintMapColor;

class ConnectionRequest {
public:
	std::unique_ptr<UnverifiedCertificate> mCertificateData;
	std::unique_ptr<Certificate>           mCertificate;
	std::unique_ptr<WebToken>              mRawToken;
	uint8_t                                mClientSubId;

	MCAPI ConnectionRequest(ConnectionRequest const&);
	MCAPI static ConnectionRequest fromString(std::string const&);
	MCAPI std::vector<AnimatedImageData> getAnimatedImageData() const;
	MCAPI std::string getArmSize() const;
	MCAPI std::vector<uint8_t> getCapeData() const;
	MCAPI std::string getCapeId() const;
	MCAPI std::string getClientPlatformId() const;
	MCAPI std::string getClientPlatformOfflineId() const;
	MCAPI std::string getClientPlatformOnlineId() const;
	MCAPI uint64_t getClientRandomId() const;
	MCAPI std::string getClientThirdPartyName() const;
	MCAPI std::string getDeviceId() const;
	MCAPI std::vector<SerializedPersonaPieceHandle> getPersonaPieces() const;
	MCAPI std::string getSelfSignedId() const;
	MCAPI std::string getSkinAnimationData() const;
	MCAPI Color getSkinColor() const;
	MCAPI std::vector<uint8_t> getSkinData() const;
	MCAPI std::string getSkinGeometry() const;
	MCAPI std::string getSkinId() const;
	MCAPI std::string getSkinResourcePatch() const;
	MCAPI std::string getTenantId() const;
	MCAPI bool isPersonaSkin() const;
	MCAPI std::string toString();
	MCAPI bool verify(std::vector<std::string> const& trustedKeys, int64_t currentTime);
	MCAPI bool verifySelfSigned();
	MCAPI std::unordered_map<persona::PieceType, TintMapColor> getPieceTintColors() const;
	MCAPI ~ConnectionRequest();

	inline uint32_t getTitleID() const {
		uint32_t result = 0;
		std::string titleIdStr = this->mCertificate->getExtraData("titleId", "").asString("");
		if (titleIdStr.empty()) return result;
		try {
			result = (uint32_t)std::stoull(titleIdStr);
		}
		catch (std::invalid_argument const &i) {}
		return result;
	}

	inline uint64_t getXUIDAsUInt64() const {
		uint64_t result = 0;
		std::string xuidStr = ExtendedCertificate::getXuid(*this->mCertificate.get());
		if (xuidStr.empty()) return result;
		try {
			result = std::stoull(xuidStr);
		}
		catch (std::invalid_argument const &i) {}
		return result;
	}
};

static_assert(sizeof(ConnectionRequest) == 0x20);

class SubClientConnectionRequest {
public:
	std::unique_ptr<UnverifiedCertificate> mCertificateData;
	std::unique_ptr<Certificate>           mCertificate;
	std::unique_ptr<WebToken>              mRawToken;
};

static_assert(sizeof(SubClientConnectionRequest) == 0x18);