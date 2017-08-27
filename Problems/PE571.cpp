#include "problems.h"

/**
 * convertBase Convert digits from base b1 to base b2.
 *
 * @param digitsIn  Vector of input digits in base b1.
 * @param b1        Base of input digits.
 * @param digitsOut Output vector to hold digits in base b2.
 * @param b2        Base of output digits.
 */

void convertBase(
    vector<uint64_t> &digitsIn,
    uint64_t b1,
    vector<uint64_t> &digitsOut,
    uint64_t b2)
{
    uint64_t valBase10 = 0;
    uint64_t e1 = digitsIn.size() - 1;
    uint64_t e2 = 0;

    for (auto digit : digitsIn)
    {
        valBase10 += digit * pow(b1, e1--);
    }

    e1 = (uint64_t)(log(valBase10) / log(b2));

    while (valBase10)
    {
        e2 = (uint64_t)(log(valBase10) / log(b2));
        uint64_t newDigit = valBase10 / pow(b2, e2);

        if (e1 - e2 > 1)
        {
            for (uint64_t i = 0; i < e1 - e2 - 1; i++)
            {
                digitsOut.push_back(0);
            }
        }

        digitsOut.push_back(newDigit);
        valBase10 -= newDigit * pow(b2, e2);

        if (e2 > 0 && valBase10 == 0)
        {
            while (e2 > 0)
            {
                digitsOut.push_back(0);
                e2--;
            }
        }

        e1 = e2;
    }
}

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

uint64_t PE571()
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
                val += digit * pow(12, e--);
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
    __debugbreak();
    return 0;
}