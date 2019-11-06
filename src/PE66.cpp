#include "commoninclude.h"

/**
 * PE66 - Compute the minimum solutions x of x^2 - Dy^2 = 1 for
 * D <= 1000. Return the largest of these solutions.
 *
 * @return Largest solution x from set of minimum set of xs that solve
 * x^2 - Dy^2 = 1 for D <= 1000.
 */

uint64_t PE66()
{
    uint64_t maxD               = 1000;
    double maxX                 = 0;
    uint64_t bestD              = 0;
    const uint32_t numSquares   = 31;

    uint64_t squares[numSquares] =
    {
        1,
        4,
        9,
        16,
        25,
        36,
        49,
        64,
        81,
        100,
        121,
        144,
        169,
        196,
        225,
        256,
        289,
        324,
        361,
        400,
        441,
        484,
        529,
        576,
        625,
        676,
        729,
        784,
        841,
        900,
        961
    };

    for (uint64_t i = 2; i < maxD; i++)
    {
        continuedFrac frac;
        bool cont = false;
        double a;
        double b;

        // Skip square numbers.

        for (uint64_t j = 0; j < numSquares; j++)
        {
            if (i == squares[j])
            {
                cont = true;
                break;
            }
        }

        if (cont)
        {
            continue;
        }

        // Compute continued fraction expansion for
        // current number.

        getContinuedFraction((uint32_t)i, frac);
        
        uint32_t r = frac.prd - 1;
        r = r % 2 == 0 ? 2 * r + 1 : r;
        double d = double(i);

        computeKConvergentDouble(frac, r, a, b); 

        if (a > maxX)
        {
            maxX = a;
            bestD = i;
        }
    }

    return bestD;
}