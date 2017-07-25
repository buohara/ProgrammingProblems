#include "problems.h"

/**
 * PE187 - Find the number of values less than 1e8 that have exactly 2,
 * not necessarily distinct, prime powers.
 *
 * Solution is to use a sieve to get primes up to 1e8 / 2. Then, just do a
 * double loop and multiply together all prime pairs. Add a product to the total
 * count if less than 1e8.
 */

uint32_t PE187()
{
    uint32_t max = (uint32_t)1e8;
    uint32_t cnt = 0;

    vector<uint32_t> primes;
    primeSieve(max / 2, primes);
   
    for (uint32_t i = 0; i < primes.size(); i++)
    {
        uint32_t p1 = primes[i];
        
        if (p1 * p1 > max)
        {
            break;
        }

        for (uint32_t j = i; j < primes.size(); j++)
        {
            uint32_t p2 = primes[j];
            
            if (p1 * p2 < max)
            {
                cnt++;
            }
            else
            {
                break;
            }
        }
    }

    return cnt;
}