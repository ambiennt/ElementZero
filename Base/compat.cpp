#include <Actor/Player.h>
#include <Math/Vec3.h>
#include <Core/Minecraft.h>
#include <Command/CommandOutput.h>
#include <Level/Level.h>
#include <Item/Item.h>
#include <Net/NetworkIdentifier.h>
#include <Net/ServerNetworkHandler.h>
#include <RakNet/RakPeer.h>

#include <modutils.h>
#include <base/base.h>
#include "loader.h"

#pragma region Player

// ServerPlayer::handleActorPickRequestOnServer
class SynchedActorData &Actor::getEntityData() const {
	return direct_access<class SynchedActorData>(this, 320); // verified
}

// Actor::Actor
class SimpleContainer &Actor::getEquipmentContainer() const {
	return *direct_access<std::unique_ptr<SimpleContainer>>(this, 1400).get(); // verified
}

// Actor::Actor
class SimpleContainer &Actor::getHandContainer() const {
	return *direct_access<std::unique_ptr<SimpleContainer>>(this, 1408).get(); // verified
}

// xref to Actor::transferTickingArea
class Dimension *Actor::getDimension() const {
	return direct_access<class Dimension *>(this, 808); // verified
}

// Player::Player
class Certificate &Player::getCertificate() const {
	return *direct_access<class Certificate *>(this, 2736); // verified
}

// Player::setBedRespawnPosition
class BlockPos &Player::getSpawnPosition() const {
	return direct_access<class BlockPos>(this, 7176);
}

// ServerPlayer::ServerPlayer
class NetworkIdentifier const &Player::getNetworkIdentifier() const {
	return direct_access<class NetworkIdentifier const>(this, 8048);
}

// AddPlayerPacket::AddPlayerPacket
std::string &Player::getDeviceId() const {
	return direct_access<std::string>(this, 7872);
}

// ServerNetworkHandler::_createNewPlayer
std::string &Player::getClientPlatformId() const {
	return direct_access<std::string>(this, 2744); // verified
}

// ServerNetworkHandler::_createNewPlayer
std::string &Player::getPlatformOfflineId() const {
	return direct_access<std::string>(this, 2680);  // verified
}

// ServerNetworkHandler::_createNewPlayer
std::string &Player::getClientPlatformOnlineId() const {
	return direct_access<std::string>(this, 3528); // verified
}

// RaidBossComponent::_sendBossEvent
uint8_t Player::getClientSubId() const {
	return direct_access<uint8_t>(this, 3520); // verified
}

// custom player fields setup
THook(void*,
	"??0Player@@QEAA@AEAVLevel@@AEAVPacketSender@@W4GameType@@AEBVNetworkIdentifier@@EVUUID@mce@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$unique_ptr@VCertificate@@U?$default_delete@VCertificate@@@std@@@8@55@Z",
	Player* player, void *level, void *packetSender, int32_t playerGameType, void *owner,
	const uint8_t subid, void *uuid, void *deviceId, void *certificate, void *platformId, void *platformOnlineId) {

	auto ret = original(player, level, packetSender, playerGameType, owner, subid, uuid, deviceId, certificate, platformId, platformOnlineId);
	auto& unusedVec = direct_access<Vec3>(player, 0xB24); // Player::mFirstPersonLatestHandOffset (store a pointer here at unused field)
	unusedVec.x = unusedVec.y = unusedVec.z = 0;
	direct_access<EZPlayerFields*>(player, 0xB24) = new EZPlayerFields();
	return ret;
}

THook(void*, "??1Player@@UEAA@XZ", Player* player) {

	auto pf = direct_access<EZPlayerFields*>(player, 0xB24);
	delete pf; // clean up to be safe because idk what bds does with this field
	pf = nullptr;
	return original(player);
}

struct EZPlayerFields* Player::getEZPlayerFields() const {
	return direct_access<struct EZPlayerFields*>(this, 0xB24);
}

#pragma endregion

void NetworkIdentifier::kick(std::string const &reason) const {
	LocateService<ServerNetworkHandler>()->disconnectClient(*this, 0, reason, reason.empty());
}

void Player::kick() { LocateService<ServerNetworkHandler>()->forceDisconnectClient(this->asServerPlayer(), true); }

std::string &ServerNetworkHandler::getMotd() { return direct_access<std::string>(this, 600); } // verified

void CommandOutput::success() { direct_access<bool>(this, 40) = true; }

uint64_t Level::getServerTick() {
	return CallServerClassMethod<const struct Tick>("?getCurrentServerTick@Level@@UEBA?BUTick@@XZ", this).value;
}

ActorUniqueID Level::getNewUniqueID() const {
	return ActorUniqueID(++this->mLastUniqueID.value);
}

// RaidBossComponent::_sendBossEvent
PacketSender &Level::getPacketSender() const { return *direct_access<PacketSender *>(this, 2240); } // verified

LevelDataWrapper &Level::getLevelDataWrapper() { return direct_access<LevelDataWrapper>(this, 544); } // verified

template <> Minecraft *LocateService<Minecraft>() {
	return *GetServerSymbol<Minecraft *>("?mGame@ServerCommand@@1PEAVMinecraft@@EA");
}

template <> ServerNetworkHandler *LocateService<ServerNetworkHandler>() {
	return LocateService<Minecraft>()->getServerNetworkHandler();
}

template <> NetworkHandler *LocateService<NetworkHandler>() {
	return direct_access<std::unique_ptr<NetworkHandler>>(LocateService<ServerInstance>(), 152).get(); // verified
}

template <> MinecraftCommands *LocateService<MinecraftCommands>() { return LocateService<Minecraft>()->getCommands(); }

MinecraftCommands *Minecraft::getCommands() { return direct_access<MinecraftCommands *>(this, 160); }

RakNet::SystemAddress NetworkIdentifier::getRealAddress() const {
	return LocateService<RakNet::RakPeer>()->GetSystemAddressFromGuid(guid);
}

TClasslessInstanceHook(bool, "?loadLevelData@DBStorage@@UEAA_NAEAVLevelData@@@Z", void *data) {
	auto &path = direct_access<std::string>(this, 160);
	worldHook(std::filesystem::weakly_canonical(path));
	return original(this, data);
}