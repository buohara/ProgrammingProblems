#include "problems.h"

/**
 * isPalindromic - Check if a number is palindromin (e.g., 12321 - yes, 12345 - no).
 *
 * @param value Check if this number is a palindrome.
 *
 * @return True if a palindrome, false otherwise.
 */

bool isPalindromic(uint64_t value)
{
    uint64_t digits[20];
    uint64_t numDigits = 0;

    while (value)
    {
        digits[numDigits++] = value % 10;
        value /= 10;
    }

    bool isPalindrome = true;

    for (uint64_t i = 0; i < numDigits / 2; i++)
    {
        if (digits[i] != digits[numDigits - i - 1])
        {
            isPalindrome = false;
            break;
        }
    }

    return isPalindrome;
}

/**
 * PE125 - Sum the numbers less than 1e8 that are both palindromic and the sum
 * of consecutive squares.
 *
 * Pretty straightforward. One gotcha I missed was checking if I'd already
 * encountered a palindrome (it can be written as the sum of squares in more than
 * one way). I added a palindromes vector to store all the ones found during search
 * to make sure nothing gets double-counted.
 */

uint64_t PE125()
{
    const uint64_t max = 1e8;
    const uint64_t maxSq = 1e4;
    uint64_t sum = 0;

    vector<uint64_t> squares;
    vector<uint64_t> palindromes;
    squares.resize(maxSq + 1);

    for (uint64_t i = 1; i <= maxSq; i++)
    {
        squares[i] = i * i;
    }

    for (uint64_t i = 1; i <= maxSq; i++)
    {
        uint64_t sqSum = 0;

        for (uint64_t j = i; j <= maxSq; j++)
        {
            sqSum += squares[j];
            if (sqSum > max)
            {
                break;
            }

            if (isPalindromic(sqSum) && (j != i) && 
                find(palindromes.begin(), palindromes.end(), sqSum) == palindromes.end())
            {
                sum += sqSum;
                palindromes.push_back(sqSum);
            }
        }
    }

    return sum;
}