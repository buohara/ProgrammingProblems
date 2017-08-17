#include "problems.h"

/**
 * getConnections - Given a prime value, replace all its digits and add/remove
 * digits on the left to generate edges for PE 425.
 *
 * @param val         Value to generate connections for.
 * @param connections Vector to hold connections found for val.
 * @param primes      List of prime numbers up to a maximum value.
 * @param isPrime     Boolean vector to quickly look up whether a new value is a prime.
 */

void getConnections(
    uint32_t val,
    vector<uint32_t> &connections,
    vector<uint32_t> &primes,
    vector<bool> &isPrime
)
{
    uint32_t tmp = val;
    vector<uint32_t> digits;
    vector<uint32_t> pwrs = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000 };

    while (tmp > 0)
    {
        digits.push_back(tmp % 10);
        tmp /= 10;
    }

    // Replace individual digits.

    for (uint32_t i = 0; i < digits.size(); i++)
    {
        for (uint32_t j = 0; j < 10; j++)
        {
            // Except for 2, primes can't be even.

            if (digits.size() > 1 && i == 0 && j % 2 == 0)
            {
                continue;
            }

            // Don't replace the highest power digit with 0.

            if (i == digits.size() - 1 && j == 0)
            {
                continue;
            }

            // Don't replace a digit with itself.

            if (j == digits[i])
            {
                continue;
            }

            uint32_t newVal = 0;
            newVal += j * pwrs[i];

            for (uint32_t k = 0; k < digits.size(); k++)
            {
                if (k == i)
                {
                    continue;
                }

                newVal += digits[k] * pwrs[k];
            }

            if (isPrime[newVal])
            {
                connections.push_back(newVal);
            }
        }
    }

    // Add/remove digits to/from the left.

    uint32_t pwr = pwrs[digits.size()];

    for (uint32_t i = 1; i < 10; i++)
    {
        uint32_t newVal = pwr * i + val;

        if (newVal > primes.back())
        {
            break;
        }

        if (isPrime[newVal])
        {
            connections.push_back(newVal);
        }
    }

    uint32_t pwr2 = pwr / 10;

    if (pwr2 > 0)
    {
        uint32_t newVal = val % pwr2;

        if (newVal > pwr2 / 10 && isPrime[newVal])
        {
            connections.push_back(newVal);
        }
    }

    return;
}

/**
 * GetMinPathValues - Using the connection rules for this problem, trace paths between
 * 2 and other nodes in the graph, minimizing the maximum value encountered along each path
 *
 * @param primes      A list of primes up to whatever max value we're searching to.
 * @param connections A map of each prime and the other primes it's connected to (graph edges).
 * @param maxPathVals Map for the minimum max value encountered between 2 and other primes.
 */

void GetMinPathValues(
    vector<uint32_t> &primes,
    map<uint32_t, vector<uint32_t>> &connections,
    map<uint32_t, uint32_t> &maxPathVals
)
{
    priority_queue<uint32_t, vector<uint32_t>, greater<uint32_t>> nextCxns;
    
    nextCxns.push(2);
    maxPathVals[2] = 0;

    while (!nextCxns.empty())
    {
        uint32_t cur = nextCxns.top();
        nextCxns.pop();

        uint32_t curMax = cur;

        if (maxPathVals[cur] > cur)
        {
            curMax = maxPathVals[cur];
        }

        vector<uint32_t> &curCxns = connections[cur];

        for (auto cxn : curCxns)
        {
            uint32_t cxnMax = maxPathVals[cxn];
            
            if (cxnMax == 0 || curMax < cxnMax)
            {
                maxPathVals[cxn] = curMax;
                nextCxns.push(cxn);
            }
        }
    }
}

/**
 * PE425 - Two numbers are connected if they differ only in one digit or have
 * any digit appended/removed to/from the left. A prime p is related to 2 if a chain of
 * such connections can be found between 2 and p and p is the biggest number in the chain.
 *
 * This one tripped me up for a bit because I'm not good with graph algorithms. Creating a
 * function to generate connections was easy. In a first, attempt, I tried visiting each node
 * and descending along chains of connections less than that node's value. This worked for
 * small values of N, but way too slow for 10^7.
 *
 * I knew that I was finding optimal paths between 2 and other nodes, which made me think
 * Djikstra's algorithm. It took me a while to get it straight that I was minimizing the max
 * path value for each node. This is what the final solution does.
 *
 * Start at 2 and set its max path val to 0. Grab its minimum connection, 3. The max val for
 * 3 will be the greater of 2 and the minimum distance to 2, or max(2, 0) = 2. Store this value
 * and push its connections onto a queue of connections to visit. Grab the next smallest value from
 * the queue and repeat. If we bump into a node again along a path with smaller max value, put
 * that node back into the queue so we can update its connections.
 *
 * Once that's done, loop through primes and sum that ones that weren't reached or whose max path val
 * is greater than that prime.
 *
 * @return [description]
 */

uint64_t PE425()
{
    vector<uint32_t> primes;
    const uint32_t max = (uint32_t)1e7;

    primeSieve(max, primes);
    uint64_t sum = 0;
    vector<bool> isPrime(10 * max, false);

    for (auto i : primes)
    {
        isPrime[i] = true;
    }

    map<uint32_t, uint32_t> maxPathVals;
    map<uint32_t, vector<uint32_t>> connections;
    
    for (uint32_t i = 0; i < primes.size(); i++)
    {
        vector<uint32_t> curConnections;
        getConnections(primes[i], curConnections, primes, isPrime);
        connections[primes[i]] = curConnections;
    }

    GetMinPathValues(primes, connections, maxPathVals);

    for (auto prime : primes)
    {
        if (maxPathVals[prime] == 0 || maxPathVals[prime] > prime)
        {
            sum += (uint64_t)prime;
        }
    }

    printf("%llu\n", sum);
    __debugbreak();
    return 0;
}