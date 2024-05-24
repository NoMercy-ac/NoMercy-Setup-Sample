#include "stdafx.h"
#include "NoMercyRSA.h"

#ifdef NOMERCY_GAME_HEARTBEAT_CHECK_V2
#include <cryptopp/integer.h>
#include <cryptopp/rsa.h>
#include <cryptopp/pem.h>
#include <cryptopp/osrng.h>

CRSALoader::CRSALoader()
{
}
CRSALoader::~CRSALoader()
{
}

bool CRSALoader::IsNumberString(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !isdigit(c); }) == s.end();
}

bool CRSALoader::DecryptHeartbeatValue(const std::string& stEncodedValue, DWORD& dwDecodedValue)
{
	if (!m_upRsaPrivateKey || !m_upRsaPrivateKey.get())
	{
		sys_err("RSA key ptr not valid");
		return false;
	}

	CryptoPP::Integer c;
	try
	{
		c = CryptoPP::Integer(stEncodedValue.c_str());
	}
	catch (const CryptoPP::Exception& ex)
	{
		sys_err("Heartbeat message: %s (%u) decode fail! Error: %s", stEncodedValue.c_str(), stEncodedValue.size(), ex.what());
		return false;
	}

	// Decrypt
	std::string recovered;

	try
	{
		CryptoPP::AutoSeededRandomPool  prng;
		CryptoPP::Integer r = m_upRsaPrivateKey->CalculateInverse(prng, c);

		size_t req = r.MinEncodedSize();

		recovered.resize(req);

		r.Encode((CryptoPP::byte*)recovered.data(), recovered.size());
	}
	catch (const CryptoPP::Exception& ex)
	{
		sys_err("Heartbeat message: %s (%u) decryption fail! Error: %s", stEncodedValue.c_str(), stEncodedValue.size(), ex.what());
		return false;
	}

	if (!IsNumberString(recovered))
	{
		sys_err("Decoded message: %s is not number", recovered.c_str());
		return false;
	}

	dwDecodedValue = strtoul(recovered.c_str(), NULL, 10);
	return true;
}

bool CRSALoader::LoadPrivateKey(const std::string& data)
{
	m_upRsaPrivateKey = std::make_unique<CryptoPP::RSA::PrivateKey>();
	
	try
	{		
		CryptoPP::StringSource source(data, true);
		CryptoPP::PEM_Load(source, *m_upRsaPrivateKey.get());
	}
	catch (const CryptoPP::Exception& ex)
	{
		sys_err("PEM could not load, Error: %s", ex.what());
		return false;
	}

	CryptoPP::AutoSeededRandomPool rnd;
	if (!m_upRsaPrivateKey->Validate(rnd, 3))
	{
		sys_err("RSA key is not valid");
		return false;
	}

	return true;
}

bool CRSALoader::LoadPrivateKeyFromFile(const std::string& stFileName)
{
	FILE* fp = fopen(stFileName.c_str(), "r");
	if (!fp)
	{
		sys_err("RSA private key file: %s open fail!", stFileName.c_str());
		return false;
	}

	long pos = ftell(fp);
	fseek(fp, 0, SEEK_END);
	long filesize = ftell(fp);
	fseek(fp, pos, SEEK_SET);

	std::vector <char> buf(filesize);
	fread(buf.data(), 1, buf.size(), fp);

	std::string data = std::string(buf.begin(), buf.end());
	if (data.empty())
	{
		sys_err("RSA private key file: %s is empty!", stFileName.c_str());
		fclose(fp);
		return false;
	}

	sys_log(2, "RSA private key loaded! Data: %s\n", data.c_str());

	fclose(fp);
	return LoadPrivateKey(data);
}
#endif
