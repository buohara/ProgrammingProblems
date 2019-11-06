#include "commoninclude.h"

struct triple
{
    uint64_t a;
    uint64_t b;
    uint64_t c;
};

/**
 * PE75 - Count the values L <=1,500,000 that can be written as the sum of prime triples
 * a, b, and c in exactly one way.
 * 
 * This is another clunky solution. It generates all prime triples that sum up to
 * 1,500,000 using Euclid's formula, removing duplicates along the way. When done, count
 * all the lengths where only one triple was found.
 */

uint64_t PE75()
{
    uint64_t maxLength = 1500000;
    uint64_t maxM = 867;
    uint64_t sum = 0;

    vector<vector<triple>> triples(maxLength + 1);

    for (uint64_t i = 2; i < maxM; i++)
    {
        for (uint64_t j = 1; j < i; j++)
        {
            // Generate a triple with Euclid's formula.

            uint64_t a = i * i - j * j;
            uint64_t b = 2 * i * j;
            uint64_t c = i * i + j * j;

            uint64_t k = 1;
            uint64_t length = k * (a + b + c);

            // Keep taking multiples k * (a, b, c) to generate more
            // triples.

            while (length <= maxLength)
            {
                triple newTriple = { k * a, k * b, k * c };
                bool bTripleExists = false;

                // Order the triples such that a <= b.

                if (newTriple.b < newTriple.a)
                {
                    uint64_t tmp = newTriple.a;
                    newTriple.a = newTriple.b;
                    newTriple.b = tmp;
                }

                // Check if we found this triple already, continue if so.

                for (uint64_t s = 0; s < triples[length].size(); s++)
                {
                    if (triples[length][s].a == newTriple.a &&
                        triples[length][s].b == newTriple.b &&
                        triples[length][s].c == newTriple.c)
                    {
                        bTripleExists = true;
                        break;
                    }
                }

                if (bTripleExists == true)
                {
                    k++;
                    length = k * (a + b + c);
                    continue;
                }

                triples[length].push_back(newTriple);

                k++;
                length = k * (a + b + c);
            }
        }
    }

    for (uint64_t i = 1; i <= maxLength; i++)
    {
        if (triples[i].size() == 1)
        {
            sum++;
        }
    }

    return sum;
}