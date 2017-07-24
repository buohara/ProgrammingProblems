#pragma once

#include <stdint.h>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <string>
#include <math.h>
#include <assert.h>
#include "mpirxx.h"

using namespace std;

struct continuedFrac
{
    vector<uint32_t> terms;
    uint32_t prd;
};

uint32_t gcd(uint32_t a, uint32_t b);
uint64_t gcd64(uint64_t a, uint64_t b);
double gcdDbl(double a, double b);
void getContinuedFraction(uint32_t inVal, continuedFrac &frac);
void computeKConvergent(continuedFrac &frac, uint64_t k, uint64_t &a, uint64_t &b);
void computeKConvergentDouble(continuedFrac &frac, uint64_t k, double &a, double &b);

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