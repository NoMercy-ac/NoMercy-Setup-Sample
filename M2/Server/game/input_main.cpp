Search:
#include "DragonSoul.h"

Add below:
#if defined(NOMERCY_GAME_HEARTBEAT_CHECK_V2)
#include "NoMercyRSA.h"
#endif
#if defined(NOMERCY_GAME_HEARTBEAT_CHECK_V1_EXTRA_SECURITY)
#include <xxhash.h>
#endif

---

Search:
size_t GetSubPacketSize(const GUILD_SUBHEADER_CG& header)

Add above:
#if defined(NOMERCY_GAME_HEARTBEAT_CHECK_V1) || defined(NOMERCY_GAME_HEARTBEAT_CHECK_V2)
void CInputMain::RecvNoMercyHeartBeatV1(LPDESC d, const char* data)
{
	SPacketCGNoMercyHeartbeatV1* p = (SPacketCGNoMercyHeartbeatV1*)data;
	if (!p)
		return;

	LPCHARACTER ch = d->GetCharacter();
	if (!ch)
		return;

	CMTRandom* nm_hb_v1_val_gen = ch->GetNoMercyHbValueGen();
	if (!nm_hb_v1_val_gen)
	{
		ch->Disconnect("NM_HB_V1_NO_VAL_GEN");
		return;
	}

	LPEVENT nm_hb_v1_event = ch->GetNoMercyHbEvent();
	if (!nm_hb_v1_event)
	{
		ch->Disconnect("NM_HB_V1_NO_EVENT");
		return;
	}

	DWORD correct_key = nm_hb_v1_val_gen->next();
	sys_log(0, "v1 val_gen: %p correct key: %lu current key: %lu", nm_hb_v1_val_gen, correct_key, p->dwHBKey);

	nomercy_hb_event_info* event_info = dynamic_cast<nomercy_hb_event_info*>(nm_hb_v1_event->info);
	if (!event_info)
	{
		ch->Disconnect("NM_HB_V1_NULL_INFO");
		return;
	}

	if (correct_key != p->dwHBKey)
	{
		sys_err("NM_HB_V1: NoMercy heartbeat key mismatch. Player: %u (%s)", ch->GetPlayerID(), ch->GetName());
		ch->ChatPacket(CHAT_TYPE_COMMAND, "nm_sv_hb_chk");
		ch->GetDesc()->DelayedDisconnect(5);
	}
#ifdef NOMERCY_GAME_HEARTBEAT_CHECK_V1_EXTRA_SECURITY
	if (!p->qwHBKeyHash || XXH64((void*)p->dwHBKey, sizeof(p->dwHBKey), NOMERCY_GAME_HEARTBEAT_CHECK_V1_EXTRA_SECURITY_SEED) != p->qwHBKeyHash)
	{
		sys_err("NM_HB_V1: NoMercy heartbeat key hash mismatch. Player: %u (%s)", ch->GetPlayerID(), ch->GetName());
		ch->Disconnect("NM_HB_V1_KEY_HASH_MISMATCH");
		return;
	}
#endif
	else
	{
		if (test_server)
			sys_log(0, "NM_HB_V1: all conditions are passed, last check: %llu", event_info->LastPulse);
		event_info->LastPulse = get_global_time();
	}
}

void CInputMain::RecvNoMercyHeartBeatV2(LPDESC d, const char* data)
{
#ifdef NOMERCY_GAME_HEARTBEAT_CHECK_V2
	SPacketCGNoMercyHeartbeatV2* p = (SPacketCGNoMercyHeartbeatV2*)data;
	if (!p)
		return;

	LPCHARACTER ch = d->GetCharacter();
	if (!ch)
		return;

	CMTRandom* nm_hb_val_gen = ch->GetNoMercyHbValueGen();
	if (!nm_hb_val_gen)
	{
		ch->Disconnect("NM_HB_V2_NO_VAL_GEN");
		return;
	}

	LPEVENT nm_hb_event = ch->GetNoMercyHbEvent();
	if (!nm_hb_event)
	{
		ch->Disconnect("NM_HB_V2_NO_EVENT");
		return;
	}

	DWORD dwDecodedKey = 0;
	if (!CRSALoader::Instance().DecryptHeartbeatValue(p->key, dwDecodedKey))
	{
		ch->Disconnect("NM_HB_V2_DECRYPT_FAIL");
		return;
	}

	DWORD correct_key = nm_hb_val_gen->next();
	sys_log(0, "v2 val_gen: %p vid: %lu correct key: %lu current key: %lu", nm_hb_val_gen, (DWORD)ch->GetVID(), correct_key, dwDecodedKey);

	nomercy_hb_event_info* event_info = dynamic_cast<nomercy_hb_event_info*>(nm_hb_event->info);
	if (!event_info)
	{
		ch->Disconnect("NM_HB_V2_NULL_INFO");
		return;
	}

	sys_log(0, "event pulse: %lld passed: %lu", event_info->LastPulse, event_info->Passed);

	if (correct_key != dwDecodedKey)
	{
		sys_err("NM_HB_V2: NoMercy heartbeat key mismatch. Player: %u (%s)", ch->GetPlayerID(), ch->GetName());
		ch->ChatPacket(CHAT_TYPE_COMMAND, "nm_sv_hb_chk");
		ch->GetDesc()->DelayedDisconnect(5);
	}
	else
	{
		if (test_server)
			sys_log(0, "NM_HB_V2: all conditions are passed, last check: %llu", event_info->LastPulse);
		event_info->LastPulse = get_global_time();
	}
#endif
}
#endif

---

Search:
        case HEADER_CG_CLIENT_VERSION:
			Version(ch, c_pData);
			break;

Add below:
#if defined(NOMERCY_GAME_HEARTBEAT_CHECK_V1) || defined(NOMERCY_GAME_HEARTBEAT_CHECK_V2)
		case HEADER_CG_NM_HB_V1:
			RecvNoMercyHeartBeatV1(d, c_pData);
			break;

		case HEADER_CG_NM_HB_V2:
			RecvNoMercyHeartBeatV2(d, c_pData);
			break;
#endif
