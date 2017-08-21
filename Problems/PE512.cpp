#include "problems.h"

/**
 * geomSeriesMod - Compute the geometric series on powers of r up to n modulo m
 * recursively.
 * 
 * @param  r Base for geometric series terms.
 * @param  n Max power of r.
 * @param  m Modulus to take for this geometric series.
 * @return   Result of geometric series mod m.
 */

uint64_t geomSeriesMod(uint64_t r, uint64_t n, uint64_t m)
{
    if (n == 0)
    {
        return 1;
    }

    if (n % 2 == 0)
    {
        uint64_t s = 1 + ((r + r * r) % m) * (geomSeriesMod(r * r, (n - 2) / 2, m) % m);
        return s;
    }
    else
    {
        uint64_t s = ((1 + r) % m) * (geomSeriesMod(r * r, (n - 1) / 2, m) % m);
        return s;
    }
}

/**
 * PE512 - Find the sum of phi(n^i) mod (n + 1) for i = 1 to n, n = 1 to 5 * 10^8.
 * 
 * Use the observation phi(n^i) = n^(i - 1) * n * ((p_k - 1) / (p_k)) =
 * n^(i - 1) * phi(n). The sum over i then collapses to a geometric series on powers of
 * n, which gets multiplied by phi(n). Use a sieve to compute phi for n up to 5 * 10^8.
 * Use a recursive geometric series function to compute geometric series values mod n + 1.
 * At first, I tried to use direct modular arithmetic, but 1 - n in (1 - n^n) / (1 - n)
 * doesn't always have a modular inverse. Recursion is slow, but gets the right answer.
 * 
 * @return Print the result, return 0.
 */

uint64_t PE512()
{
    uint64_t max = (uint64_t)5e8;
    uint64_t sum = 1;

    vector<uint64_t> totients(max + 1, 1);
    totients[0] = 0;
    totients[1] = 1;

    for (uint64_t n = 2; n <= max; n++)
    {
        totients[n] = n;
    }

    for (uint64_t n = 2; n <= max; n++)
    {
        if (totients[n] == n)
        {
            uint64_t tmp = n;
            while (tmp <= max)
            {
                totients[tmp] /= n;
                totients[tmp] *= (n - 1);
                tmp += n;
            }
        }
    }

    for (uint64_t n = 2; n <= max; n++)
    {
        uint64_t m = n + 1;
        uint64_t a = geomSeriesMod(n, n - 1, m);
        uint64_t b = totients[n];
        sum += (a * b) % m;
    }

    printf("%llu\n", sum);
    __debugbreak();
    return 0;
}