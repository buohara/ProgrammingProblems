#include "commoninclude.h"

/**
 * PE68 - Magic 5-gon ring. Find the maximum 16-digit string that solves a "magic"
 * 5-gon ring. Go to the website for problem details.
 *
 * This solution is clunky, but works. It works by just taking all permutations of 
 * digits 1-10 into nodes of the 5-gon ring. When checking permutations, ignore those
 * where 10 is on the inner ring, since such a solution string must have 17 digits. 
 * For each valid permutation, check if all the lines sum to the same value. If so, and the
 * result string is greater than the best so far, make this string the new best string.
 */

uint64_t PE68()
{
    // Initialize some data.

    vector<uint64_t> digits(10);
    uint64_t maxString = 0;

    for (uint64_t i = 0; i < 10; i++)
    {
        digits[i] = i + 1;
    }

    uint64_t triples[5][3] =
    {
        0, 5, 6,
        1, 6, 7,
        2, 7, 8,
        3, 8, 9,
        4, 9, 5
    };

    // Keep permuting digits 1-10 into the 5-gon positions. If a solution
    // is found, check if its string is the best 16-digit solution so far.

    do
    {
        // Find the index of the node on the outer ring with lowest value
        // for starting position. Check for 10s along the way - if there's no
        // 10 in the outer ring, 10 will get counted twice and possible solutions will 
        // have 17 digits, so ignore.

        uint64_t lowIdx = 0;
        vector<uint64_t> solutionSet;
        bool bTenFound = (digits[lowIdx] == 10);

        for (uint64_t i = 1; i <= 4; i++)
        {
            if (digits[i] < digits[lowIdx])
            {
                lowIdx = i;
            }

            if (digits[i] == 10)
            {
                bTenFound = true;
            }
        }

        if (bTenFound == false)
        {
            continue;
        }

        uint64_t lineSum = 0;
        bool bContinue = false;

        // Grab the sums of each line in the 5-gon.

        for (uint64_t i = 0; i < 5; i++)
        {
            uint64_t tripleIdx = lowIdx + i;
            
            if (tripleIdx > 4)
            {
                tripleIdx %= 5;
            }

            uint64_t tripleSum = digits[triples[tripleIdx][0]] +
                digits[triples[tripleIdx][1]] +
                digits[triples[tripleIdx][2]];

            solutionSet.push_back(digits[triples[tripleIdx][0]]);
            solutionSet.push_back(digits[triples[tripleIdx][1]]);
            solutionSet.push_back(digits[triples[tripleIdx][2]]);

            // If this is the first line store its sum.

            if (i == 0)
            {
                lineSum = tripleSum;
            }

            // If this is line 2-5, make sure it matches the first line.

            else
            {
                if (tripleSum != lineSum)
                {
                    bContinue = true;
                    break;
                }
            }
        }

        // Go to the next permutation if line sums don't form a solution.

        if (bContinue == true)
        {
            continue;
        }

        uint64_t pow = 1;
        uint64_t curString = 0;
        uint64_t digits = 0;

        for (uint64_t i = 0; i < 15; i++) 
        {
            curString += solutionSet[15 - i - 1] * pow;
            if (solutionSet[15 - i - 1] == 10)
            {
                pow *= 100;
                digits += 2;
            }
            else
            {
                pow *= 10;
                digits++;
            }
        }

        if (curString > maxString && digits == 16)
        {
            maxString = curString;
        }

    } 
    while (next_permutation(digits.begin(), digits.end()) == true);

    return maxString;
}