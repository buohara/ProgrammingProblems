#include "problems.h"

/**
 * getDivisors Get the divisors of a number by trial division. Loop from
 * i = 1 : sqrt(val). If val % i == 0, add i and (val / i) to list of divisors.
 *
 * @param val      Value to get divisors for.
 * @param divisors Out, a list of divisors of val.
 */

void getDivisors(uint64_t val, set<uint64_t> &divisors)
{
    divisors.insert(1);
    divisors.insert(val);

    for (uint64_t i = 2; i * i <= val; i++)
    {
        if (val % i == 0)
        {
            divisors.insert(i);
            divisors.insert(val / i);
        }
    }
}

/**
 * Solution pair (x, y) for this problem, and compare operator for
 * inserting into set in ascending order/no duplicates.
 */

struct uvec2
{
    uint64_t x;
    uint64_t y;

    bool operator<(const uvec2 &b) const
    {
        if (x != b.x)
        {
            return x < b.x;
        }

        return y < b.y;
    }
};

/**
 * PE108 Find the least value N such that 1 / x + 1 / y = 1 / N has at least 1000 solutions
 * over integers.
 *
 * Build solutions for values of N using pairs of divisors n and m. The Diophantine equation
 * above can be rearranged:
 *
 * 1 / N = 1 / kmn = (kn(m + n) + km(m + n)) / (kn(m + n) * km (m + n).
 *
 * So, take pairs of divisors m and n such that m * n divides N and compute k = N / (m * n).
 * Values x = k * m * (m + n) and y = k * n * (m + n) are solutions to the equation. Start at
 * N = 2 and loop through increasing N computing solutions until we hit an N with 1000 solutions.
 *
 * @return Zero, print solution to console when found.
 */

uint64_t PE108()
{
    uint64_t val = 6;
    const uint64_t max = 1000;

    while (true)
    {
        set<uint64_t> divisors;
        getDivisors(val, divisors);
        set<uvec2> solutions;

        for (auto n : divisors)
        {
            for (auto m : divisors)
            {
                if (m * n > val)
                {
                    break;
                }

                if (val % (m * n) != 0)
                {
                    continue;
                }

                uint64_t k = val / (m * n);
                uint64_t x = k * m * (m + n);
                uint64_t y = k * n * (m + n);

                if (x < y)
                {
                    swap(x, y);
                }

                solutions.insert({ x, y });

                if (solutions.size() >= max)
                {
                    cout << val << endl;
                    __debugbreak();
                }
            }
        }

        val++;
    }

    return 0;
}