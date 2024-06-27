Search:
#include "AccountConnector.h"

Add below:
#include "PythonApplication.h"
#include "NoMercyClient.h"

---

Search: (CPythonNetworkStream::SendLoginPacket)
	if (!Send(sizeof(LoginPacket), &LoginPacket))
	{
		Tracen("SendLogin Error");
		return false;
	}

Add below:
#ifdef ENABLE_NOMERCY_ANTICHEAT
	CNoMercy::Instance().OnGameTick();
#endif

---

Search: (CPythonNetworkStream::SendLoginPacketNew)
	for (DWORD i = 0; i < 4; ++i)
		LoginPacket.adwClientKey[i] = g_adwEncryptKey[i];

Add below:
#if defined(ENABLE_NOMERCY_ANTICHEAT) && defined(ENABLE_NOMERCY_PREMIUM_PLAN)
	const std::string strNoMercySID = CPythonApplication::Instance().GetNoMercySID();
	if (strNoMercySID.empty())
	{
		TraceError("NoMercy is not initialized!");
		return false;
	}
	strncpy(LoginPacket.szNoMercySID, strNoMercySID.c_str(), sizeof(LoginPacket.szNoMercySID) - 1);
	LoginPacket.szNoMercySID[sizeof(LoginPacket.szNoMercySID) - 1] = '\0';
#endif

---

Search: (CPythonNetworkStream::SendLoginPacketNew)
#ifndef _IMPROVED_PACKET_ENCRYPTION_
	SetSecurityMode(true, (const char *) g_adwEncryptKey, (const char *) g_adwDecryptKey);
#endif

Add below:
#ifdef ENABLE_NOMERCY_ANTICHEAT
	CNoMercy::Instance().OnGameTick();
#endif
