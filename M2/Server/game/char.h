Search:
#include "mining.h"

Add below:
#if defined(NOMERCY_GAME_HEARTBEAT_CHECK_V1) || defined(NOMERCY_GAME_HEARTBEAT_CHECK_V2)
#include "NoMercyRandom.h"
#endif

---

Search:
		void			Disconnect(const char * c_pszReason);

Add below:
#if defined(NOMERCY_GAME_HEARTBEAT_CHECK_V1) || defined(NOMERCY_GAME_HEARTBEAT_CHECK_V2)
public:
		void		SetNoMercyHbValueGen(CMTRandom* ptr) { m_nomercy_hb_value_gen = ptr; }
		CMTRandom* GetNoMercyHbValueGen() { return m_nomercy_hb_value_gen; }

		void		SetNoMercyHbEvent(LPEVENT ptr) { m_nomercy_hb_event = ptr; }
		LPEVENT		GetNoMercyHbEvent() { return m_nomercy_hb_event; }

	private:
		CMTRandom* m_nomercy_hb_value_gen;
		LPEVENT    m_nomercy_hb_event;
#endif
