#include "problems.h"

void GenerateAdmiss(
    uint64_t max,
    vector<uint64_t> &generators,
    set<uint64_t> &admiss
)
{
    set<uint64_t> newVals;
    uint64_t min = 1;
    
    for (auto p : generators)
    {
        min *= p;
    }

    while (min < max)
    {
        for (auto p : generators)
        {
            newVals.insert(p * min);
        }

        admiss.insert(min);

        min = *newVals.begin();
        newVals.erase(min);
    }
}

void PE293()
{
    const uint64_t max = (uint64_t)1e9;

    vector<uint64_t> primes;
    primeSieve(max, primes);
    set<uint64_t> admiss;
    set<uint64_t> fortunates;
    uint64_t twoPows = 2;
    uint64_t sum = 0;

    while (twoPows < max)
    {
        admiss.insert(twoPows);
        twoPows *= 2;
    }

    for (uint64_t i = 2; i <= 10; i++)
    {
        uint64_t min = 1;
        vector<uint64_t> generators;

        for (uint64_t k = 0; k < i; k++)
        {
            min *= primes[k];
            generators.push_back(primes[k]);

            if (min >= max)
            {
                break;
            }
        }

        if (min >= max)
        {
            continue;
        }

        GenerateAdmiss(max, generators, admiss);
    }

    for (auto val : admiss)
    {
        auto ub = upper_bound(primes.begin(), primes.end(), val + 1);
        fortunates.insert(*ub - val);
    }

    for (auto val : fortunates)
    {
        sum += val;
    }

    cout << sum << endl;
}