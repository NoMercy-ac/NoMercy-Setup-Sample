Search:
		void SetForceSightRange(int iRange);

Add below:
#ifdef ENABLE_NOMERCY_ANTICHEAT
		void SetNoMercySID(const char* c_szNoMercySID) { m_strNoMercySID = c_szNoMercySID; }
		std::string GetNoMercySID() { return m_strNoMercySID; }
#endif

---

Search:
		DWORD						m_dwHeight;

Add below:
#ifdef ENABLE_NOMERCY_ANTICHEAT
		std::string					m_strNoMercySID;
#endif