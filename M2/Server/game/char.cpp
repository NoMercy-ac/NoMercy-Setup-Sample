Search:
	m_pkMobInst		= NULL;

Add below:
#if defined(NOMERCY_GAME_HEARTBEAT_CHECK_V1) || defined(NOMERCY_GAME_HEARTBEAT_CHECK_V2)
	m_nomercy_hb_value_gen = NULL;
	m_nomercy_hb_event = NULL;
#endif

---

Search:
	if (GetRider())
		GetRider()->ClearHorseInfo();

Add below:
#if defined(NOMERCY_GAME_HEARTBEAT_CHECK_V1) || defined(NOMERCY_GAME_HEARTBEAT_CHECK_V2)
	if (m_nomercy_hb_event)
	{
		event_cancel(&m_nomercy_hb_event);
		m_nomercy_hb_event = NULL;
	}

	if (m_nomercy_hb_value_gen)
	{
		M2_DELETE(m_nomercy_hb_value_gen);
		m_nomercy_hb_value_gen = NULL;
	}
#endif