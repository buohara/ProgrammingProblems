#include "utils.h"

/**
 * gcd - Compute greatest common divisor of integers 
 * a and b.
 *
 * @param a First value.
 * @param b Second value.
 *
 * @return Greatest common divisor of a and b.
 */

uint32_t gcd(uint32_t a, uint32_t b)
{
    uint32_t c;
    while (a != 0)
    {
        c = a;
        a = b % a;
        b = c;
    }
    return b;
}

/**
 * gcd64 - Compute greatest common divisor of 64 bit integers
 * a and b.
 *
 * @param a First value.
 * @param b Second value.
 *
 * @return Greatest common divisor of a and b.
 */

uint64_t gcd64(uint64_t a, uint64_t b)
{
    uint64_t c;
    while (a != 0) 
    {
        c = a; 
        a = b % a;
        b = c;
    }
    return b;
}

/**
 * gcdDbl - Compute greatest common divisor of doubles
 * a and b.
 *
 * @param a First value.
 * @param b Second value.
 *
 * @return Greatest common divisor of a and b.
 */

double gcdDbl(double a, double b)
{
    double c;
    while (a >= 0.1)
    {
        c = a;
        a = fmod(b, a);
        b = c;
    }
    return b;
}

/**
 * [gcdExtended description]
 * @param  a [description]
 * @param  b [description]
 * @param  x [description]
 * @param  y [description]
 * @return   [description]
 */

uint32_t gcdExtended(uint32_t a, uint32_t b, uint32_t &x, uint32_t &y)
{
    if (a == 0)
    {
        x = 0;
        y = 1;
        return b;
    }

    uint32_t x1;
    uint32_t y1;
    uint32_t gcd = gcdExtended(b % a, a, x1, y1);

    x = y1 - (b / a) * x1;
    y = x1;

    return gcd;
}

/**
 * [gcdExtended description]
 * @param  a [description]
 * @param  b [description]
 * @param  x [description]
 * @param  y [description]
 * @return   [description]
 */

int64_t gcdExtended(int64_t a, int64_t b, int64_t &x, int64_t &y)
{
    if (a == 0)
    {
        x = 0;
        y = 1;
        return b;
    }

    int64_t x1;
    int64_t y1;
    int64_t gcd = gcdExtended(b % a, a, x1, y1);

    x = y1 - (b / a) * x1;
    y = x1;

    return gcd;
}

/**
 * getContinuedFraction - Compute terms [a0, a1, ... , aN] in continued
 * fraction exansion of sqrt(A). Determine the period length and start
 * term for continued fraction.
 *
 * @param inVal Value to compute continued fraction expansion for.
 * @param terms (out) Vector to store computed continued fraction terms.
 * @param prd Computed period length of continued fraction.
 * @param prdStartIdx Index into terms where period begins.
 */

void getContinuedFraction(uint32_t inVal, continuedFrac &frac)
{
    double val = (double)inVal;
    val = sqrt(val);
    uint32_t a = (uint32_t)val;
    uint32_t a0 = a;
    uint32_t m = 0;
    uint32_t d = 1;

    // Check for perfect squares.

    if (val - (double)a == 0)
    {
        return;
    }

    frac.terms.push_back(a0);

    while (1)
    {
        m = d * a - m;
        d = (inVal - m * m) / d;
        a = (a0 + m) / d;

        frac.terms.push_back(a);

        if (a == 2 * a0)
        {
            frac.prd = (uint32_t)frac.terms.size() - 1;
            return;
        }
    }
}

/**
 * computeKConvergent - Compute the kth convergent for a continued fraction
 * a0 + 1 / ( a1 + 1 / ... ( a_(k-1) + 1 / a_k)). 
 * 
 * @param frac Terms [a0, a1, ..., ak] for continued fraction.
 * @param k Index of the convergent term to compute.
 * @param a (out) Numerator of convergent term.
 * @param b (out) Denominator of convergent term.
 */

