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

void getContinuedFraction(uint32_t inVal, continuedFrac &frac);
void computeKConvergent(continuedFrac &frac, uint64_t k, uint64_t &a, uint64_t &b);
void computeKConvergentDouble(continuedFrac &frac, uint64_t k, double &a, double &b);