#include "problems.h"

/**
 * Given sequence of primes p1, p2, ... , pN, ..., find first value of N
 * such that ((pN + 1)^N + (pN - 1)^N) mod p^2 > 1e10.
 *
 * Expanding out the exponentials, (pN +- 1)^N, alternating terms cancel. Even
 * powers of N will always have a remainder of 2. For odd N, only the second to last
 * term will have a non-zero remainder, (2 * binomial(n, n - 1) * p ) mod p^2 =
 * (2 * n * p ) mod p^2
 *
 * So, just look through primes computing (2 * n * p ) mod p^2
 * until we hit a value > 1e10;
 *
 * @return Zero, print result.
 */

void PE123()
{
    const uint64_t maxR = (uint64_t)1e10;
    const uint64_t maxPrime = (uint64_t)1e6;

    vector<uint64_t> primes;
    primeSieve(maxPrime, primes);

    Binomial bi;

    uint64_t n = 2;

    while (n < primes.size())
    {
        uint64_t p = primes[n];
        uint64_t sum = 2 * (n + 1) * p;
        sum %= (p * p);

        if (sum > maxR)
        {
            cout << n + 1 << ": " << sum << endl;
            __debugbreak();
        }

        n += 2;
    }
}