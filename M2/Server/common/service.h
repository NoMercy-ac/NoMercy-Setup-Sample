Add:

#define ENABLE_NOMERCY_SERVER
#ifdef ENABLE_NOMERCY_SERVER
// Rest API based heartbeat check
#define NOMERCY_HEARTBEAT_CHECK
#define NOMERCY_HEARTBEAT_CHECK_INTERVAL 60 // in seconds
#define NOMERCY_HEARTBEAT_CHECK_INITIAL_DELAY 30 // in seconds

// Rest API based heartbeat check license info
#define NOMERCY_LICENSE_ID "..." // **CHANGE THIS TO YOUR LICENSE ID**
#define NOMERCY_GAME_ID 2
#define NOMERCY_API_KEY "..." // **CHANGE THIS TO YOUR API KEY**

// ----------------------------------------------------------------

// Game network based heartbeat check, **Enable only one of them(V1/V2)**
// #define NOMERCY_GAME_HEARTBEAT_CHECK_V1 // Raw data exchange based heartbeat check
#ifdef NOMERCY_GAME_HEARTBEAT_CHECK_V1
// #define NOMERCY_GAME_HEARTBEAT_CHECK_V1_EXTRA_SECURITY // Extra security for incoming data, it's requires xxHash library, See: https://github.com/Cyan4973/xxHash
#define NOMERCY_GAME_HEARTBEAT_CHECK_V1_EXTRA_SECURITY_SEED 0x6A09E667 // xxHash seed for NOMERCY_GAME_HEARTBEAT_CHECK_V1_EXTRA_SECURITY
#endif
// #define NOMERCY_GAME_HEARTBEAT_CHECK_V2 // RSA (PEM) encrypted data exchange based heartbeat check
// NOTE: NOMERCY_GAME_HEARTBEAT_CHECK_V2 requires Crypto++ library with PEM support, See: https://github.com/noloader/cryptopp-pem
#ifdef NOMERCY_GAME_HEARTBEAT_CHECK_V2
// Game network based heartbeat check RSA private key file
#define NOMERCY_RSA_PRIV_KEY_FILENAME "NoMercy_heartbeat_priv.key"
#endif

#define NOMERCY_GAME_HEARTBEAT_CHECK_INTERVAL 60 // in seconds
#endif

