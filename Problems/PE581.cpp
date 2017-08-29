#include "problems.h"

struct KSmoothGenerator
{
    vector<uint64_t> primes;
    set<uint64_t> queue;
    
    /**
     * Init - Initialize the k smooth generator with list of primes
     * pk up to K. Put 1 into its queue of values, then loop through
     * pulling queue items min and inserting pk * min without duplices
     * (using STL set insert) up to a max value.  
     *
     * @param primesIn List of primes up to K.
     * @param max      Max value to generate value up to.
     */
    
    void Init(vector<uint64_t> &primesIn, uint64_t max)
    {
        for (auto prime : primesIn)
        {
            primes.push_back(prime);
        }

        queue.insert(1);
        auto min = queue.begin();
       
        while (*min <= max && min != queue.end())
        {
            for (auto prime : primes)
            {
                if (*min * prime <= max)
                {
                    queue.insert(min, prime * (*min));
                }
            }

            min++;
        }
    }

    /**
     * triangleSum Get sum of triangle numbers indices that are k smooth. Loop
     * through N, and if N and N + 1 are k-smooth, so is N * (N + 1) / 2.
     *
     * @return Sum of k-smooth triangle numbers.
     */
    
    uint64_t triangleSum()
    {
        uint64_t sum = 0;
        uint64_t hits = 0;
        
        auto n1 = queue.begin();
        while (n1 != queue.end())
        {
            auto n2 = next(n1);
            
            if (*n2 == *n1 + 1)
            {
                hits++;
                cout << "Hit " << hits << ": " << *n1 << endl;
                sum += *n1;
            }

            n1++;
        }

        return sum;
    }
};

/**
 * PE581 - Genererate a the sum of all indices N such that N * (N + 1) / 2 is 47-smooth.
 *
 * Use the KSmoothGenerator class to genererate all KSmooth numbers up to 2 trillion. Then,
 * loop through the generated list looking for pairs of consecutive k-smooth values. These
 * are triangle numbers.
 *
 * @return Zero. Print sum to console.
 */

uint64_t PE581()
{
    vector<uint64_t> smallPrimes = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47 };
    uint64_t maxN = (uint64_t)2e12;
    KSmoothGenerator kgen;
    kgen.Init(smallPrimes, maxN);

    uint64_t sum = kgen.triangleSum();
    cout << sum << endl;

    __debugbreak();
    return 0;
}