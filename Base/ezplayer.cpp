#include "include/base/ezplayer.h"
#include <Actor/ServerPlayer.h>

// EZPlayer setup
THook(void*,
	"??0Player@@QEAA@AEAVLevel@@AEAVPacketSender@@W4GameType@@AEBVNetworkIdentifier@@EVUUID@mce@@AEBV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@V?$unique_ptr@VCertificate@@U?$default_delete@VCertificate@@@std@@@8@55@Z",
	Player* player, void *level, void *packetSender, int32_t playerGameType, void *owner,
	const uint8_t subid, void *uuid, void *deviceId, void *certificate, void *platformId, void *platformOnlineId) {

	auto ret = original(player, level, packetSender, playerGameType, owner, subid, uuid, deviceId, certificate, platformId, platformOnlineId);
	player->mEZPlayer = new EZPlayer(); // store pointer at unused field, Player::mFirstPersonLatestHandOffset
	return ret;
}

THook(void*, "??1Player@@UEAA@XZ", Player* player) {
	auto ret = original(player);
	delete player->mEZPlayer; // clean up
	return ret;
}




// update some EZPlayer fields below...




// we need to use custom values for more accurate player pos deltas
// the client won't always send movement packets at the exact start of the tick due to latency
// this makes getting the single-tick pos delta really difficult if we only relied on client values
// in summary, mRawPosOld/mRawPos are synced with the start and the end of the ServerPlayer tick, and this->getPos()/this->getPosOld()
// are synced with when the client sends the movement packet

// keep track of previous and current health/absorption
// getHealthAsInt() and getAbsorptionAsInt() exist for the current values

// reset the liquid bucket pickup conditions for InventoryTransactionFix
TInstanceHook(void, "?normalTick@ServerPlayer@@UEAAXXZ", ServerPlayer) {
	
	this->mEZPlayer->mRawPosOld = this->getPos();
	original(this);
	this->mEZPlayer->mRawPos = this->getPos();

	this->mEZPlayer->mHealthOld = this->getHealthAsInt();
	this->mEZPlayer->mAbsorptionOld = this->getAbsorptionAsInt();

	if (this->mEZPlayer->mShouldCancelBucketPickup && this->mOnGround) {
		this->mEZPlayer->mShouldCancelBucketPickup = false;
	}
}