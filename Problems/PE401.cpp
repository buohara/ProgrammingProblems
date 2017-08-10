#include "problems.h"

/**
 * Sum of squares from min to max, inclusive.
 */

mpz_class squareSum(mpz_class min, mpz_class max)
{
    mpz_class s1     = max * (max + 1) * (2 * max + 1) / 6;
    mpz_class a      = min - 1;
    mpz_class s2     = a * (a + 1) * (2 * a + 1) / 6;
    
    return s1 - s2;
}

/**
 * PE401 - Find the sums of squares of divisors for each N in 1 to 1e15. Code is slow
 * (~3mins), probably because it uses big integers.
 *
 * Use the formula sum(1:N)(N^2) = N * (N + 1) * (2N + 1) / 6. Use the following observations:
 *
 * 1. A number N divides M = (1e15 / N) numbers between 1 and 10^15. So, M * N^2 appears in
 * the final sum.
 *
 * 2. Consider the number 1e15 / 2 = 5e14. This means all numbers M from 5e14 + 1 to 1e15
 * squared will appears in the final sum as 1 * M^2, so we can use the sum of squares formula.
 * Likewise, all M numbers 10^15 / 3 = 3.33^1014 + 1 to 5^15 will appear as 2 * M^2 in the 
 * final sum, etc.
 * 
 * So, we only need to loop up to the square root of 1e15 and sum contributions from 1 and 2
 * to get the final answer.
 */

uint64_t PE401()
{
    uint64_t max    = (uint64_t)1e15;
    mpz_class sum    = max;

    for (uint64_t i = 2; i * i < max; i++)
    {   
        mpz_class k1 = max / (i - 1);
        mpz_class k2 = max / i;

        sum += k2 * i * i;
        
        sum += (i - 1) * squareSum(k2 + 1, k1);

        if ((i + 1) * (i + 1) > max && i + 1 <= k2)
        {
            mpz_class k3 = max / (i + 1);
            sum += k3 * (i + 1) * (i + 1);
        }
    }

    printf("%s\n", sum.get_str().c_str());
    __debugbreak();
    return 0;
} 