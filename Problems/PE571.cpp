#include "problems.h"

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
        valBase10 += digit * pow(b1, e1);
        e1--;
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
        e1 = e2;
    }
}

bool isSuperPandigital(vector<uint64_t> &digits, vector<uint64_t> &bases)
{
    bool isPandigital = true;

    for (base : bases)
    {

    }

    isPandigital;
}

uint64_t PE571()
{
    vector<uint64_t> digits = { 1, 0, 2, 3, 4, 5, 6, 7, 8, 9 };
    uint64_t numSuperPandigitals = 0;

    while (next_permutation(digits.begin(), digits.end()))
    {
        numSuperPandigitals++;
        if (numSuperPandigitals == 10)
        {
            break;
        }
    }

    __debugbreak();
    return 0;
}