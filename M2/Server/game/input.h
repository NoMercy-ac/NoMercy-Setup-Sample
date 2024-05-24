Search:
void LoginFailure(LPDESC d, const char * c_pszStatus);

Add above:
#if defined(NOMERCY_GAME_HEARTBEAT_CHECK_V1) || defined(NOMERCY_GAME_HEARTBEAT_CHECK_V2)
EVENTINFO(nomercy_hb_event_info)
{
	DWORD PlayerId;
	time_t LastPulse;
	DWORD Passed;

	nomercy_hb_event_info()
	{
		PlayerId = 0;
		LastPulse = 0;
		Passed = 0;
	}
};
#endif

---

Search:
        void		PartyParameter(LPCHARACTER ch, const char * c_pData);

Add below:
#if defined(NOMERCY_GAME_HEARTBEAT_CHECK_V1) || defined(NOMERCY_GAME_HEARTBEAT_CHECK_V2)
		void		RecvNoMercyHeartBeatV1(LPDESC d, const char* data);
		void		RecvNoMercyHeartBeatV2(LPDESC d, const char* data);
#endif
