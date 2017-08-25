#include "problems.h"

/**
 * Solve LC - Find minimum non-negative x that solves x = a mod n, x = b mod m. Return
 * 0 zero if no solution is found. Solution is found by forward and back substitution of
 * x = a + k * n and x = b + l * m, eliminating GCDs along the way. Once one solution is
 * found, subtract off extra factors of m * n / GCG(m, n) to get minimum solution.
 * 
 * @param  a 
 * @param  n 
 * @param  b 
 * @param  m 
 * @return Minimum non-negative solution to x = a mod n, x = b mod m.
 */

uint64_t SolveLC(int64_t a, int64_t n, int64_t b, int64_t m)
{
    int64_t c = gcd(n, m);
    int64_t d = b - a;

    if (d < 0)
    {
        int64_t k = -d / m;
        d += (k + 1) * m;
    }
    
    if (d % c != 0)
    {
        return 0;
    }

    d /= c;
    int64_t n2 = n / c;
    int64_t m2 = m / c;

    int64_t x;
    int64_t y;

    gcdExtended(n2, m2, x, y);

    d *= x;
    
    if (d < 0)
    {
        int64_t k = -d / m2;
        d += (k + 1) * m2;
    }

    int64_t out = d * n + a;
    
    if (out > m * n2)
    {
        int64_t k = out / (m * n2);
        out -= (k * m * n2);
    }

    return out;
}

/**
 * PE 531 - For 1000000 <= n < m < 1005000, sum minimum non-negative solution to
 * linear congruences x = phi(n) mod n and x = phi(m) mod m. First, compute totients up
 * to 1005000. Then, loop over n and m solving linear congruences with SolveLC.
 * 
 * @return Zero. Print answer to problem to console.
 */

uint64_t PE531()
{
    uint64_t max = 1005000;
    uint64_t sum = 0;

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
    
    for (uint64_t n = 1000000; n < max; n++)
    {
        for (uint64_t m = n + 1; m < max; m++)
        {
            uint64_t tn = totients[n];
            uint64_t tm = totients[m];
            uint64_t x = SolveLC(tn, n, tm, m);

            if (x % n != tn && x != 0)
            {
                __debugbreak();
            }

            if (x % m != tm && x != 0)
            {
                __debugbreak();
            }

            sum += x;
        }
    }

    printf("%llu\n", sum);
    __debugbreak();
    return 0;
}