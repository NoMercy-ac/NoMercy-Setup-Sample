Search:
#include "shutdown_manager.h"

Add below:
#include "NoMercyServer.h"

---

Search:
		m_lpCharacter->Disconnect("DESC::~DESC");

Add above:
#ifdef ENABLE_NOMERCY_SERVER
		CNoMercyServer::instance().OnLogoutPlayer(m_lpCharacter->GetPlayerID());
#endif

---

Search:
void DESC::BindCharacter(LPCHARACTER ch)
{
	m_lpCharacter = ch;

Add below:
#ifdef ENABLE_NOMERCY_SERVER
	CNoMercyServer::instance().OnLoginPlayer(ch->GetPlayerID());
#endif

---

Search:
DWORD DESC::GetLoginKey()
{
	if (m_pkLoginKey)
		return m_pkLoginKey->m_dwKey;

	return m_dwLoginKey;
}

Add below:
#ifdef ENABLE_NOMERCY_SERVER
void DESC::SetNoMercySID(const char* c_pszSID)
{
	m_stNoMercySID = c_pszSID;
}

const char* DESC::GetNoMercySID() const
{
	return m_stNoMercySID.c_str();
}
#endif