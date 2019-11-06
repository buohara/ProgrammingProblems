#include "problems.h"

/**
 * PE313 - Let S(m, n) be the min number of moves to solve an m x n sliding
 * game puzzle, i.e., move a red counter from the top left of the grid to the
 * bottom right. Count the number of grids for which S(m, n) = p^2, where p is
 * a prime < 1e6.
 *
 * For an arbitrary grid, there are a few sets of moves to count:
 *
 * 1. Move the empty slot up to the red counter. This costs m + n - 4 moves.
 *
 * 2. Move the red counter diagonally as far as it can go using the rotation move
 * shown in the problem description. The initial rotation costs 5 moves, additional
 * rotations cost 6 * min(m - 2, n - 2). Assume m > n, so this is just 6n - 7.
 *
 * 3. Once the red counter has moved diagonally as far as possible, slide it along
 * the side until it hits the bottom corner. The first slide costs 3 moves, additional ones
 * cost 5. If m > n, this is 5 * (m - n) - 2.
 *
 * Combining terms gives 6m + 2n - 13 = p^2. This is a linear Diophantine with m > n. Just
 * double the solutions for m to get the n > m cases. For m = n, solve the equations simplify
 * to 8m - 11 = p^2.
 *
 * @return Zero, print result to console.
 */

uint64_t PE313()
{
    const uint64_t primeBnd = 1000000;
    vector<uint64_t> primes;
    primeSieve(primeBnd, primes);
    uint64_t sum = 0;

    for (auto p : primes)
    {
        uint64_t k = p * p + 11;
        
        if (k % 8 == 0)
        {
            sum++;
        }

        k = (p * p + 13) / 2;
        
        uint64_t mmax = (k - 2) / 3;
        uint64_t mmin = k / 4 + 1;

        sum += 2 * (mmax - mmin + 1);
    }

    cout << sum << endl;
    __debugbreak();
    return 0;
}