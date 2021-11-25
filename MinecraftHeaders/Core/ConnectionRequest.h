#pragma once

#include "Certificate.h"
#include "WebToken.h"
#include "UnverifiedCertificate.h"
#include "../dll.h"

#include "../Actor/Skin/Persona.h"
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
	//MCAPI class mce::Color getSkinColor(void) const; // todo
	MCAPI std::vector<uint8_t> getSkinData(void) const;
	MCAPI std::string getSkinGeometry(void) const;
	MCAPI std::string getSkinId(void) const;
	MCAPI std::string getSkinResourcePatch(void) const;
	MCAPI std::string getTenantId(void) const;
	MCAPI bool isPersonaSkin(void) const;
	MCAPI std::string toString(void);
	MCAPI bool verify(class std::vector<std::string> const&, int64_t);
	MCAPI bool verifySelfSigned(void);
	MCAPI std::unordered_map<enum persona::PieceType, class TintMapColor> getPieceTintColors(void) const;
	MCAPI ~ConnectionRequest(void);
};

static_assert(sizeof(ConnectionRequest) == 32);

class SubClientConnectionRequest {
public:
	std::unique_ptr<UnverifiedCertificate> mCertificateData;
	std::unique_ptr<Certificate>           mCertificate;
	std::unique_ptr<WebToken>              mRawToken;
	uint8_t                                mClientSubId;
};