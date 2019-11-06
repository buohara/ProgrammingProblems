#include "commoninclude.h"

/**
 * PE348 - Find a cyclic number A whose first 11 digits are 00000000137 and last 5 digits
 * are 56789.
 *
 * Use properties of reptend primes, a prime such that 1/p generates a repeating
 * decimal expansion of length p - 1, the decimal part of which is the cyclic number A.
 * We're given the first digits of A are 00000000137, so 1/p ~= 0.00000000137, which gives
 * a ballpark of primes to search through (729e6 - 730e6). A must satisfy 
 * A = (10^(p - 1) - 1) / p, so p * A is a bunch of 9s. We're given the last digits of A are
 * 56789, so check prime candidates times 56789 results in 9s. When we find one, do long
 * division to get the digits of A.
 */

uint64_t PE358()
{
    vector<uint32_t> primes;
    primeSieve(729000000, 730000000, primes);
    uint64_t nines = (uint64_t)1e15 - 1;

    for (uint32_t i = 0; i < primes.size(); i++)
    {
        if ((((uint64_t)primes[i]) * 56789) % 100000 == 99999)
        {
            uint64_t sum = 0;
            uint64_t r = (uint64_t)primes[i];
            uint64_t t = 1;

            while (t < r)
            {
                t *= 10;
            }

            for (uint32_t j = 0; j < primes[i] - 1; j++)
            {
                sum += t / r;
                t = 10 * (t - r * (t / r));
            }

            printf("%llu\n", sum);
            __debugbreak();
        }
    }

    return 0;
}