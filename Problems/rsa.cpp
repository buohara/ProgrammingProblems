#include "primes.h"
#include "rsa.h"
#include <time.h>
#include <string>

using namespace std;

// Global RSA keys.

static uint32_t n = 0;
static uint32_t e = 0;
static uint32_t d = 0;

/**
 * AssertMultOverflowU32 Assert if multiplying to 32-bit unsigned ints (i * j) will result in an
 * overflow. Used when performing modular exponentation.
 * 
 * @param i First multiplication argument [in].
 * @param j Second multiplication argument [in].
 */

__inline void AssertMultOverflowU32(uint32_t i, uint32_t j)
{
    assert(i < UINT32_MAX / j);
}

/**
 * getCoprimeVal - For a given input value and a list of primes, return the first prime number
 * that is coprime to the input value. Naive approach: determine the prime factors of the
 * input value by trial division, then select that smallest prime number from input prime list not in 
 * set of prime factors computed for val.
 *
 * @param  val    Input value to get a coprime value for [in].
 * @param  primes A list of prime numbers [in].
 *
 * @return        The smallest prime number coprime to val.
 */

uint32_t GetCoprimeVal(uint32_t val, vector<uint32_t> &primes)
{
    vector<uint32_t> primeFactors;

    for (auto &p : primes)
    {
        if (val % p == 0)
        {
            primeFactors.push_back(p);

            while (val % p == 0)
            {
                val /= p;
            }
        }

        if (val == 1)
        {
            break;
        }
    }

    for (auto &p : primes)
    {
        if (find(primeFactors.begin(), primeFactors.end(), p) == primeFactors.end())
        {
            return p;
        }
    }
}

/**
 * modularInverse - Find the modular inverse of an input value with respect to an input
 * modulus. Naive implementation. Simply loop through candidate inverses and return
 * the candidate when (val * candidate) % modular == 1. Return 0 if no inverse found.
 *
 * @param  val Value to compute modular inverse for [in].
 * @param  mod Modulus to use for inverse [in].
 *
 * @return     Inverse of val % modulus if found, 0 otherwise.
 */

uint32_t ModularInverse(uint32_t val, uint32_t mod)
{
    for (uint32_t i = 2; i < mod; i++)
    {
        if ((val * i) % mod == 1)
        {
            return i;
        }
    }

    return 0;
}

/**
 * generateKeys - Generate keys for RSA encryption/decryption. Generate a list of prime numbers,
 * then randomly pick two primes, p and q, from the list. Compute n = p * q,
 * phi = (p - 1) * (q - 1), e such that gcd(e, phi) = 1, and d such that d * e = 1 mod phi. The
 * values (d, e, n) are the keys used for encryption/decryption.
 */

void GenerateRSAKeys()
{
    vector<uint32_t> primes;
    const uint32_t max_prime = 500;

    primeSieve(max_prime, primes);

    uint32_t idx1   = rand() % (primes.size());
    uint32_t idx2   = rand() % (primes.size());

    uint32_t p      = primes[idx1];
    uint32_t q      = primes[idx2];

    n               = p * q;
    uint32_t phi    = (p - 1) * (q - 1);
    e               = GetCoprimeVal(phi, primes);
    d               = ModularInverse(e, phi);
}

/**
 * encrypt - Encrypt an input value using simple RSA encryption. Given a message coded into an
 * integer M and global keys (n, e), compute ciphertext c = M^e mod n. No padding used. Exponentiation
 * method used is inefficient: does e multiplications.
 *
 * Assumes static global keys have already been generated. Currently assumes input string
 * length is 1 (i.e., a single character). Method concatenates ascii values of input string
 * into a long integer. Encryption/decryption then takes remainders mod N of this integer,
 * which fails when the integer is too big and N too small.
 *
 * @param  msg Message to encrypt [in].
 *
 * @return     Encrypted ciphertext of input message.
 */

uint32_t Encrypt(string &msg)
{
    assert(n != 0);
    assert(d != 0);
    assert(e != 0);

    uint32_t l = msg.length();

    assert(l == 1);

    const char* pData = msg.data();
    string intstring;

    for (uint32_t i = 0; i < l; i++)
    {
        intstring += to_string((uint8_t)pData[i]);
    }

    uint32_t m = atol(intstring.c_str());
    uint32_t c = 1;

    for (uint32_t i = 0; i < e; i++)
    {
        AssertMultOverflowU32(m, c);
        c *= m;
        c %= n;
    }
    
    return c;
}

/**
 * decrypt - Decrypt a ciphertext using simple RSA decryption. Given a ciphertext c and global
 * keys (n, d), compute original message m = c ^ d mod n. Exponentiation
 * method used is inefficient: does d multiplications.
 * 
 * Assumes global RSA keys (n, e, d) have already been generated.
 *
 * @param  c Ciphertext to decrypt [in].
 *
 * @return   String with decrypted message.
 */

string Decrypt(uint32_t c)
{
    assert(n != 0);
    assert(d != 0);
    assert(e != 0);

    uint32_t m = 1;

    for (uint32_t i = 0; i < d; i++)
    {
        AssertMultOverflowU32(m, c);
        m *= c;
        m %= n;
    }

    char message[2] = { (char)m, '\0' };
    return string(message);
}

/**
 * TestRSA - Program to test RSA encryption/decryption. Generate RSA keys.
 * Randomly generate a single character message (a letter between A and Z, or ascii 65 to 90).  
 * Encrypt the message, then decrypt it. Assert decrypted message is same as original message.
 * Repeat 1000 times.
 */

void TestRSA()
{
    const uint32_t nTestLoops = 1000;
    srand(time(NULL));
    GenerateRSAKeys();

    for (uint32_t i = 0; i < nTestLoops; i++)
    {
        char randMsg[2] = { (char)(rand() % 26 + 65), '\0' };
        string message  = string(randMsg);
        uint32_t c      = Encrypt(message);
        string result   = Decrypt(c);

        assert(result == message);
    }
}