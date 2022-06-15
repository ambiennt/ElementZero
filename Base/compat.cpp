#include "include/base/compat.h"








std::string session;

mce::UUID const& getSessionUUID() {
  	if (!session.empty()) {
    	static auto result = mce::UUID::fromString(session);
    	return result;
  	}
  	return mce::UUID::EMPTY;
}

THook(DedicatedServer::StartResult,
  	"?start@DedicatedServer@@QEAA?AW4StartResult@1@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z",
  	void* self, std::string const &uuid) {
  	session = uuid;
  	return original(self, uuid);
}

TClasslessInstanceHook(void,
  	"?announceServer@RakNetServerLocator@@UEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0W4GameType@@HH_N@Z",
  	std::string const &playerName, std::string const &worldName, int32_t gameType,
  	int32_t numPlayers, int32_t maxNumPlayers, bool isJoinableThroughServerScreen) {

  	direct_access<RakNet::RakPeer*>(this, 0x118) = LocateService<RakNet::RakPeer>();
  	original(this, playerName, worldName, gameType, numPlayers, maxNumPlayers, isJoinableThroughServerScreen);
  	direct_access<RakNet::RakPeer*>(this, 0x118) = nullptr;
}

TClasslessInstanceHook(bool, "?loadLevelData@DBStorage@@UEAA_NAEAVLevelData@@@Z", void *data) {
	auto &path = direct_access<std::string>(this, 0xA0);
	worldHook(std::filesystem::weakly_canonical(path));
	return original(this, data);
}










static DedicatedServer *mDedicatedServer = nullptr;
static RakNet::RakPeer *mRakPeer         = nullptr;
static AppPlatform *mAppPlatform         = nullptr;

THook(void*, "??0DedicatedServer@@QEAA@XZ", void* self) {
	auto ret = original(self);
	if (!mDedicatedServer) { mDedicatedServer = (DedicatedServer*)self; }
	return ret;
}

THook(void*, "??0AppPlatform@@QEAA@_N@Z", void* self, bool registerService) {
  	auto ret = original(self, registerService);
  	if (!mAppPlatform) { mAppPlatform = (AppPlatform*)self; }
  	return ret;
}

THook(void*, "??0RakPeer@RakNet@@QEAA@XZ", void *self) {
  	auto ret = original(self);
	if (!mRakPeer) { mRakPeer = (RakNet::RakPeer*)self; }
	return ret;
}








template <> ServerInstance *LocateService<ServerInstance>() {
  	static auto ptr = GetServerSymbol<ServerInstance *>(
		"?mService@?$ServiceLocator@VServerInstance@@@@0V?$NonOwnerPointer@VServerInstance@@@Bedrock@@A");
  	return *ptr;
}

template <> DedicatedServer *LocateService<DedicatedServer>() { return mDedicatedServer; }

template <> RakNet::RakPeer *LocateService<RakNet::RakPeer>() { return mRakPeer; }

template <> AppPlatform *LocateService<AppPlatform>() { return mAppPlatform; }

template <> Minecraft *LocateService<Minecraft>() {
	return LocateService<ServerInstance>()->mMinecraft.get();
}

template <> ServerNetworkHandler *LocateService<ServerNetworkHandler>() {
	return LocateService<Minecraft>()->getServerNetworkHandler();
}

template <> NetworkHandler *LocateService<NetworkHandler>() {
	return LocateService<ServerInstance>()->mNetwork.get();
}

template <> MinecraftCommands *LocateService<MinecraftCommands>() {
	return LocateService<Minecraft>()->mCommands.get();
}

template <> CommandRegistry *LocateService<CommandRegistry>() {
	return LocateService<MinecraftCommands>()->mRegistry.get();
}

template <> Level *LocateService<Level>() {
	return LocateService<Minecraft>()->getLevel();
}

template <> LoopbackPacketSender *LocateService<LoopbackPacketSender>() {
	return LocateService<ServerInstance>()->mPacketSender.get();
}































#pragma region player

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

#pragma endregion

















void ServerNetworkHandler::forceDisconnectClient(Player const& player,
	bool skipDisconnectScreen, bool skipPlayerLeftChatMsg, std::string const& disconnectMsg) {
	this->forceDisconnectClient(player.getNetworkIdentifier(), player.mClientSubId,
		skipDisconnectScreen, skipPlayerLeftChatMsg, disconnectMsg);
}

