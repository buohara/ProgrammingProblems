#include "problems.h"

/**
 * PE78 - Find the least value N such that the number of ways N can be
 * divided into smaller sets is divisible by 1,000,000.
 *
 * At first, this looked like a change counting problem, so I tried a basic
 * recursive algorithm, then a DP algorithm. Both were too slow/memory heavy.
 *
 * After some thinking, I realized this is an integer partition problem, and
 * partitions of N can be written as a recurrence using partitions of M < N,
 * namely, when M is a pentagonal number.
 * See https://en.wikipedia.org/wiki/Partition_(number_theory)
 *
 * @return Zero. Print answer when found.
 */

uint64_t PE78()
{
    uint64_t maxPent = (uint64_t)1e4;
    uint64_t maxN = (uint64_t)1e6;

    vector<int64_t> pentagonals(2 * maxPent);
    vector<mpz_class> partitions;

    for (int64_t i = 0; i < maxPent; i++)
    {
        int64_t m1 = i + 1;
        int64_t m2 = -m1;

        if ((m1 - 1) % 2 == 0)
        {
            pentagonals[2 * i] = m1 * (3 * m1 - 1) / 2;
            pentagonals[2 * i + 1] = m2 * (3 * m2 - 1) / 2;
        }
        else
        {
            pentagonals[2 * i] = -m1 * (3 * m1 - 1) / 2;
            pentagonals[2 * i + 1] = -m2 * (3 * m2 - 1) / 2;
        }
    }

    partitions.push_back(1);

    for (uint64_t n = 1; n < maxN; n++)
    {
        partitions.push_back(0);

        for (uint64_t m = 0; abs(pentagonals[m]) <= n; m++)
        {
            if (pentagonals[m] < 0)
            {
                partitions[n] -= partitions[n - abs(pentagonals[m])];
            }
            else 
            {
                partitions[n] += partitions[n - abs(pentagonals[m])];
            }
        }

        if (partitions[n] % 1000000 == 0)
        {
            cout << n << endl;
            __debugbreak();
            return n;
        }
    }

    return 0;
}