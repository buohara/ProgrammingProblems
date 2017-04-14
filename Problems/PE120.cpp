#include "problems.h"

/**
 * PE120 - Find the max R of R = ((a + 1)^N + (a - 1)^N) mod a^2 for for all N and
 * 3 <= a <= 100.
 *
 * The binomial expansions cancel odd/even powers of a depending on
 * whether N is even/odd. For N even, all terms except for 2 contain 2 or more powers of
 * a, so R is always 2. For N odd, the only term that doesn't have 2 or more powers of a
 * is the term 2aN. So, just loop over values of N computing 2aN mod a^2 looking for a max. 
 * This solution just loops up to N <= a^2, which I don't think is quite right (although it
 * got the right answer for this problem). It's probably better to keep checking N until 
 * the remainders start repeating a cycle.
 */

uint64_t PE120()
{
    uint64_t sum = 0;

    for (uint64_t a = 3; a <= 1000; a++)
    {
        uint64_t maxR = 2;

        for (uint64_t n = 1; n <= a * a; n += 2)
        {
            uint64_t p = 2 * n * a;
            uint64_t newR = p % (a * a);

            if (newR > maxR)
            {
                maxR = newR;
            }
        }

        sum += maxR;
    }

    return sum;
}