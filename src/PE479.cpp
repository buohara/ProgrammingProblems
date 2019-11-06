#include "commoninclude.h"

/**
 * PE479 - Get roots a, b, and c of 1/x = (k/x)^2 * (k + x^2) - kx.
 * Then compute sum on 1 <= p,k <= 10^6 of (a + b)^p * (b + c)^p * (c + a)^p.
 *
 * After computing some cubic roots, I noticed (a + b)(b + c)(c + a) formed a
 * sequence of -3, -8, -15, -24, i.e., start at three and subtract r, r + 2, r + 4.
 * So, no need to solve cubics. The sum on p can be collapsed into a geometric series
 * (1 - p^n+1) / (1 - p) - 1. Compute these terms and be careful with modular arithmetic.
 */

void PE479()
{
    uint64_t max    = 1000000;
    uint64_t sum    = 0;
    uint64_t term   = 3;
    uint64_t q      = 3;
    uint64_t m      = 1000000007;

    for (uint64_t i = 1; i < max; i++)
    {
        uint64_t num = 1 + powMod64(q, max + 1, m);
        uint64_t den = powMod64(1 + q, m - 2, m);
        uint64_t k   = ((num * den) - 1) % m;

        sum += k;
        sum %= m;

        term += 2;
        q += term;
        q %= m;
    }

    printf("%llu\n", sum);
}