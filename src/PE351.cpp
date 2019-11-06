#include "commoninclude.h"

/**
 * PE351 - Find the number of points occluded from the center in an order 1e8
 * hexagonal orchard.
 *
 * A point K is occluded along an edge of length N if K/N is reducible. E.g, 
 * point 2 along an edge of length 4 is occluded by (2/4) = (1/2). So, work this
 * from the inside out. Along each edge, compute the number of irreducible points
 * using the totient function. Project these points (e.g., for 1/2, do 2/4,
 * 3/6, 4/8, etc., out to 5e7/1e8). All these points are occluded. Multiply this number
 * by 6 for each of the 6 triangles in a hex grid. Add in 6 * (1e8 - 1) for the six grid
 * legs to get the total.
 */

void PE351()
{
    const uint64_t max = (uint64_t)1e8;
    uint64_t sum = 0;
    sum += 6 * (max - 1);

    vector<vector<primePower>> factors;
    factorSieve(max, factors);

    for (uint64_t i = 2; i < factors.size(); i++)
    {
        uint64_t totient = i;
        
        for (uint64_t j = 0; j < factors[i].size(); j++)
        {
            totient *= factors[i][j].prime - 1;
            totient /= factors[i][j].prime;
        }

        uint64_t occludedLayers = max / i - 1;
        sum += 6 * totient * occludedLayers;
    }

    printf("%llu\n", sum);
}