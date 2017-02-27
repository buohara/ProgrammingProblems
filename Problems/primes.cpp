#include "primes.h"

/**
 * primeSieve - Generate a list of prime numbers up to a maximum value.
 * Use a simple sieve: mark off multiples starting at 2, and whatever's
 * left is prime.
 *
 * @param max Generate all prime numbers up to this value.
 * @param primes (out) A list of all the primes found.
 */

void primeSieve(uint32_t max, vector<uint32_t> &primes)
{
    vector<uint32_t> scratch;
    assert(max / 2 < scratch.max_size());
    scratch.resize(max + 1, 0);

    scratch[0] = 1;
    scratch[1] = 1;

	uint32_t primeCnt = 0;

    // Starting at 2, loop through multiples of numbers and mark 
    // them as composite.

	for (uint32_t i = 2; i <= max / 2; i++)
	{
		uint32_t factor = 2 * i;
		while (factor <= max)
		{
			scratch[factor] = 1;
			factor += i;
		}
	}

    // Count how many primes are left over.

	for (uint32_t i = 1; i <= max; i++)
	{
        if (scratch[i] == 0)
        {
            primeCnt++;
        }
	}

    // Put them in the output vector and done.

    primes.resize(primeCnt);

	for (uint32_t i = 1, j = 0; i <= max; i++)
	{
        if (scratch[i] == 0)
        {
            primes[j++] = i;
        }
	}
}

/**
 * isPrime - Check if a number is prime by trial division.
 *
 * @param value Value to check for primality.
 * @param primes List of primes to use for trial divisions.
 *
 * @return True if input is prime, false otherwise.
 */

bool isPrime(uint64_t value, vector<uint32_t> &primes)
{
    uint32_t i = 0;
    uint64_t curPrime = (uint64_t)primes[i];

    while (curPrime * curPrime <= value && i < primes.size())
    {
        if (value % curPrime == 0)
        {
            return false;
        }

        i++;
        curPrime = (uint64_t)primes[i];
    }

    return true;
}