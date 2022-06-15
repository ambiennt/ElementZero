#include <dllentry.h>
#include <hook.h>
#include <base/log.h>

DEF_LOGGER("NoEncryption");

void dllenter() {}
void dllexit() {}

THook(void**,
	"?getEncryptedPeerForUser@NetworkHandler@@QEAA?AV?$weak_ptr@VEncryptedNetworkPeer@@@std@@AEBVNetworkIdentifier@@@Z",
	void *self, void **ret, void *netId) {
	ret[0] = nullptr;
	ret[1] = nullptr;
	return ret;
}