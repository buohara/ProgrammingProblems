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
        if (scratch[i] == 1)
        {
            continue;
        }

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
 * primeSieve - Prime sieve, 64-bit version.
 * 
 * @param max Generate all prime numbers up to this value.
 * @param primes (out) A list of all the primes found.
 */

void primeSieve(uint64_t max, vector<uint64_t> &primes)
{
    vector<uint64_t> scratch;
    assert(max / 2 < scratch.max_size());
    scratch.resize(max + 1, 0);

    scratch[0] = 1;
    scratch[1] = 1;

    uint64_t primeCnt = 0;

    // Starting at 2, loop through multiples of numbers and mark 
    // them as composite.

    for (uint64_t i = 2; i <= max / 2; i++)
    {
        if (scratch[i] == 1)
        {
            continue;
        }

        uint64_t factor = 2 * i;
        while (factor <= max)
        {
            scratch[factor] = 1;
            factor += i;
        }
    }

    // Count how many primes are left over.

    for (uint64_t i = 1; i <= max; i++)
    {
        if (scratch[i] == 0)
        {
            primeCnt++;
        }
    }

    // Put them in the output vector and done.

    primes.resize(primeCnt);

    for (uint64_t i = 1, j = 0; i <= max; i++)
    {
        if (scratch[i] == 0)
        {
            primes[j++] = i;
        }
    }
}

/**
 * primeSieve - Use sieving to generate a list of primes betwee
 * a min and max value, inclusive.
 *
 * @param min Generate primes including and above this value.
 * @param max Generate all prime numbers up to and including this value.
 * @param primes (out) A list of all the primes found.
 */

void primeSieve(uint32_t min, uint32_t max, vector<uint32_t> &primes)
{
    vector<uint32_t> scratch;
    scratch.resize(max - min + 1, 0);

    uint32_t primeCnt = 0;

    for (uint32_t i = 2; i <= max / 2; i++)
    {
        uint32_t factor = (min / i) * i;
        factor = 2 * i > factor ? 2 * i : factor;
        
        if (factor < min)
        {
            factor += i;
        }

        while (factor <= max)
        {
            scratch[factor - min] = 1;
            factor += i;
        }
    }

    // Count how many primes are left over.

    for (uint32_t i = 0; i <= max - min; i++)
    {
        if (scratch[i] == 0)
        {
            primeCnt++;
        }
    }

    // Put them in the output vector and done.

    primes.resize(primeCnt);

    for (uint32_t i = 0, j = 0; i <= max - min; i++)
    {
        if (scratch[i] == 0)
        {
            primes[j++] = i + min;
        }
    }
}

/**
 * primeSieve - Same as above, but put primes in a hash table
 * for quicker lookup.
 *
 * @param max Generate all prime numbers up to this value.
 * @param primes (out) A list of all the primes found.
 */

