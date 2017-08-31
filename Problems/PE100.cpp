#include "problems.h"

/**
 * PE100 - Blue/red ball problem is equivalent to: solve for smallest n such that
 * n * (n - 1) / m * (m - 1) = 0.5 and m >= 1e12. This problem rearranges to a
 * diophantine equation 2n^2 - 2n - 2m^2 + m = 0. Solutions can be found by computing
 * approximations x / y to sqrt(2) with continued fractions, and then converting to
 * (x + 1) / 2 and (y + 1) / 2.
 *
 * @return Zero. Print result.
 */

uint64_t PE100()
{    
    int64_t m = 1;
    int64_t n = 0;
    frac one = { 1, 1 };

    while (true)
    {
        frac r = { n, m };
        frac sqrt = one + r;
       
        mpz_class y = (sqrt.num.get_si() + 1) / 2;
        mpz_class x = (sqrt.den.get_si() + 1) / 2;

        cout << x << ", " << y << endl;

        if (y > 1000000000000)
        {
            if (y * (y - 1) / (x * (x - 1)) == 2)
            {
                cout << "Solution: " << x << endl;
                break;
            }
        }

        uint64_t mtmp = m;
        m = 2 * m + n;
        n = mtmp;
    }

    __debugbreak();
    return 0;
}