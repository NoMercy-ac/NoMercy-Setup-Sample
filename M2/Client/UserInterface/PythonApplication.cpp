Search:
#include "CheckLatestFiles.h"

Add below:
#include "NoMercyClient.h"

---

Search:
		s_uiLoad = s_dwFaceCount = s_dwUpdateFrameCount = s_dwRenderFrameCount = 0;

Add below:
#ifdef ENABLE_NOMERCY_ANTICHEAT
		CNoMercy::Instance().OnGameTick();
#endif
