#include "commoninclude.h"

/**
 * PE179 - Find the number of values N such that N and N+1 have the same
 * number of divisors.
 * 
 * This solution uses a modified prime sieve that keeps track of prime powers
 * as it sieves out values. Once done, it returns a list from [0,max] of prime
 * factorizations. Using that, compute number of divisors using
 * (k1 + 1)(k2 + 1)...(Kn + 1) from N = p1^(k1)p2^(k2)...p3^(k3).
 */

void PE179()
{
    uint32_t max = (uint32_t)1e7;
    vector<vector<primePower>> values;
    factorSieve(max, values);
    uint32_t cnt = 0;

    uint32_t n1 = 1;
    uint32_t n2 = 0;

    for (uint32_t i = 2; i < max; i++)
    {
        n2 = 1;
        for (uint32_t j = 0; j < values[i].size(); j++)
        {
            n2 *= (values[i][j].power + 1);
        }

        if (n2 == n1)
        {
            cnt++;
        }

        n1 = n2;
    }

    printf("%d\n", cnt);
}