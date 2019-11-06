#include "problems.h"

/**
 * digitSum  - Sum the digits base 10 of an input value.
 * @param  value Value to compute digit sum for.
 * @return       Sum of digits.
 */

uint64_t digitSum(uint64_t value)
{
    uint64_t sum = 0;

    while (value)
    {
        sum += value % 10;
        value /= 10;
    }

    return sum;
}

struct Power
{
    uint64_t val;
    uint64_t b;
    uint64_t e;

    bool operator<(const Power rhs) const
    {
        if (val != rhs.val)
        {
            return val < rhs.val;
        }

        return b < rhs.b;
    }
};

/**
 * PE119 - Find the 30th number that is equal to the sum of its digits raised to
 * any power.
 *
 * The idea here is to generate powers of integers N^M and insert them into an ordered set,
 * storing values (N, M, N^M). Once the set is generated, loop through and check for S(N^M) == N,
 * where S(x) is the sum of digits of x base 10. Stop when we find #30. This approach isn't generally
 * correct - I only take powers of 2 <= N <= 1e4. There could be values of N >= 1e4 where S(N^M) == N.
 * This solution just happened to work, so I stopped and moved on. A more correct approach would be to
 * cap both N and N^M at some max value to prevent any holes. 
 * 
 * @return Zero, print result.
 */

uint64_t PE119()
{
    set<Power> powers;
    uint64_t seqCnt         = 0;
    const uint64_t maxN     = (uint64_t)1e4;
    const uint64_t maxPow   = (uint64_t)1e13;

    for (uint64_t n = 2; n <= maxN; n++)
    {
        uint64_t pow = 1;
        uint64_t e = 0;

        while (pow < maxPow)
        {
            pow *= n;
            e++;

            if (pow < 10)
            {
                continue;
            }

            powers.insert({ pow, n, e });
        }
    }

    for (auto power : powers)
    {
        if (digitSum(power.val) == power.b)
        {
            seqCnt++;
            cout << seqCnt << ": " << power.val << endl;

            if (seqCnt == 30)
            {
                break;
            }
        }
    }

    __debugbreak();
    return 0;
}