void ServerNetworkHandler::forceDisconnectClient(NetworkIdentifier const& netId, uint8_t subId,
	bool skipDisconnectScreen, bool skipPlayerLeftChatMsg, std::string const& disconnectMsg) {
	this->disconnectClient(netId, subId, disconnectMsg, skipDisconnectScreen);
	this->onDisconnect(netId, disconnectMsg, skipPlayerLeftChatMsg);
}

void CommandOutput::success() { direct_access<bool>(this, 40) = true; }

// RaidBossComponent::_sendBossEvent
PacketSender &Level::getPacketSender() const { return *direct_access<PacketSender *>(this, 2240); } // verified

LevelDataWrapper &Level::getLevelDataWrapper() { return direct_access<LevelDataWrapper>(this, 544); } // verified

uint64_t Level::getServerTick() {
	return (uint64_t)(CallServerClassMethod<const struct Tick>("?getCurrentServerTick@Level@@UEBA?BUTick@@XZ", this).value);
}

struct ActorUniqueID Level::getNewUniqueID() const {
	return ActorUniqueID(++this->mLastUniqueID.value);
}

RakNet::SystemAddress NetworkIdentifier::getRealAddress() const {
	return LocateService<RakNet::RakPeer>()->GetSystemAddressFromGuid(this->mGuid);
}

bool EnchantUtils::applyUnfilteredEnchant(ItemStackBase &out, EnchantmentInstance const& newEnchant, bool overwriteDuplicates) {

	auto resultEnchants = out.constructItemEnchantsFromUserData(); // get current ItemEnchants for the given itemstack
	int32_t activationIndex = determineActivation(newEnchant.mEnchantType); // get the proper index for ItemEnchants::mItemEnchants[3]

	if ((activationIndex >= 0) && (activationIndex <= 2)) { // boundary checking...

		auto &instanceVectorToWriteTo = resultEnchants.mItemEnchants[activationIndex];
		if (overwriteDuplicates) {

			for (int32_t i = 0; i < instanceVectorToWriteTo.size(); i++) {

				if (instanceVectorToWriteTo[i].mEnchantType == newEnchant.mEnchantType) { // if the enchant id is the same, overwrite at that index

					instanceVectorToWriteTo[i] = newEnchant;
					_convertBookCheck(out);
					out.saveEnchantsToUserData(resultEnchants);
					return true;
				}
			}
		}

		instanceVectorToWriteTo.push_back(newEnchant); // add newEnchant to current enchants
		_convertBookCheck(out); // convert newEnchant to a book enchant if the given itemstack is a book
		out.saveEnchantsToUserData(resultEnchants); // apply newEnchant to the given itemstack
		return true;
	}

	return false;
}

bool EnchantUtils::removeEnchant(ItemStackBase &out, Enchant::Type typeToRemove) {

	auto resultEnchants = out.constructItemEnchantsFromUserData();
	int32_t activationIndex = determineActivation(typeToRemove);

	if ((activationIndex >= 0) && (activationIndex <= 2)) {

		auto &instanceVectorToWriteTo = resultEnchants.mItemEnchants[activationIndex];
		bool atLeastOneRemoved = false;
		auto it = instanceVectorToWriteTo.begin();

		while (it != instanceVectorToWriteTo.end()) {
			if (it->mEnchantType == typeToRemove) {
				it = instanceVectorToWriteTo.erase(it);
				atLeastOneRemoved = true;
			}
			else ++it;
		}

		if (atLeastOneRemoved) {
			out.saveEnchantsToUserData(resultEnchants);
		}
		return atLeastOneRemoved;
	}
	return false;
}

void EnchantUtils::removeAllEnchants(ItemStackBase &out) {

	auto resultEnchants = out.constructItemEnchantsFromUserData();

	const int32_t ENCHANTS_ARRAY_SIZE = 3;
	for (int32_t i = 0; i < ENCHANTS_ARRAY_SIZE; i++) {
		resultEnchants.mItemEnchants[i].clear();
	}

	out.saveEnchantsToUserData(resultEnchants);
}