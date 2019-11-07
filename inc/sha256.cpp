#include "sha256.h"
#include "openssl/sha.h"

struct MsgBlock
{
    uint32_t words[16];
};

struct SHA256Hash
{
    uint32_t words[8];
};

// Constants used by SHA256 algorithm. These are the fractional parts of the cube roots of the first
// 64 prime numbers.

const uint32_t constants[64] =
{
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// Initial hash value used by SHA256 algorithm.

const uint32_t H0[8] =
{
    0x6a09e667,
    0xbb67ae85,
    0x3c6ef372,
    0xa54ff53a,
    0x510e527f,
    0x9b05688c,
    0x1f83d9ab,
    0x5be0cd19
};

static inline uint32_t rotr32(uint32_t x, uint32_t n) { return (x >> n) | (x << (32 - n)); }
static inline uint32_t ch(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (~x & z);  }
static inline uint32_t maj(uint32_t x, uint32_t y, uint32_t z) { return (x & y) ^ (x & z) ^ (y & z); }
static inline uint32_t bsig0(uint32_t x) { return rotr32(x, 2) ^ rotr32(x, 13) ^ rotr32(x, 22); }
static inline uint32_t bsig1(uint32_t x) { return rotr32(x, 6) ^ rotr32(x, 11) ^ rotr32(x, 25); }
static inline uint32_t ssig0(uint32_t x) { return rotr32(x, 7) ^ rotr32(x, 18) ^ (x >> 3); }
static inline uint32_t ssig1(uint32_t x) { return rotr32(x, 17) ^ rotr32(x, 19) ^ (x >> 10); }

/**
 * PrintBlockedMessage - Given a message padded into 512 bit blocks of 32 bit words each, print
 * the messages blocks/words.
 *
 * @param msgBlocked [in] Input message broken into 512 bit blocks.
 */

static void PrintBlockedMessage(const vector<MsgBlock>& msgBlocked)
{
    for (uint32_t i = 0; i < msgBlocked.size(); i++)
    {
        printf("MsgBlock %d:\n", i);
        for (uint32_t j = 0; j < 16; j++) printf("0x%lx ", msgBlocked[i].words[j]);
    }
}

/**
 * Pad - Given an input message, pad with zeros and append message length in bits such
 * that total message length is a multiple of 512 bits.
 *
 * @param msg [in/out] Message to pad. Message will be modified with appended zeros and message
 * length bytes.
 */

static void Pad(string &msg)
{
    uint64_t l          = (uint64_t)msg.size() * 8;
    uint64_t k          = 512 - ((l + 65LL) % 512);
    uint64_t padBytes   = (k + 1) / 8;

    if (padBytes > 0)
    {
        msg.push_back((char)0x80);
        for (uint64_t i = 0; i < padBytes - 1; i++) msg.push_back((char)0);
        
        msg.push_back((char)(0xFF00000000000000 & l >> 56));
        msg.push_back((char)(0x00FF000000000000 & l >> 48));
        msg.push_back((char)(0x0000FF0000000000 & l >> 40));
        msg.push_back((char)(0x000000FF00000000 & l >> 32));
        msg.push_back((char)(0x00000000FF000000 & l >> 24));
        msg.push_back((char)(0x0000000000FF0000 & l >> 16));
        msg.push_back((char)(0x000000000000FF00 & l >> 8));
        msg.push_back((char)(0x00000000000000FF & l));
    }
    else
    {
        msg.push_back((char)((0x8000000000000000 | l) >> 56));
        msg.push_back((char)(0x00FF000000000000 & l >> 48));
        msg.push_back((char)(0x0000FF0000000000 & l >> 40));
        msg.push_back((char)(0x000000FF00000000 & l >> 32));
        msg.push_back((char)(0x00000000FF000000 & l >> 24));
        msg.push_back((char)(0x0000000000FF0000 & l >> 16));
        msg.push_back((char)(0x000000000000FF00 & l >> 8));
        msg.push_back((char)(0x00000000000000FF & l));
    }

    assert((msg.size() * 8) % 512 == 0);
}

/**
 * ParseBlocks - Given a padded message, parse it into 512 bit blocks of 16 32 bit words.
 *
 * @param msgPadded  [in] Padded message to be parsed.
 * @param msgBlocked [out] Blocked representation of input message broken into 512 bit blocks of 32bit words.
 */

static void ParseBlocks(const vector<uint8_t>& msgPadded, vector<MsgBlock>& msgBlocked)
{
    assert((msgPadded.size() * 8) % 512 == 0);

    const uint64_t numBlocks        = msgPadded.size() * 8 / 512;
    const uint64_t wordsPerBlock    = 16;

    for (uint64_t i = 0; i < numBlocks; i++)
    {
        uint64_t blockOffset = i * 64;
        MsgBlock curBlock;

        for (uint64_t j = 0; j < wordsPerBlock; j++)
        {
            uint32_t curWord = 0;
            uint64_t wordOffset = blockOffset + (j * 4);

            curWord |= (uint32_t)(msgPadded[wordOffset]) << 24;
            curWord |= (uint32_t)(msgPadded[wordOffset + 1]) << 16;
            curWord |= (uint32_t)(msgPadded[wordOffset + 2]) << 8;
            curWord |= (uint32_t)(msgPadded[wordOffset + 3]);

            curBlock.words[j] = curWord;
        }

        msgBlocked.push_back(curBlock);
    }
}

/**
 * CompuateSHA256 - Given a padded/blocked input message, compute its SHA256 hash.
 * 
 * @param blockedMessage [in] Input message to hash.
 * @param hash           [out] Computed hash of message.
 */

void CompuateSHA256(const vector<MsgBlock>& blockedMessage, SHA256Hash &hash)
{
}

/**
 * TestSHA256 - For debugging. Given a test message 'abc', pad it and parse it into 512 bit blocks.
 */

void TestSHA256()
{
    // Internal version.

    vector<MsgBlock> msgBlocked;

    string str("Sample Text");

    Pad(str);

    ParseBlocks(str, msgBlocked);
    PrintBlockedMessage(msgBlocked);

    // OpenSSL validation.

    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());

    SHA256_Final(hash, &sha256);

    __debugbreak();
}