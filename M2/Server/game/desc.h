Search:
        DWORD			GetLoginKey();

Add below:
#ifdef ENABLE_NOMERCY_SERVER
		void			SetNoMercySID(const char* c_pszSID);
		const char*		GetNoMercySID() const;
#endif

---

Search:
		DWORD			m_dwPanamaKey;

Add below:
#ifdef ENABLE_NOMERCY_SERVER
		std::string		m_stNoMercySID;
#endif
