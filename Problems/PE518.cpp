#include "problems.h"

/**
 * PE518 - Find the sum of prime triplets (a, b, c) with
 * a < b < c < N, N = 1e8, and each (a + 1, b + 1, c + 1) is 
 * a geometric progression.
 *
 * This code is slow (~7 mins, debug build on a Core i7-5930K).
 */

uint64_t PE518()
{
    uint32_t max = 1e8;
    uint64_t sum = 0;

    // Load all primes up to 1e8 into a hash table for faster lookup
    // when searching begins. Hashing all the primes up to 1e8 takes ~1 minute.

    vector<uint32_t> primes;
    readPrimesFromFile("primes.txt", primes, max);
    unordered_set<uint32_t> hashedPrimes;
    hashedPrimes.reserve(primes.size());

    for (uint32_t i = 0; i < primes.size(); i++)
    {
        hashedPrimes.insert(primes[i]);
    }

    // Compute all square numbers up to 1e8 for determining search
    // ranges later.

    const uint32_t numSquares = 10001;
    uint32_t squares[numSquares];

    for (uint32_t i = 1; i < numSquares; i++)
    {
        squares[i] = i * i;
    }

    // This method takes every prime p, determines factors (a/b), and
    // computes triples (p + 1), (a/b) * (p + 1), (a/b)^2 * (p + 1).
    // If (a/b) * (p + 1) - 1 and (a/b)^2 * (p + 1) - 1 are each prime
    // (i.e., they're in the hash table of known primes), we've found a triple.
    //
    // The expensive part is searching (a/b) candidates. They are determined
    // with the inequality b < a < b * sqrt (1e8 + 1 / p + 1). The bs must satisfy
    // b^2 | (p + 1) (since the third prime in a triple is of the form
    // (a/b)^2 * (p + 1) - 1), so pick the largest b that satisfies this condition.

    for (uint32_t i = 0; i < primes.size() - 2; i++)
    {
        uint32_t b = 1;
        uint32_t p = primes[i] + 1;

        // Find largest b where b^2 | (p + 1).

        for (uint32_t j = 2; squares[j] <= p; j++)
        {
            while (p % squares[j] == 0)
            {
                b *= j;
                p /= squares[j];
            }
        }

        p = primes[i] + 1;

        // Compute search range [b, b * sqrt (1e8 + 1 / p + 1)]

        double num = (double)(max + 1);
        double amaxd = (double)b * sqrt(num / (double)p);
        uint32_t amax = (uint32_t)amaxd + 1;
        
        // Loop over all as in the search range. Check if the numbers found are prime,
        // and add to the sum if a triple is found.

        for (uint32_t a = b + 1; a < amax; a++)
        {
            uint32_t p2 = (p / b) * a - 1;
            uint32_t p3 = (p / (b * b)) * a * a - 1;
            
            if (hashedPrimes.find(p2) != hashedPrimes.end() &&
                hashedPrimes.find(p3) != hashedPrimes.end())
            {
                sum += (p - 1) + p2 + p3;
            }
        }
    }

    return sum;
}