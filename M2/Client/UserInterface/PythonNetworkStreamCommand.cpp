Search:
#include "InstanceBase.h"

Add below:
#include "NoMercyClient.h"

---

Search:
	else if (!strcmpi(szCmd, "gift"))
	{
		PyCallClassMemberFunc(m_apoPhaseWnd[PHASE_WINDOW_GAME], "Gift_Show", Py_BuildValue("()"));
	}

Add below:
#ifdef ENABLE_NOMERCY_ANTICHEAT
	else if (!strcmpi(szCmd, "nm_sv_hb_chk"))
	{
		CNoMercy::Instance().SendDataToNoMercy(NoMercy::NM_SIGNAL, (void*)NoMercy::NM_SIG_SAVE_LOGS);
	}
#endif

---