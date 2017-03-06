#include "problems.h"

/**
 * PE577 - Count the number of regular hexagons in a triangular lattice with side
 * 3 <= N <= 12345.
 */

uint64_t PE577()
{
    uint64_t sum = 0;

    for (uint64_t i = 3; i <= 12345; i++)
    {
        uint64_t maxHexSize = i / 3;

        for (uint64_t j = 1; j <= maxHexSize; j++)
        {
            sum += j * (i - 3 * j + 1) * (i - 3 * j + 2) / 2;
        }
    }

    return sum;
}