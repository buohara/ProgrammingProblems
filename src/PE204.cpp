#include "problems.h"

/**
 * PE 204 - Find all 100-Hamming numbers up 1e9.
 * 
 * Pretty straight-forward. Push 1 into an STL set, then interatively insert all
 * primes times the current min value in the set, then remove the min value. Every time
 * we remove a min value, increment the Hamming number count.
 * 
 * @return Zero, print result.
 */

uint64_t PE204()
{
    vector<uint64_t> primes;
    primeSieve(100, primes);
    const uint64_t maxHNum = (uint64_t)1e9;
    set<uint64_t> hNums;

    uint64_t hNumCnt = 1;

    hNums.insert(1);

    uint64_t min = *hNums.begin();
    hNums.erase(min);

    while (min < maxHNum)
    {
        hNumCnt++;

        for (auto prime : primes)
        {
            if (min * prime <= maxHNum)
            {
                hNums.insert(min * prime);
            }
        }

        min = *hNums.begin();
        hNums.erase(min);
    }

    cout << hNumCnt << endl;
    __debugbreak();
    return 0;
}