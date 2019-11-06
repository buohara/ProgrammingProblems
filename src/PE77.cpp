#include "commoninclude.h"

/**
 * PE77 - Find the smallest number that can be written as the sum of primes
 * (possibly repeated) in at least 5000 different ways.
 */

void PE77()
{
    vector<uint32_t> primes;
    const uint32_t max = (uint32_t)1e4;
    primeSieve(max, primes);
    uint32_t numPrimes = (uint32_t)primes.size();
    vector<vector<uint32_t>> counts(numPrimes + 1, vector<uint32_t>(max + 1));

    // There's only one way to sum to zero (i.e., an empty set of primes).

    for (uint32_t primeCnt = 0; primeCnt < numPrimes; primeCnt++)
    {
        counts[primeCnt][0] = 1;
    }

    // There are no ways to sum to any amount using zero primes.

    for (uint32_t amt = 1; amt <= max; amt++)
    {
        counts[0][amt] = 0;
    }

    // This is a DP "count ways to make change" problem. Count the
    // number of ways N can be written as a sum of 1 prime, 2 primes, etc.

    for (uint32_t primeCnt = 1; primeCnt <= numPrimes; primeCnt++)
    {
        for (uint32_t amt = 1; amt <= max; amt++)
        {
            if (primes[primeCnt - 1] <= amt)
            {
                counts[primeCnt][amt] = counts[primeCnt][amt - primes[primeCnt - 1]] +
                    counts[primeCnt - 1][amt];
            }
            else
            {
                counts[primeCnt][amt] = counts[primeCnt - 1][amt];
            }
        }
    }

    // Find the lowest amount that's >= 5000.

    for (uint32_t amt = 1; amt <= max; amt++)
    {
        for (uint32_t primeCnt = 1; primeCnt <= numPrimes; primeCnt++)
        {
            if (counts[primeCnt][amt] >= 5000)
            {
                printf("%d\n", amt);
                return;
            }
        }
    }
}