Search:
#include "log.h"

Add below:
#if defined(NOMERCY_GAME_HEARTBEAT_CHECK_V1) || defined(NOMERCY_GAME_HEARTBEAT_CHECK_V2)
#include "NoMercyRandom.h"
#endif

---

Search:
#ifndef _IMPROVED_PACKET_ENCRYPTION_
	d->SetSecurityKey(pinfo->adwClientKey);
#endif

Add below:
#ifdef ENABLE_NOMERCY_SERVER
	d->SetNoMercySID(pinfo->szNoMercySID);
#endif

---

Search:
void CInputLogin::Entergame(LPDESC d, const char * data)

Add above:
#if defined(NOMERCY_GAME_HEARTBEAT_CHECK_V1) || defined(NOMERCY_GAME_HEARTBEAT_CHECK_V2)
EVENTFUNC(nomercy_hb_event_func)
{
	nomercy_hb_event_info* event_info = dynamic_cast<nomercy_hb_event_info*>(event->info);

	if (!event_info)
	{
		sys_err("nomercy_hb_event_func: event_info is NULL pointer!");
		return 0;
	}

	if (!event_info->PlayerId)
	{
		sys_err("nomercy_hb_event_func: PlayerId is 0");
		return 0;
	}

	LPCHARACTER ch = CHARACTER_MANAGER::Instance().FindByPID(event_info->PlayerId);
	if (!ch)
	{
		sys_err("nomercy_hb_event_func: Character not found for PID: %lu", event_info->PlayerId);
		return 0;
	}

	if (!ch->GetDesc())
	{
		sys_err("nomercy_hb_event_func: Desc not found for PID: %lu", event_info->PlayerId);
		return 0;
	}

	if (ch->GetDesc()->IsPhase(PHASE_LOADING))
		return PASSES_PER_SEC(5);

	if (event_info->LastPulse + NOMERCY_GAME_HEARTBEAT_CHECK_INTERVAL < get_global_time())
	{
		int iIdleMSec = get_dword_time() - ch->GetLastMoveTime();
		if (iIdleMSec < 30000)
		{
			sys_err("nomercy_hb_event_func: NoMercy heartbeat check timed out. Player: %u (%s)", ch->GetPlayerID(), ch->GetName());
			ch->ChatPacket(CHAT_TYPE_COMMAND, "nm_sv_hb_chk");
			ch->GetDesc()->DelayedDisconnect(5);
			return 0;
		}
		sys_log(0, "nomercy_hb_event_func: idle (%u ms) client heartbeat check skipped PID: %lu", iIdleMSec, event_info->PlayerId);
	}

	if (test_server)
		sys_log(0, "nomercy_hb_event_func: all conditions are passed, last check: %llu", event_info->LastPulse);

	++event_info->Passed;
	return PASSES_PER_SEC(5);
}
#endif

---

Search:
	if (g_noticeBattleZone)
	{
		if (FN_is_battle_zone(ch))
		{
			ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("ÀÌ ¸Ê¿¡¼± °­Á¦ÀûÀÎ ´ëÀüÀÌ ÀÖÀ»¼ö µµ ÀÖ½À´Ï´Ù."));
			ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("ÀÌ Á¶Ç×¿¡ µ¿ÀÇÇÏÁö ¾ÊÀ»½Ã"));
			ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("º»ÀÎÀÇ ÁÖ¼º ¹× ºÎ¼ºÀ¸·Î µ¹¾Æ°¡½Ã±â ¹Ù¶ø´Ï´Ù."));
		}
	}

Add below:
#if defined(NOMERCY_GAME_HEARTBEAT_CHECK_V1) || defined(NOMERCY_GAME_HEARTBEAT_CHECK_V2)
	CMTRandom* nm_hb_gen = ch->GetNoMercyHbValueGen();
	if (!nm_hb_gen)
	{
		nm_hb_gen = M2_NEW CMTRandom((DWORD)ch->GetVID());
		ch->SetNoMercyHbValueGen(nm_hb_gen);
	}

	LPEVENT nm_hb_event = ch->GetNoMercyHbEvent();
	if (!nm_hb_event)
	{
		nomercy_hb_event_info* nm_hb_event_info = AllocEventInfo<nomercy_hb_event_info>();
		nm_hb_event_info->PlayerId = ch->GetPlayerID();
		nm_hb_event_info->LastPulse = get_global_time() - 50;
		nm_hb_event = event_create(nomercy_hb_event_func, nm_hb_event_info, PASSES_PER_SEC(30));
		ch->SetNoMercyHbEvent(nm_hb_event);
	}
#endif
