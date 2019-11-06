#include "problems.h"

/**
 * isSuperPandigital Check if a vector of digits is pandigital over
 * a set of input bases.
 *
 * @param  digits Input vector to check for super pandigital property.
 * @param  bases  Input vector of bases to check.
 * @return        True if input vector is pandigital over all bases, false o/w.
 */

bool isSuperPandigital(vector<uint64_t> &digits, vector<uint64_t> &bases)
{
    for (auto base : bases)
    {
        vector<uint64_t> baseDigits;
        convertBase(digits, 12, baseDigits, base);
        vector<bool> digitsFound(base, false);

        if (baseDigits[0] == 0)
        {
            return false;
        }

        for (uint64_t i = 0; i < base; i++)
        {
            if (find(baseDigits.begin(), baseDigits.end(), i) != baseDigits.end())
            {
                digitsFound[i] = true;
            }
        }

        if (find(digitsFound.begin(), digitsFound.end(), false) != digitsFound.end())
        {
            return false;
        }
    }

    return true;
}

/**
 * PE571 Find the sum of the 10 smallest numbers that are pandigitial in bases 2 to 12.
 *
 * Straight-forward, but slow. Start with the smallest possible 12-pandigital number,
 * 1023456789AB. Then, just brute-force convert to bases 2-11 and check if each result
 * contains all digits in that base, add to running sum if so. Iterate through 12-pandigitals
 * by taking lexicographic permutations.
 *
 * The bottleneck in this code is the time spent converting bases. I think these
 * conversions might be unnecessary. I could just get 1023456789AB in all bases once,
 * then take lexicographic permutations of those as I iterate through 12-pandigitals.
 *
 * @return Zero. Print sum to console.
 */

void PE571()
{
    vector<uint64_t> digits = { 1, 0, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    vector<uint64_t> bases = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
    uint64_t numSuperPandigitals = 0;
    uint64_t sum = 0;

    do
    {
        if (digits[0] == 0)
        {
            continue;
        }

        if (isSuperPandigital(digits, bases))
        {
            numSuperPandigitals++;
            uint64_t val = 0;
            uint64_t e = 11;

            for (auto digit : digits)
            {
                val += digit * (uint64_t)pow(12, e--);
            }

            printf("Super pandigital %llu: %llu\n", numSuperPandigitals, val);
            sum += val;
        }
        
        if (numSuperPandigitals == 10)
        {
            break;
        }
    } 
    while (next_permutation(digits.begin(), digits.end()));

    printf("%llu\n", sum);
}