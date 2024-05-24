Search:
#include "ProcessCRC.h"

Add below:
#include "NoMercyClient.h"

---

Search: (CPythonNetworkStream::SetGamePhase)
	__RefreshStatus();

Add below:
#ifdef ENABLE_NOMERCY_ANTICHEAT
	if (!CNoMercy::Instance().NoMercyMessageHandled())
	{
		TraceError("NoMercy tick message could not handled!");

		SetOffLinePhase();
		Disconnect();
		return;
	}
    
	CNoMercy::Instance().SendDataToNoMercy(NoMercy::NM_SIGNAL, (void*)NoMercy::NM_SIG_HEARTBEAT_V1_SETUP);
#endif
