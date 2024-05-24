#pragma once
#include "Locale.h"

#ifdef ENABLE_NOMERCY_ANTICHEAT
#include <NoMercy.h>

#define NOMERCY_GAME_CODE 2
#define NOMERCY_MAJOR_VERSION 1

class CNoMercy : public CSingleton <CNoMercy>
{
public:
	CNoMercy() = default;
	virtual ~CNoMercy() = default;

	bool InitializeNoMercy();
	void FinalizeNoMercy();

	void OnGameTick();

	void SendDataToNoMercy(uint32_t Code, const void* lpMessage);
	void SendClientFunctionsToNoMercy();
	
	bool NoMercyMessageHandled() const { return m_bNoMercyTickMsgHandled; };
	void SetNoMercyMessageHandled() { m_bNoMercyTickMsgHandled = true; };

private:
	bool m_bNoMercyTickMsgHandled;
};
#endif
