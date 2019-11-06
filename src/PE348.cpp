#include "commoninclude.h"

/**
 * PE348 - Find the sum of the first give numbers that are palindromic and can
 * be written as squbes in 4 different ways.
 *
 * Straight-forward search. Generate cubes and squares, add them, check if they are
 * a palindrome, and store them if so. If we hit them again later, increment their sqube count.
 * When the sqube count hits 4, store it as a 4-sqube. Sort the list of 4-squbes and add
 * the minimum 5.
 */

void PE348()
{
    uint64_t maxSquares = (uint64_t)1e5;
    uint64_t maxCubes = (uint64_t)1e4;

    vector<uint64_t> squares;
    vector<uint64_t> cubes;
    map<uint64_t, uint64_t> squbes;
    vector<uint64_t> fourSqubes;

    uint64_t result = 0;
    uint64_t idx = 0;

    for (uint64_t i = 2; i <= maxSquares; i++)
    {
        squares.push_back(i * i);
    }

    for (uint64_t i = 2; i <= maxCubes; i++)
    {
        cubes.push_back(i * i * i);
    }

    for (uint64_t i = 0; i < cubes.size(); i++)
    {
        for (uint64_t j = 0; j < squares.size(); j++)
        {
            uint64_t sqube = cubes[i] + squares[j];

            if (isPalindromic64(cubes[i] + squares[j]))
            {       
                if (squbes.find(sqube) == squbes.end())
                {
                    squbes[sqube] = 1;
                }
                else
                {
                    squbes[sqube]++;

                    if (squbes[sqube] == 4)
                    {
                        fourSqubes.push_back(sqube);
                        printf("%llu: %llu^2 + %llu^3\n", sqube, j + 2, i + 2);
                    }
                }
            }
        }
    }

    sort(fourSqubes.begin(), fourSqubes.end());

    for (uint64_t i = 0; i < 5; i++)
    {
        result += fourSqubes[i];
    }

    printf("%llu\n", result);
}