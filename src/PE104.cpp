#include "problems.h"

/**
 * PE104 - Find the first Fibonacci number those first 9 digits and last 9 digits are
 * 1-9 pandigital.
 *
 * This is a very brute-force approach. It uses the MPIR library for big integers. Keep
 * looping computing Fibonacci numbers. Once we get to a 9 digit number, grab its digits
 * as a string and check the first and last 9 digits for 1-9. The bottleneck of this code
 * is extracting the digit string. It would probably be a lot quicker to mod 1e9 to get the
 * last 9 digits and divide 10^(numDigits - 9) to get the first 9. But, this works and I
 * want to do more problems :).
 */

void PE104()
{
    mpz_class f1 = 1;
    mpz_class f2 = 1;
    mpz_class f3;
    uint32_t solutionIdx = 3;

    string str;
    str.reserve(100000);

    while (true)
    {
        f3 = f1 + f2;
        f1 = f2;
        f2 = f3;

        str = f3.get_str();
        uint32_t nDigits = (uint32_t)str.size();

        if (nDigits >= 9)
        {
            uint32_t startCnts[10] = { 0 };
            uint32_t endCnts[10] = { 0 };

            for (uint32_t j = 0; j < 9; j++)
            {
                uint32_t sDigit = str[j] - '0';
                uint32_t eDigit = str[nDigits - j - 1] - '0';
                startCnts[sDigit]++;
                endCnts[eDigit]++;
            }

            bool endsPandigital = true;

            for (uint32_t j = 1; j < 10; j++)
            {
                if (startCnts[j] != 1 || endCnts[j] != 1)
                {
                    endsPandigital = false;
                    break;
                }
            }

            if (endsPandigital == true)
            {
                break;
            }
        }

        solutionIdx++;
    }

    printf("%d\n", solutionIdx);
}