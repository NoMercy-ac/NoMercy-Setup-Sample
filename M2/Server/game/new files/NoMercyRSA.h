#pragma once
#include "../../common/service.h"

#ifdef NOMERCY_GAME_HEARTBEAT_CHECK_V2
#include <cryptopp/rsa.h>

class CRSALoader : public singleton <CRSALoader>
{
public:
	CRSALoader();
	virtual ~CRSALoader();

	bool LoadPrivateKey(const std::string& data);
	bool LoadPrivateKeyFromFile(const std::string& stFileName);

	bool DecryptHeartbeatValue(const std::string& stEncodedValue, DWORD& dwDecodedValue);

protected:
	bool IsNumberString(const std::string& s);

private:
	std::unique_ptr <CryptoPP::RSA::PrivateKey> m_upRsaPrivateKey;
};
#endif
