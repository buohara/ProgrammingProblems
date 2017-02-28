#pragma once

#include <stdint.h>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <string>
#include <math.h>
#include <assert.h>

using namespace std;

struct continuedFrac
{
    vector<uint32_t> terms;
    uint32_t prd;
};

uint32_t gcd(uint32_t a, uint32_t b);
uint64_t gcd64(uint64_t a, uint64_t b);
void getContinuedFraction(uint32_t inVal, continuedFrac &frac);
void computeKConvergent(continuedFrac &frac, uint64_t k, uint64_t &a, uint64_t &b);
void computeKConvergentDouble(continuedFrac &frac, uint64_t k, double &a, double &b);