void computeKConvergent(continuedFrac &frac, uint64_t k, uint64_t &a, uint64_t &b)
{
    // Return cases k = 0 or 1

    if (k == 0)
    {
        a = frac.terms[0];
        b = 1;
        return;
    }

    if (k == 1)
    {
        a = frac.terms[1] * frac.terms[0] + 1;
        b = frac.terms[1];
        return;
    }

    uint64_t prd = frac.prd;  
    
    uint64_t n0 = frac.terms[0];
    uint64_t n1 = frac.terms[1] * n0 + 1;
    uint64_t n2;

    uint64_t d0 = 1;
    uint64_t d1 = frac.terms[1];
    uint64_t d2;

    // Iteratively build up convergents via
    // n_n+2 = a_n+2 * n_n+1 + n_n

    for (uint64_t i = 2; i <= k; i++)
    {
        uint64_t newTerm = (uint64_t)frac.terms[(i - 1) % prd + 1];

        n2 = newTerm * n1 + n0;
        d2 = newTerm * d1 + d0;

        uint64_t c = gcd((uint32_t)n2, (uint32_t)d2);
        n2 /= c;
        d2 /= c;

        n0 = n1;
        n1 = n2;
        d0 = d1;
        d1 = d2;
    }

    // Done.

    a = n2;
    b = d2;
}

/**
 * computeKConvergentDouble - Compute the kth convergent for a continued fraction
 * a0 + 1 / ( a1 + 1 / ... ( a_(k-1) + 1 / a_k)).
 *
 * This is a hack double version of the uint64_t version above. Use doubles so we don't
 * overflow ints during iterations for large k.
 *
 * @param frac Terms [a0, a1, ..., ak] for continued fraction.
 * @param k Index of the convergent term to compute.
 * @param a (out) Numerator of convergent term.
 * @param b (out) Denominator of convergent term.
 */

void computeKConvergentDouble(continuedFrac &frac, uint64_t k, double &a, double &b)
{
    // Return cases k = 0 or 1

    if (k == 0)
    {
        a = frac.terms[0];
        b = 1;
        return;
    }

    if (k == 1)
    {
        a = frac.terms[1] * frac.terms[0] + 1;
        b = frac.terms[1];
        return;
    }

    uint32_t prd = frac.prd;

    double n0 = frac.terms[0];
    double n1 = frac.terms[1] * n0 + 1;
    double n2;

    double d0 = 1;
    double d1 = frac.terms[1];
    double d2;

    // Iteratively build up convergents.

    for (uint64_t i = 2; i <= k; i++)
    {
        uint64_t newTerm = (uint64_t)frac.terms[(i - 1) % prd + 1];

        n2 = newTerm * n1 + n0;
        d2 = newTerm * d1 + d0;

        n0 = n1;
        n1 = n2;
        d0 = d1;
        d1 = d2;
    }

    // Done.

    a = n2;
    b = d2;
}

/**
 * isPalindromic - Check if a number is palindromic (e.g., 12321 - yes, 12345 - no).
 *
 * @param value Check if this number is a palindrome.
 *
 * @return True if a palindrome, false otherwise.
 */

