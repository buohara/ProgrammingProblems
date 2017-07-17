#include "problems.h"

uint64_t PE203()
{
    const uint64_t maxRows = 51;
    const uint32_t maxPrime = 1000000;
    uint64_t sum = 0;

    vector<uint64_t> rows[maxRows + 1];
    vector<uint64_t> distincts;
    distincts.push_back(1);

    rows[1].push_back(1);
    rows[2].push_back(1);
    rows[2].push_back(1);

    // Populate prime squares

    vector<uint32_t> primes;
    vector<uint64_t> primeSquares;

    primeSieve(maxPrime, primes);

    for (uint32_t i = 0; i < primes.size(); i++)
    {
        uint64_t prime = (uint64_t)primes[i];
        primeSquares.push_back(prime * prime);
    }

    // Build Pascal's triangle and store distinct values.

    for (uint64_t i = 3; i <= maxRows; i++)
    {
        rows[i].push_back(1);
        
        for (uint64_t j = 1; j < rows[i - 1].size(); j++)
        {
            uint64_t c1 = rows[i - 1][j];
            uint64_t c2 = rows[i - 1][j - 1];
            rows[i].push_back(c1 + c2);

            if (find(distincts.begin(), distincts.end(), c1 + c2) == distincts.end())
            {
                distincts.push_back(c1 + c2);
            }
        }

        rows[i].push_back(1);
    }

    // Filter out square-free values from Pascal's triangle

    for (uint32_t i = 0; i < distincts.size(); i++)
    {
        uint64_t distinct = distincts[i];
        bool squareFree = true;

        for (uint32_t j = 0; j < primeSquares.size(); j++)
        {
            uint64_t square = primeSquares[j];
            
            if (square > distinct)
            {
                break;
            }

            if (distinct % square == 0)
            {
                squareFree = false;
                break;
            }
        }

        if (squareFree == true)
        {
            sum += distinct;
        }
    }

    __debugbreak();
    return 0;
}