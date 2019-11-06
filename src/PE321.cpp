#include "commoninclude.h"

/**
 * PE321 - Swapping counters. Given an arrangement of 3 Xs and 3 0s like XXX 000, 
 * find number of swaps M(3) required to get 000 XXX. E.g., M(3) = 15. 
 * Find the first 40 values of N for which M(N) is a triangle number.
 *
 * First, M(N) = (N + 1)^2 - 1. Triangle numbers have the form M(M + 1), so we need to
 * solve for pairs (M, N) such that (N + 1)^2 - 1 - M(M + 1) = 0. Rearranging, this turns
 * into a Pell-like equation, x^2 - 2y^2 = -7. Two fundamental solutions to this are 
 * (x, y) = (1, 2) and (-1, 2). 
 *
 * This approach generates a family of solutions by taking the
 * fundamental solution to x^2 - 2y^2 = -1, (1 + sqrt(2)), and generating the solutions
 * (1 + 2 * sqrt(2)) * (1 + sqrt(2))^2N and (-1 + 2 * sqrt(2)) * (1 + sqrt(2))^2N. The
 * sqrt(2) component of each of these solutions is 2N + 2 where M(N) is a triangle number.
 */

void PE321()
{
    const int64_t x = 3;
    const int64_t y = 2;

    int64_t a = 3;
    int64_t b = 2;
    int64_t cnt = 1;
    int64_t sum = 0;

    for (uint32_t i = 0; i < 20; i++)
    {
        int64_t c = -1;
        int64_t d = 2;

        int64_t n = b * c + a * d;
        cout << cnt << ": " << (n - 2) / 2 << endl;
        cnt++;
        sum += (n - 2) / 2;

        c = 1;

        n = b * c + a * d;
        cout << cnt << ": " << (n - 2) / 2 << endl;
        cnt++;
        sum += (n - 2) / 2;

        int64_t tmpA = a;
        a = x * a + 2 * b * y;
        b = y * tmpA + b * x;
    }

    cout << endl << sum << endl;
}