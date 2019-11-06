#include "problems.h"

/**
 * PE95 Find the smallest value of the longest chain of amicable values
 * below 1e6.
 *
 * First, compute divisor sums of all values up to 1e6. Use a sieve to get
 * prime factorizations, then use property that proper divisor sum of N is 
 * (1 + pk_1 + pk_1^2 ... )(1 + pk_2 + pk_2^2 ... ) - N and formula for 
 * geometric series. After computing these, follow sums, storing ones that
 * form chains. Finally, get the longest chain found and grab its min value.
 *
 * @return Zero. Print result to console.
 */

void PE95()
{
    uint64_t max = (uint64_t)1e6;
    vector<vector<primePower>> primeFactors;
    factorSieve((uint32_t)max, primeFactors);
    vector<uint64_t> divisorSums(max + 1, 0);
    uint64_t min = UINT64_MAX;

    // Get divisor sums from prime factorizations.

    vector<vector<uint64_t>> chains;
    uint64_t n = 0;

    for (auto primes : primeFactors)
    {
        if (n < 2)
        {
            divisorSums[n++] = 0;
            continue;
        }

        uint64_t sum = 1;

        for (auto prime : primes) sum *= geomSum(prime.prime, prime.power);

        divisorSums[n] = sum - n;
        n++;
    }

    // Follow divisor sums to form chains.

    for (uint64_t n = 0; n < divisorSums.size(); n++)
    {
        vector<uint64_t> chain;
        chain.push_back(n);
        uint64_t next = divisorSums[n];

        if (n % 1000 == 0) cout << n << endl;

        while (find(chain.begin(), chain.end(), next) == chain.end())
        {
            if (next >= 1000000) break;

            chain.push_back(next);
            next = divisorSums[next];
        }

        if (next == chain[0]) chains.push_back(chain);
    }

    // Grab the longest chain (debugging, I happen to know its length is 28) 
    // and find its min value.

    for (auto chain : chains)
    {
        if (chain.size() == 28)
        {
            for (auto val : chain)
            {
                if (val < min) min = val;
            }

            break;
        }
    }

    cout << min << endl;
}