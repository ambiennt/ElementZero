#include "include/base/ezplayer.h"
#include <Actor/Player.h>

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
	delete player->mEZPlayer; // clean up to be safe because idk what BDS does with this field
	player->mEZPlayer = nullptr;
	return ret;
}