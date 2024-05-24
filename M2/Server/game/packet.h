Search:
HEADER_CG_STATE_CHECKER			= 206,

Add below:
#if defined(NOMERCY_GAME_HEARTBEAT_CHECK_V1) || defined(NOMERCY_GAME_HEARTBEAT_CHECK_V2)
	HEADER_CG_NM_HB_V1 = 221, // DO NOT CHANGE THIS VALUE, IF IT'S USED BY ANOTHER PACKET HEADER CHABGE IT IN THE OTHER HEADER
	HEADER_CG_NM_HB_V2 = 222, // DO NOT CHANGE THIS VALUE, IF IT'S USED BY ANOTHER PACKET HEADER CHABGE IT IN THE OTHER HEADER
#endif

---

Search:
} TPacketCGHandshake;

Add below:
#if defined(NOMERCY_GAME_HEARTBEAT_CHECK_V1) || defined(NOMERCY_GAME_HEARTBEAT_CHECK_V2)
// NOTE: If you changed the packet alignments, the NoMercy packets must be aligned with 1
struct SPacketCGNoMercyHeartbeatV1
{
	uint8_t header;
	uint32_t dwHBKey;
	uint64_t qwHBKeyHash;
};

struct SPacketCGNoMercyHeartbeatV2
{
	uint8_t header;
	char key[1024];
};
#endif

---

Search: (in TPacketCGLogin2)
    DWORD	adwClientKey[4];

Add below:
	char	szNoMercySID[128 + 1];