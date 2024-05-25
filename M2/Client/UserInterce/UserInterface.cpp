Search:
#include "CheckLatestFiles.h"

Add below:
#include "NoMercyClient.h"

---

Search:
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

Add below:
#ifdef ENABLE_NOMERCY_ANTICHEAT
	static CNoMercy s_kNoMercyInstance;
	if (CNoMercy::Instance().InitializeNoMercy())
		return EXIT_FAILURE;
#endif

---

Search:
	Main(hInstance, lpCmdLine);

Add below:
#ifdef ENABLE_NOMERCY_ANTICHEAT
	CNoMercy::Instance().FinalizeNoMercy();
#endif
