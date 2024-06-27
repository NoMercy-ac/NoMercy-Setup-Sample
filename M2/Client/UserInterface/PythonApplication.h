Search:
		void SetForceSightRange(int iRange);

Add below:
#if defined(ENABLE_NOMERCY_ANTICHEAT) && defined(ENABLE_NOMERCY_PREMIUM_PLAN)
		void SetNoMercySID(const char* c_szNoMercySID) { m_strNoMercySID = c_szNoMercySID; }
		std::string GetNoMercySID() { return m_strNoMercySID; }
#endif

---

Search:
		DWORD						m_dwHeight;

Add below:
#if defined(ENABLE_NOMERCY_ANTICHEAT) && defined(ENABLE_NOMERCY_PREMIUM_PLAN)
		std::string					m_strNoMercySID;
#endif