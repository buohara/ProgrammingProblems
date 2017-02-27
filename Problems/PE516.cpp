#include "problems.h"

/**
 * generateHammingNumbers - Generate ordered sequence of numbers whose only
 * prime factors are 2, 3, and 5 up to a maximum value.
 *
 * @param max Stop searching for Hamming numbers past this value.
 * @param hammingNumber (out) List of generated Hamming numbers.
 */

void generateHammingNumbers(uint64_t max, vector<uint64_t> &hammingNumbers)
{
    hammingNumbers.push_back(1);

    uint32_t twoIdx     = 0;
    uint32_t threeIdx   = 0;
    uint32_t fiveIdx    = 0;

    uint64_t nextTwo    = 2;
    uint64_t nextThree  = 3;
    uint64_t nextFive   = 5;

    while (true)
    {
        // Check if we're past the limit and return;

        uint64_t last = hammingNumbers[hammingNumbers.size() - 1];
        if (last > max)
        {
            hammingNumbers.pop_back();
            return;
        }

        // Make sure all new candidate values are greater than the
        // last number we added.

        while (nextTwo <= last)
        {
            nextTwo = 2 * hammingNumbers[++twoIdx];
        }

        while (nextThree <= last)
        {
            nextThree = 3 * hammingNumbers[++threeIdx];
        }

        while (nextFive <= last)
        {
            nextFive = 5 * hammingNumbers[++fiveIdx];
        }

        // Add new numbers.

        if (nextTwo <= nextThree && nextTwo <= nextFive)
        {
            hammingNumbers.push_back(nextTwo);
            nextTwo = 2 * hammingNumbers[++twoIdx];
            continue;
        }

        if (nextThree <= nextTwo && nextThree <= nextFive)
        {
            hammingNumbers.push_back(nextThree);
            nextThree = 3 * hammingNumbers[++threeIdx];
            continue;
        }

        if (nextFive <= nextTwo && nextFive <= nextThree)
        {
            hammingNumbers.push_back(nextFive);
            nextFive = 5 * hammingNumbers[++fiveIdx];
            continue;
        }
    }
}

/**
 * getHammingPrimes - Generate primes whose Euler totient is a Hamming
 * number.
 *
 * @param hammingNumbers List of Hamming numbers to check.
 * @param primes List of primes to use for trial divisions in prime check.
 * @param hammingPrimes (out) Generated Hamming primes.
 */

void getHammingPrimes(
    vector<uint64_t> &hammingNumbers,
    vector<uint32_t> &primes,
    vector<uint64_t> &hammingPrimes
)
{
    for (uint32_t i = 0; i < hammingNumbers.size(); i++)
    {
        if (isPrime(hammingNumbers[i] + 1, primes) &&
            hammingNumbers[i] + 1 > 5)
        {
            hammingPrimes.push_back(hammingNumbers[i] + 1);
        }
    }
}

struct primeProduct
{
    uint64_t value;
    uint32_t lastFacIdx;
};

/**
 * PE516 - Find the sum mod 2^32 of all numbers N up to 10^12 such that
 * the Euler totient of N is a Hamming number (i.e., phi(N) = 2^i * 3^j * 5^k).
 *
 * @return Sum mod 2^32 of Ns with Hamming totients.
 */

uint64_t PE516()
{
    uint64_t max        = 1e12;
    uint64_t maxPrime   = 1e6;
    uint64_t sum        = 0;
    uint64_t modulus    = 0x100000000;

    // First, generate all Hamming numbers and primes whose
    // totients are Hamming numbers ("Hamming primes").

    vector<uint64_t> hammingNumbers;
    vector<uint64_t> hammingPrimes;
    vector<uint32_t> primes;

    generateHammingNumbers(max, hammingNumbers);
    primeSieve(maxPrime, primes);
    getHammingPrimes(hammingNumbers, primes, hammingPrimes);

    // Generate all combinations of products of Hamming primes less
    // than 1e12.

    vector<vector<primeProduct>> primeProducts(hammingPrimes.size() + 1);
    vector<uint64_t> products;
    products.push_back(1);

    for (uint32_t i = 0; i < hammingPrimes.size(); i++)
    {
        primeProduct newProduct;
        newProduct.value = hammingPrimes[i];
        newProduct.lastFacIdx = i;
        primeProducts[1].push_back(newProduct);
        products.push_back(newProduct.value);
    }

    for (uint32_t i = 1; i < primeProducts.size() - 1; i++)
    {
        for (uint32_t j = 0; j < primeProducts[i].size(); j++)
        {
            uint32_t nextIdx = primeProducts[i][j].lastFacIdx + 1;
            while (nextIdx < hammingPrimes.size() &&
                primeProducts[i][j].value * hammingPrimes[nextIdx] <= max)
            {
                primeProduct newProduct;
                newProduct.value = primeProducts[i][j].value * hammingPrimes[nextIdx];
                newProduct.lastFacIdx = nextIdx;
                primeProducts[i + 1].push_back(newProduct);
                products.push_back(newProduct.value);
                nextIdx++;
            }
        }
    }

    sort(products.begin(), products.end());

    // Finally, multiply all Hamming numbers with Hamming primes to
    // get the final sum.

    for (uint32_t i = 0; i < hammingNumbers.size(); i++)
    {
        for (uint32_t j = 0; j < products.size(); j++)
        {
            uint64_t newProduct = hammingNumbers[i] * products[j];

            if (newProduct > max)
            {
                break;
            }

            sum += newProduct;
            sum %= modulus;
        }
    }

    return sum;
}