#include "problems.h"

/**
 * PE 173 - Count number of laminae (square grid with a square hole centered in
 * the middle) with up to 1 million tiles.
 *
 * Pretty straight-forward. Starting at lamina size N=3, check differences of squares 
 * N^2 - M^2 for M < N. Loop up to a maximum lamina size N=250001. At edge thickness 
 * of 1 tile, this has exactly 1 million tiles.
 * 
 * @return Zero, print result.
 */

uint64_t PE173()
{
    const uint64_t maxN = 250001;
    const uint64_t maxTiles = 1000000;
    uint64_t cnt = 0;

    for (uint64_t n = 3; n <= maxN; n++)
    {
        uint64_t m = (n % 2 == 0) ? 2 : 1;

        while (m < n)
        {
            uint64_t numTiles = (n + m) * (n - m);
            
            if (numTiles <= maxTiles)
            {
                cnt++;
            }

            m += 2;
        }
    }

    cout << cnt << endl;
    __debugbreak();
    return 0;
}