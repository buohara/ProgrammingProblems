#include "commoninclude.h"

/** 
 * Direct calculation of P(f, r). Using sums of even and odd numbers (see problem description below).
 */

mpz_class PFR(mpz_class f, mpz_class r)
{
    mpz_class first;
    mpz_class out;

    if (f == 1)
    {
        first = 1;
        out = first + r * (r + 1) / 2 - 1;
        return out;
    }
    else if (f == 2)
    {
        first = 2;
    }
    else if (f % 2 == 0)
    {
        first = f * f / 2;
    }
    else
    {
        first = (f + 1) * (f - 1) / 2;
    }

    out = first;

    if (f % 2 == 1)
    {
        mpz_class k = r / 2;
        out += k * k;
        
        mpz_class n = (f - 1) + (r - 1) / 2;
        out += n * (n + 1);
        out -= f * (f - 1);
    }
    else
    {
        mpz_class k = (r - 1) / 2;
        out += k * (k + 1);
        
        mpz_class n = f + (r / 2);
        out += n * n;
        out -= f * f;
    }

    return out;
}

/** 
 * Initial code to compute who got which rooms on which floors. Brute force. Start with person 1, and
 * for person N, loop through floors checking if N + M is square. If no hits, stick them on a new floor.
 */

void debug359()
{
    vector<vector<uint32_t>> floors(2);

    floors[1].push_back(0);
    floors[1].push_back(1);

    vector<uint32_t> squares;

    for (uint32_t i = 1; i <= 300; i++)
    {
        squares.push_back(i * i);
    }

    for (uint32_t i = 2; i <= 300; i++)
    {
        bool newFloor = true;

        for (uint32_t floor = 1; floor < floors.size(); floor++)
        {
            uint32_t sum = i + floors[floor].back();

            if (find(squares.begin(), squares.end(), sum) != squares.end())
            {
                floors[floor].push_back(i);
                newFloor = false;
                break;
            }
        }

        if (newFloor == true)
        {
            vector<uint32_t> newFloor;
            floors.push_back(newFloor);
            floors.back().push_back(0);
            floors.back().push_back(i);
        }
    }
}

/**
 * PE351 - Hilbert's new hotel. In ascending order, a person N gets the first room on a floor 
 * such that the floor is empty, or if the last room went to person M, N + M is square. Let
 * P(f, r) be the number person that got room r on floor f. Compute the sum of all P(f, r) such
 * that f * r = 71328803586048.
 *
 * Basically, using the debug code above, I printed out P(f, r) for the first few hundred people.
 * Then looking at the patterns, figured out a way to directly compute P(f, r) for arbitrary f and r.
 *
 * The trick is looking at differences between person N - person M between rooms r + 1 and r. 
 * For example, on floor 4, the differences are:
 *
 * Floor 4 (first occupant is person 8): 9 2 11 4 13 6 15 8 17 10 19 12 21 14 23 16 25 18 27 20 ...
 * 
 * or rearranging, (2 4 6 8 10 12 ...) (9 11 13 15 17 ...)
 *
 * So use formulas for sums of even and odd numbers (k * (k + 1) and k^2) and add this to the
 * first occupant to get P(f, r). Use GMP for big integers.
 */

void PE359()
{
    // From trial division, 71,328,803,586,048 = (2^27) * (3^12) 

    uint64_t two27      = 134217728;    // 2^27
    uint64_t three12    = 531441;       // 3^12
    uint64_t max        = 71328803586048;

    uint64_t a = 1;
    mpz_class sum = 0;

    while (a <= two27)
    {
        uint64_t b = 1;

        while (b <= three12)
        {
            uint64_t r = a * b;
            uint64_t f = max / r;

            sum += PFR(f, r);
            b *= 3;
        }
        a *= 2;
    }

    printf("%s", sum.get_str().c_str());
}