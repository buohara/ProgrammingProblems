#pragma once

#define _USE_MATH_DEFINES

#include <stdint.h>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <string>
#include <math.h>
#include <assert.h>
#include <complex>
#include <cmath>
#include "mpirxx.h"

using namespace std;

struct continuedFrac
{
    vector<uint32_t> terms;
    uint32_t prd;
};

struct frac
{
    mpz_class num;
    mpz_class den;

    frac& operator=(const frac &rhs)
    {
        num = rhs.num;
        den = rhs.den;
        return *this;
    }

    frac& operator+=(const frac &rhs)
    {
        num = num * rhs.den + rhs.num * den;
        den = den * rhs.den;

        mpz_class c;
        mpz_gcd(c.get_mpz_t(), num.get_mpz_t(), den.get_mpz_t());
        num /= c;
        den /= c;

        return *this;
    }

    frac& operator*=(const frac &rhs)
    {
        num *= rhs.num;
        den *= rhs.den;

        mpz_class c;
        mpz_gcd(c.get_mpz_t(), num.get_mpz_t(), den.get_mpz_t());

        num /= c;
        den /= c;

        return *this;
    }

    frac operator+(const frac &other)
    {
        frac result = *this;
        result += other;
        return result;
    }

    frac operator*(const frac &other)
    {
        frac result = *this;
        result *= other;
        return result;
    }
};

uint32_t gcd(uint32_t a, uint32_t b);
uint64_t gcd64(uint64_t a, uint64_t b);
double gcdDbl(double a, double b);
uint32_t gcdExtended(uint32_t a, uint32_t b, uint32_t &x, uint32_t &y);
int64_t gcdExtended(int64_t a, int64_t b, int64_t &x, int64_t &y);
void getContinuedFraction(uint32_t inVal, continuedFrac &frac);
void computeKConvergent(continuedFrac &frac, uint64_t k, uint64_t &a, uint64_t &b);
void computeKConvergentDouble(continuedFrac &frac, uint64_t k, double &a, double &b);
bool isPalindromic(uint32_t value);
bool isPalindromic64(uint64_t value);
void cubicRoots(double a, double b, double c, double d, vector<complex<double>> &roots);
uint32_t numDigits(uint32_t val);
uint32_t powMod(uint32_t b, uint32_t e, uint32_t n);
int64_t powMod64(int64_t b, int64_t e, int64_t n);
uint64_t geomSum(uint64_t r, uint64_t n);

void convertBase(
    vector<uint64_t> &digitsIn,
    uint64_t b1,
    vector<uint64_t> &digitsOut,
    uint64_t b2
);