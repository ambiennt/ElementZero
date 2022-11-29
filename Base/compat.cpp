#include "include/base/compat.h"

std::string session;

mce::UUID const& getSessionUUID() {
	if (!session.empty()) {
		static auto result = mce::UUID::fromString(session);
		return result;
	}
	return mce::UUID::EMPTY;
}

TClasslessInstanceHook(int32_t,
	"?start@DedicatedServer@@QEAA?AW4StartResult@1@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@@Z",
	const std::string& uuid) {
	session = uuid;
	return original(this, uuid);
}

TClasslessInstanceHook(void,
	"?announceServer@RakNetServerLocator@@UEAAXAEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@0W4GameType@@HH_N@Z",
	std::string const &playerName, std::string const &worldName, int32_t gameType,
	int32_t numPlayers, int32_t maxNumPlayers, bool isJoinableThroughServerScreen) {

	directAccess<RakNet::RakPeer*>(this, 0x118) = LocateService<RakNet::RakPeer>();
	original(this, playerName, worldName, gameType, numPlayers, maxNumPlayers, isJoinableThroughServerScreen);
	directAccess<RakNet::RakPeer*>(this, 0x118) = nullptr;
}

TClasslessInstanceHook(bool, "?loadLevelData@DBStorage@@UEAA_NAEAVLevelData@@@Z", void *data) {
	auto &path = directAccess<std::string>(this, 0xA0);
	worldHook(std::filesystem::weakly_canonical(path));
	return original(this, data);
}









static DedicatedServer *mDedicatedServer    = nullptr;
static RakNet::RakPeer *mRakPeer            = nullptr;
static AppPlatform *mAppPlatform            = nullptr;
static MinecraftServerScriptEngine *mEngine = nullptr;

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

THook(void*, "??0ScriptEngine@@QEAA@W4ApiScriptType@ScriptApi@@@Z", void* self, int32_t ApiScriptType) {
	auto ret = original(self, ApiScriptType);
	if (!mEngine) { mEngine = (MinecraftServerScriptEngine*)self; }
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

template <> MinecraftServerScriptEngine *LocateService<MinecraftServerScriptEngine>() { return mEngine; }

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







void ServerNetworkHandler::forceDisconnectClient(const Player& player,
	bool skipPlayerLeftChatMsg, const std::string& disconnectMsg) {
	this->forceDisconnectClient(player.mNetworkIdentifier, player.mClientSubId, skipPlayerLeftChatMsg, disconnectMsg);
}

void ServerNetworkHandler::forceDisconnectClient(const NetworkIdentifier& netId, uint8_t subId,
	bool skipPlayerLeftChatMsg, const std::string& disconnectMsg) {

	auto sendPkt = [&]() -> void {
		DisconnectPacket pkt(disconnectMsg.empty(), disconnectMsg);
		this->mPacketSender->sendToClient(netId, pkt, subId)
;	};

	this->mPacketSender->flush(netId, std::move(sendPkt));
	this->onDisconnect(netId, skipPlayerLeftChatMsg);
}

void CommandOutput::success() { directAccess<bool>(this, 40) = true; }

RakNet::SystemAddress NetworkIdentifier::getRealAddress() const {
	return LocateService<RakNet::RakPeer>()->GetSystemAddressFromGuid(this->mGuid);
}

bool EnchantUtils::applyUnfilteredEnchant(ItemStackBase &out, EnchantmentInstance const& newEnchant, bool overwriteDuplicates) {

	auto resultEnchants = out.constructItemEnchantsFromUserData(); // get current ItemEnchants for the given itemstack
	int32_t activationIndex = EnchantUtils::determineActivation(newEnchant.mEnchantType); // get the proper index for ItemEnchants::mItemEnchants[3]

	if ((activationIndex >= 0) && (activationIndex <= 2)) { // boundary checking...

		auto &instanceVectorToWriteTo = resultEnchants.mItemEnchants[activationIndex];
		if (overwriteDuplicates) {

			for (int32_t i = 0; i < instanceVectorToWriteTo.size(); i++) {

				if (instanceVectorToWriteTo[i].mEnchantType == newEnchant.mEnchantType) { // if the enchant id is the same, overwrite at that index

					instanceVectorToWriteTo[i] = newEnchant;
					EnchantUtils::_convertBookCheck(out);
					out.saveEnchantsToUserData(resultEnchants);
					return true;
				}
			}
		}

		instanceVectorToWriteTo.push_back(newEnchant); // add newEnchant to current enchants
		EnchantUtils::_convertBookCheck(out); // convert newEnchant to a book enchant if the given itemstack is a book
		out.saveEnchantsToUserData(resultEnchants); // apply newEnchant to the given itemstack
		return true;
	}

	return false;
}

bool EnchantUtils::removeEnchant(ItemStackBase &out, Enchant::Type typeToRemove) {

	auto resultEnchants = out.constructItemEnchantsFromUserData();
	int32_t activationIndex = EnchantUtils::determineActivation(typeToRemove);

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
	constexpr int32_t ENCHANTS_ARRAY_SIZE = 3;
	for (int32_t i = 0; i < ENCHANTS_ARRAY_SIZE; i++) {
		resultEnchants.mItemEnchants[i].clear();
	}
	out.saveEnchantsToUserData(resultEnchants);
}