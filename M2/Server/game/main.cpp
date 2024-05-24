Search:
#include "skill_power.h"

Add below:
#include "NoMercyServer.h"
#ifdef NOMERCY_GAME_HEARTBEAT_CHECK_V2
#include "NoMercyRSA.h"
#endif

---

Search:
DSManager dsManager;

Add below:
#ifdef ENABLE_NOMERCY_SERVER
	CNoMercyServer noMercyServer;
#endif
#ifdef NOMERCY_GAME_HEARTBEAT_CHECK_V2
	CRSALoader rsa;
#endif

---

Search:
  	if (!start(argc, argv)) {
		CleanUpForEarlyExit();
		return 0;
	}

Add below:
#ifdef ENABLE_NOMERCY_SERVER
	if (!CNoMercyServer::Instance().Initialize(NOMERCY_LICENSE_ID, NOMERCY_GAME_ID, NOMERCY_API_KEY))
	{
		CleanUpForEarlyExit();
		return 0;
	}
#endif

#ifdef NOMERCY_GAME_HEARTBEAT_CHECK_V2
	if (!CRSALoader::Instance().LoadPrivateKeyFromFile(NOMERCY_RSA_PRIV_KEY_FILENAME))
	{
		sys_err("LoadPrivateKeyFromFile (%s) failed", NOMERCY_RSA_PRIV_KEY_FILENAME);
		return 0;
	}
#endif