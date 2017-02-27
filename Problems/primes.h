#pragma once

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <assert.h>

using namespace std;

void primeSieve(uint32_t max, vector<uint32_t> &primes);
bool isPrime(uint64_t prime, vector<uint32_t> &primes);