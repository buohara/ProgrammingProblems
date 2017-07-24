#include "problems.h"

struct frogNode
{
    frac probP;
    frac probN;
};

/**
 * PE329 - Prime frog Problem. 
 *
 * Use MPIR for handling large integers. Iteratively solve the probability that 
 * each title 1-500 is P or N given the previous sequence of hops. Use the recursion
 * P[N][C][K] = (1/2) * F(C, K) * (P[N - 1][K - 1] + P[N - 1][K + 1]). N is the iteration number
 * (1 - 15), K is the tile index (1 - 500), C is whether this iteration is 'PRIME' or 
 * 'NOT PRIME', F(C, K) is 2/3 or 1/3 depending on whether K is prime. Adjust formula at boundaries
 * (e.g., remove the 1/2 factor from tile 1 when computing tile 2's probability). 
 */

uint32_t PE329()
{
    const uint32_t max = 500;
    vector<uint32_t> primes;
    primeSieve(max + 1, primes);

    vector<frogNode> nodes(max + 1);
    vector<frac> curProb(max + 1);
    vector<frac> nextProb(max + 1);

    vector<char> searchString = 
    { 'P', 'P', 'P', 'P', 'N', 'N', 'P', 'P', 'P', 'N', 'P', 'P', 'N', 'P', 'N' };
    
    frac half = { 1, 2 };
    frac resultProb = { 0, 1 };

    // Initialize random probabilities of starting at any node and croaking 'P'

    for (uint32_t i = 1; i <= max; i++)
    {
        curProb[i] = { 1, max };

        if (find(primes.begin(), primes.end(), i) == primes.end())
        {
            nodes[i].probP = { 1, 3 };
            nodes[i].probN = { 2, 3 };
        }
        else
        {
            nodes[i].probP = { 2, 3 };
            nodes[i].probN = { 1, 3 };
        }

        curProb[i] *= nodes[i].probP;
    }

    for (uint32_t i = 1; i < searchString.size(); i++)
    {
        for (uint32_t j = 1; j < nodes.size(); j++)
        {
            frac croakProb;

            if (searchString[i] == 'P')
            {
                croakProb = nodes[j].probP;
            }
            else
            {
                croakProb = nodes[j].probN;
            }

            if (j == 1)
            {
                nextProb[j] = half * croakProb * curProb[2];
            }
            else if (j == 2)
            {
                nextProb[j] = croakProb * curProb[1] + half * croakProb * curProb[3];
            }
            else if (j == 499)
            {
                nextProb[j] = croakProb * curProb[500] + half * croakProb * curProb[498];
            }
            else if (j == 500)
            {
                nextProb[j] = half * croakProb * curProb[499];
            }
            else
            {
                nextProb[j] = half * croakProb * curProb[j - 1] + half * croakProb * curProb[j + 1];
                //nextProb[j] = half * croakProb * (curProb[j - 1] + curProb[j + 1]);
            }
        }

        for (uint32_t j = 1; j < nodes.size(); j++)
        {
            curProb[j] = nextProb[j];
        }
    }

    for (uint32_t i = 1; i < nodes.size(); i++)
    {
        resultProb += curProb[i];
    }

    return 0;
}