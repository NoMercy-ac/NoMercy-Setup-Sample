#include "StdAfx.h"
#include "PythonNetworkStream.h"
#ifdef ENABLE_NOMERCY_ETERPACK_CHECK
#include "../EterPack/EterPackManager.h"
#endif
#include "PythonPlayer.h"
#include "NoMercyClient.h"
#include "PythonApplication.h"
#include <atomic>

#ifdef ENABLE_NOMERCY_ANTICHEAT

#pragma comment(linker, "/ALIGN:0x10000")

//#ifdef _DEBUG
//	#pragma comment( lib, "NoMercy_Module_x86_d.lib" )
//#else
	#pragma comment( lib, "NoMercy_Module_x86.lib" )
//#endif

using namespace NoMercy;

// Client function wrappers
static bool __cdecl SendWrapper(const char* c_pData, int iLength)
{
	if (!CPythonNetworkStream::InstancePtr())
		return false;
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	return rkNetStream.Send(iLength, c_pData);
}

static DWORD __cdecl GetVID()
{
	if (!CPythonNetworkStream::InstancePtr())
		return 0;
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	return rkNetStream.GetMainActorVID();
}

static DWORD __cdecl GetPhase()
{
	if (!CPythonNetworkStream::InstancePtr())
		return -1;

	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	const std::string stPhase = rkNetStream.GetPhaseString();

	if (stPhase == "OffLine")
		return 1;
	else if (stPhase == "Login")
		return 2;
	else if (stPhase == "HandShake")
		return 3;
	else if (stPhase == "Select")
		return 4;
	else if (stPhase == "Loading")
		return 5;
	else if (stPhase == "Game")
		return 6;
	else
		return 0;
}

static const char* __cdecl GetPlayerName()
{
	if (!CPythonPlayer::InstancePtr())
		return "";
	return CPythonPlayer::Instance().GetName();
}

static bool __cdecl IsMappedFileExist(const char* c_szFileName)
{
#ifdef ENABLE_NOMERCY_ETERPACK_CHECK
	return CEterPackManager::Instance().isExist(c_szFileName);
#else
	return false;
#endif
}

static DWORD __cdecl GetMappedFileHash(const char* c_szFileName)
{
#ifdef ENABLE_NOMERCY_ETERPACK_CHECK
	CMappedFile file;
	const void* pData = NULL;

	if (CEterPackManager::Instance().GetFromPack(file, c_szFileName, &pData))
		return GetCRC32((const char*)pData, file.Size());

	return -1;
#else
	return -2;
#endif
}

static bool __cdecl SendSequenceFunc()
{
#ifdef ENABLE_NOMERCY_USE_PACKET_SEQUENCE
	CPythonNetworkStream& rkNetStream = CPythonNetworkStream::Instance();
	return rkNetStream.SendSequence();
#else
	return true;
#endif
}

static std::atomic_bool gs_abGameStarted = false;

// NoMercy message handler
void __stdcall OnNoMercyMessage(int Code, const char* c_szMessage, const void* lpParam)
{
#ifdef _DEBUG
	TraceError("[NoMercy] %u (%s)", Code, c_szMessage);
#endif

	if (Code == NM_DATA_RECV_TICK_RESPONSE)
	{
		CNoMercy::Instance().SetNoMercyMessageHandled();
	}
	else if (Code == NM_DATA_RECV_SESSION_ID && lpParam)
	{
		const SSessionIDCtx* c_pSIDctx = (const SSessionIDCtx*)lpParam;
		CPythonApplication::Instance().SetNoMercySID(c_pSIDctx->szSessionID);
	}
	else if (Code == NM_SIGNAL && c_szMessage && *c_szMessage)
	{
		const auto c_ulMessage = std::strtoul(c_szMessage, nullptr, 10);
		if (c_ulMessage == NM_GAME_STARTED)
		{
			gs_abGameStarted = true;

			CNoMercy::Instance().SendDataToNoMercy(NoMercy::NM_SIGNAL, (void*)NoMercy::NM_SIG_GAME_INIT);
			CNoMercy::Instance().SendClientFunctionsToNoMercy();
		}
	}
}

// NoMercy Functions
bool CNoMercy::InitializeNoMercy()
{
	if (NM_Initialize(NOMERCY_GAME_CODE, NOMERCY_MAJOR_VERSION, &OnNoMercyMessage))
	{
		TraceError("NoMercy Initilization fail! Error code: %u", GetLastError());
		return false;
	}
	return true;
}

void CNoMercy::FinalizeNoMercy()
{
	NM_Finalize();
}

void CNoMercy::SendDataToNoMercy(uint32_t Code, const void* lpMessage)
{
	if (!gs_abGameStarted.load())
	{
		TraceError("Game not started yet! Requested message: %u(%p) is ignored.", Code, lpMessage);
		return;
	}

	NM_ForwardMessage(Code, lpMessage);
}

void CNoMercy::OnGameTick()
{
	if (!gs_abGameStarted.load())
		return;

	static DWORD s_dwLastTick = 0;
	DWORD dwCurrentTick = GetTickCount();

	if (dwCurrentTick - s_dwLastTick >= NOMERCY_TICK_INTERVAL)
	{
		SendDataToNoMercy(NM_SIGNAL, (void*)NM_SIG_GAME_POLL_EVENT);

		s_dwLastTick = dwCurrentTick;
	}
}

void CNoMercy::SendClientFunctionsToNoMercy()
{
	SendDataToNoMercy(NM_DATA_SEND_TRACEERROR, TraceError);
	SendDataToNoMercy(NM_DATA_SEND_NET_SEND_PACKET, SendWrapper);
	SendDataToNoMercy(NM_DATA_SEND_VID, GetVID);
	SendDataToNoMercy(NM_DATA_SEND_PHASE, GetPhase);
	SendDataToNoMercy(NM_DATA_SEND_PLAYER_NAME, GetPlayerName);
	SendDataToNoMercy(NM_DATA_SEND_MAPPED_FILE_HASH, GetMappedFileHash);
	SendDataToNoMercy(NM_DATA_SEND_NET_SEND_SEQ, SendSequenceFunc);
	SendDataToNoMercy(NM_SIGNAL, (void*)NM_SIG_POINTER_REDIRECTION_COMPLETED);
}
#endif