void primeSieve(uint32_t max, unordered_set<uint32_t> &primes)
{
    vector<uint32_t> scratch(max + 1);

    scratch[0] = 1;
    scratch[1] = 1;

    uint32_t primeCnt = 0;

    // Starting at 2, loop through multiples of numbers and mark 
    // them as composite.

    for (uint32_t i = 2; i <= max / 2; i++)
    {
        if (scratch[i] == 1)
        {
            continue;
        }

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

    for (uint32_t i = 1, j = 0; i <= max; i++)
    {
        if (scratch[i] == 0)
        {
            primes.insert(i);
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

/**
 * writePrimesToFile - Write computed primes to a file.
 *
 * @param fileName Name of output file.
 * @param primes List of primes to write to file.
 */

void writePrimesToFile(const char* fileName, vector<uint32_t> &primes)
{
    ofstream primeFile;
    primeFile.open(fileName);
    
    for (uint32_t i = 0; i < primes.size(); i++)
    {
        primeFile << primes[i] << " ";
        if (i > 0 && i % 100 == 0)
        {
            primeFile << "\n";
        }
    }

    primeFile.close();
}

/**
 * readPrimesFromFile - Write computed primes to a file.
 *
 * @param fileName Name of input file.
 * @param primes List of primes to populate from file.
 * @param max Read in all primes less than or equal to this max value. If zero,
 * read all primes from file.
 */

void readPrimesFromFile(const char* fileName, vector<uint32_t> &primes, uint32_t max)
{
    uint32_t exponent = 0;
    uint32_t tmpMax = max / 10;

    while (tmpMax)
    {
        exponent++;
        tmpMax /= 10;
    }

    uint32_t numPrimes = primePi(exponent);
    primes.resize(numPrimes + 1);

    ifstream primeFile;
    string line;
    primeFile.open(fileName);
    uint32_t inPrime;
    uint32_t i = 0;

    while (!primeFile.eof())
    {
        primeFile >> inPrime;
        if (inPrime > max)
        {
            primeFile.close();
            return;
        }

        primes[i++] = inPrime;
    }

    primeFile.close();
}

/**
 * readPrimesFromFile - Same as above, but read primes into a hash table.
 *
 * @param fileName Name of input file.
 * @param primes List of primes to populate from file.
 * @param max Read in all primes less than or equal to this max value. If zero,
 * read all primes from file.
 */

void readPrimesFromFile(const char* fileName, unordered_set<uint32_t> &primes, uint32_t max)
{
    uint32_t exponent = 0;
    uint32_t tmpMax = max / 10;

    while (tmpMax)
    {
        exponent++;
        tmpMax /= 10;
    }

    uint32_t numPrimes = primePi(exponent);
    primes.reserve(numPrimes + 1);

    ifstream primeFile;
    primeFile.open(fileName);
    uint32_t inPrime;

    while (!primeFile.eof())
    {
        primeFile >> inPrime;
        if (inPrime > max)
        {
            primeFile.close();
            return;
        }

        primes.insert(inPrime);
    }

    primeFile.close();
}

/**
 * primePi - Return number of primes up to 10^exponent.
 *
 * @param exponent Value of exponent for pi(10^exponent).
 *
 * @return Number of primes up to 10^exponent.
 */

uint32_t primePi(uint32_t exponent)
{
    const uint32_t piVals[11] =
    {
        0,
        4,
        25,
        168,
        1229,
        9592,
        78498,
        664579,
        5761455,
        50847534,
        455052511
    };

    return piVals[exponent];
}

/**
 * factorSieve - Perform a prime sieve while storing prime factorizations
 * as we go.
 *
 * @param max Max value to factor.
 * @param values Out. A list from 0 - max with prime factorizations. 
 */

void factorSieve(uint32_t max, vector<vector<primePower>> &values)
{
    values.resize(max + 1);
    values[1].push_back({ 1, 1 });

    for (uint32_t i = 2; i <= max; i++)
    {
        if (values[i].size() == 0)
        {
            values[i].push_back({ i, 1 });
            
            uint32_t tmp = 2 * i;

            while (tmp <= max)
            {
                uint32_t tmp2 = tmp;
                uint32_t pwr = 0;

                while (tmp2 % i == 0)
                {
                    pwr++;
                    tmp2 /= i;
                }

                values[tmp].push_back({ i, pwr });
                tmp += i;
            }
        }
    }
}

/**
 * [factorTrialDivision Get prime factors of a value by trial division.]
 * @param primes  A list of primes to do trival division with.
 * @param factors Out list of prime powers of value.
 * @param value   Value to get prime factorization for.
 */

void factorTrialDivision(vector<uint32_t> &primes, vector<primePower> &factors, uint64_t value)
{
    for (uint32_t i = 0; i < primes.size(); i++)
    {
        uint64_t curPrime = (uint64_t)primes[i];

        if (value % curPrime == 0)
        {
            primePower newFactor;
            newFactor.prime = (uint32_t)curPrime;
            newFactor.power = 0;

            while (value % curPrime == 0)
            {
                newFactor.power++;
                value /= curPrime;
            }

            factors.push_back(newFactor);
        }

        if (value == 1)
        {
            return;
        }
    }
}