bool isPalindromic(uint32_t value)
{
    uint32_t digits[20];
    uint32_t numDigits = 0;

    while (value)
    {
        digits[numDigits++] = value % 10;
        value /= 10;
    }

    bool isPalindrome = true;

    for (uint32_t i = 0; i < numDigits / 2; i++)
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
 * isPalindromic64 - Check if 64 bit number is palindromin (e.g., 12321 - yes, 12345 - no).
 *
 * @param value Check if this number is a palindrome.
 *
 * @return True if a palindrome, false otherwise.
 */

bool isPalindromic64(uint64_t value)
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
 * powMod - Quickly compute b^e mod n.
 *
 * @param b Base value.
 * @param e Exponent.
 * @param n Modulus.
 * 
 * @return result of b^e mod n.
 */

uint32_t powMod(uint32_t b, uint32_t e, uint32_t n)
{
    uint32_t result = 1;
    while (e > 0)
    {
        if (e % 2 == 1)
        {
            result = (result * b) % n;
        }

        e = e >> 1;
        b = (b * b) % n;
    }
    return result;
}

/**
 * powMod64 - Quickly compute b^e mod n 64-bit uints.
 *
 * @param b Base value.
 * @param e Exponent.
 * @param n Modulus.
 *
 * @return result of b^e mod n.
 */

int64_t powMod64(int64_t b, int64_t e, int64_t n)
{
    int64_t result = 1;
    while (e > 0)
    {
        if (e % 2 == 1)
        {
            result = (result * b) % n;
        }

        e = e >> 1;
        b = (b * b) % n;
    }
    return result;
}

/**
 * numDigits - Get the number of digits in a number
 *
 * @param val The value to count digits of.
 *
 * @return Number of digits in val.
 */

uint32_t numDigits(uint32_t val)
{
    uint32_t digits = 0;

    while (val > 0)
    {
        val /= 10;
        digits++;
    }

    return digits;
}

/**
 * [cubicRoots Compute cubic roots of ax^3 + bx^2 + cx + d]
 * @param a     Coefficient a
 * @param b     Coefficient b
 * @param c     Coefficient c
 * @param d     Coefficient d
 * @param roots The three complex roots computed by this function.
 */

void cubicRoots(double a, double b, double c, double d, vector<complex<double>> &roots)
{
    double d0 = b * b - 3.0 * a * c;
    double d1 = 2.0 * b * b * b - 9.0 * a * b * c + 27.0 * a * a * d;

    complex<double> w1 = polar(1.0, 2.0 * M_PI / 3.0);
    complex<double> w2 = polar(1.0, 4.0 * M_PI / 3.0);

    double k = d1 * d1 - 4.0 * d0 * d0 * d0;
    complex<double> p;

    if (k >= 0.0)
    {
        p = 0.5 * (d1 + sqrt(k));
    }
    else
    {
        p = complex<double>(0.5 * d1, 0.5 *  sqrt(-k));
    }

    complex<double> r = pow(p , 1.0 / 3.0);

    complex<double> x1 = -(1.0 / (3.0 * a)) * (b + r + d0 / r);
    complex<double> x2 = -(1.0 / (3.0 * a)) * (b + w1 * r + d0 / (w1 * r));
    complex<double> x3 = -(1.0 / (3.0 * a)) * (b + w2 * r + d0 / (w2 * r));

    roots.push_back(x1);
    roots.push_back(x2);
    roots.push_back(x3);

    return;
}

/**
 * convertBase Convert digits from base b1 to base b2.
 *
 * @param digitsIn  Vector of input digits in base b1.
 * @param b1        Base of input digits.
 * @param digitsOut Output vector to hold digits in base b2.
 * @param b2        Base of output digits.
 */

void convertBase(
    vector<uint64_t> &digitsIn,
    uint64_t b1,
    vector<uint64_t> &digitsOut,
    uint64_t b2)
{
    uint64_t valBase10 = 0;
    uint64_t e1 = digitsIn.size() - 1;
    uint64_t e2 = 0;

    for (auto digit : digitsIn)
    {
        valBase10 += digit * pow(b1, e1--);
    }

    e1 = (uint64_t)(log(valBase10) / log(b2));

    while (valBase10)
    {
        e2 = (uint64_t)(log(valBase10) / log(b2));
        uint64_t newDigit = valBase10 / pow(b2, e2);

        if (e1 - e2 > 1)
        {
            for (uint64_t i = 0; i < e1 - e2 - 1; i++)
            {
                digitsOut.push_back(0);
            }
        }

        digitsOut.push_back(newDigit);
        valBase10 -= newDigit * pow(b2, e2);

        if (e2 > 0 && valBase10 == 0)
        {
            while (e2 > 0)
            {
                digitsOut.push_back(0);
                e2--;
            }
        }

        e1 = e2;
    }
}

/**
 * geomSum Compute geometric series 1 + r + r^2 ... + r^n
 *
 * @param  r Geometric series base.
 * @param  n Max N for geometric series.
 * @return   Sum of geometric series.
 */

uint64_t geomSum(uint64_t r, uint64_t n)
{
    return (pow(r, n + 1) - 1) / (r - 1);
}

/**
 * Get Milliseconds - CPU timer function. Get milliseconds elapsed since start of epoch.
 *
 * @return Milliseconds since start of epoch as 64bit int.
 */

long long GetMilliseconds()
{
    static LARGE_INTEGER frequency;
    static BOOL useQpc = QueryPerformanceFrequency(&frequency);

    if (useQpc)
    {
        LARGE_INTEGER now;
        QueryPerformanceCounter(&now);
        return (1000LL * now.QuadPart) / frequency.QuadPart;
    }
    else
    {
        return GetTickCount();
    }
}