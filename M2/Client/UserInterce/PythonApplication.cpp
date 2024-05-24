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

---

Search:
	CGrannyMaterial::CreateSphereMap(1, "d:/ymir work/special/spheremap01.jpg");

Add below:
#ifdef ENABLE_NOMERCY_ANTICHEAT
	CNoMercy::Instance().SendDataToNoMercy(NoMercy::NM_SIGNAL, (void*)NoMercy::NM_SIG_GAME_INIT);
#endif