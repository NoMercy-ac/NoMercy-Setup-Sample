Search:
	Set(HEADER_CG_WHISPER, sizeof(TPacketCGWhisper), "Whisper", true);

Add below:
#if defined(NOMERCY_GAME_HEARTBEAT_CHECK_V1) || defined(NOMERCY_GAME_HEARTBEAT_CHECK_V2)
	Set(HEADER_CG_NM_HB_V1, sizeof(SPacketCGNoMercyHeartbeatV1), "NoMercyHbV1", false);
	Set(HEADER_CG_NM_HB_V2, sizeof(SPacketCGNoMercyHeartbeatV2), "NoMercyHbV2", false);
#endif