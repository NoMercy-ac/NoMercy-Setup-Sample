Search:
        DWORD			GetLoginKey();

Add below:
#if defined(ENABLE_NOMERCY_ANTICHEAT) && defined(ENABLE_NOMERCY_PREMIUM_PLAN)
		void			SetNoMercySID(const char* c_pszSID);
		const char*		GetNoMercySID() const;
#endif

---

Search:
		DWORD			m_dwPanamaKey;

Add below:
#if defined(ENABLE_NOMERCY_ANTICHEAT) && defined(ENABLE_NOMERCY_PREMIUM_PLAN)
		std::string		m_stNoMercySID;
#endif
