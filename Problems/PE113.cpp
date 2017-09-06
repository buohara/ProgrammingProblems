#include "problems.h"

/**
 * isBouncy A brute-force method to determine if a value is bouncy.
 * Used for debugging this problem.
 *
 * @param  val Value to check bounciness property of.
 * @return     True if bouncy, false otherwise.
 */

bool isBouncy(uint64_t val)
{
    bool inc = false;
    bool dec = false;

    uint64_t valTmp = val;
    uint64_t d1 = valTmp % 10;
    valTmp /= 10;

    while (valTmp)
    {
        uint64_t d2 = valTmp % 10;
        valTmp /= 10;

        if (d2 > d1)
        {
            inc = true;
        }

        if (d2 < d1)
        {
            dec = true;
        }

        if (dec && inc)
        {
            return true;
        }

        d1 = d2;
    }

    return false;
}

/**
 * PE113 - Determine how many bouncy numbers are below 10^100. Bouncy means
 * the digits either increase and decrease, e.g., 596, or decrease and increase,
 * e.g., 726.
 *
 * Generate increasing/decreasing numbers by DP. If an (n - 1) digit length number
 * with leading digit p is increasing, then so is any number formed by appending q
 * to the left where q <= p. A similar property is true for decreasing numbers.
 * For this method, start with numbers of length one, and iteratively count non-bouncy 
 * numbers of length 2 using this property, etc., until numbers with 100 digits are
 * formed. This method double-counts "flat" numbers, e.g., 77777, for each number length,
 * so subtract off 9 at each level.
 *
 * @return [description]
 */

uint64_t PE113()
{
    map<uint64_t, map<uint64_t, uint64_t>> incTable;
    map<uint64_t, map<uint64_t, uint64_t>> decTable;
    uint64_t sum = 0;
    uint64_t maxLen = 100;

    for (uint64_t digit = 0; digit < 10; digit++)
    {
        incTable[1][digit] = 1;
        decTable[1][digit] = 1;
    }

    for (uint64_t len = 2; len <= 100; len++)
    {
        for (uint64_t digit = 0; digit < 10; digit++)
        {
            for (uint64_t n = digit; n < 10; n++)
            {
                incTable[len][digit] += incTable[len - 1][n];
            }

            for (uint64_t n = 0; n <= digit; n++)
            {
                decTable[len][digit] += decTable[len - 1][n];
            }
        }
    }

    for (uint64_t len = 1; len <= maxLen; len++)
    {
        for (uint64_t i = 1; i <= 9; i++)
        {
            sum += incTable[len][i];
            sum += decTable[len][i];
        }

        sum -= 9;
    }

    cout << sum << endl;
    __debugbreak();
    return 0;
}