#include "commoninclude.h"

/**
 * Struct to hold a number and the product of its prime factors
 * (not necessarily all powers of those factors).
 */

struct Radical
{
    uint32_t value;
    uint32_t radical;

    bool operator<(const Radical &rhs) const
    {
        if (radical == rhs.radical)
        {
            return value < rhs.value;
        }

        return radical < rhs.radical;
    }
};

/**
 * PE124 - Find the 10,000th number from 100,000 numbers sorted by radical (product)
 * of single powers of the numbers prime factors, e.g., rad(504) = 2 * 3 * 7 = 42.
 *
 * Pretty straight-forward approach. Do a prime seive to gets primes up to 100,000.
 * Factor all numbers up to 100,000 by trial division, then sort by radical. Return
 * item 10,000.
 */

uint32_t PE124()
{
    uint32_t max = (uint32_t)1e5;
    vector<uint32_t> primes;
    primeSieve(max, primes);

    vector<Radical> radicals;
    radicals.resize(max + 1);

    radicals[1] = { 1, 1 };
    radicals[2] = { 2, 2 };
    radicals[3] = { 3, 3 };

    for (uint32_t i = 4; i <= max; i++)
    {
        uint32_t tmp = i;
        uint32_t rad = 1;

        for (uint32_t j = 0; j < primes.size(); j++)
        {
            uint32_t prm = primes[j];

            if (tmp % prm == 0)
            {
                rad *= prm;
                while (tmp % prm == 0)
                {
                    tmp /= prm;
                }
            }

            if (tmp == 1)
            {
                break;
            }
        }

        radicals[i] = { i, rad };
    }

    sort(radicals.begin(), radicals.end());
    return radicals[max].radical;
}