#pragma once

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <unordered_set>
#include <string>
#include <assert.h>
#include <iostream>
#include <fstream>

using namespace std;

struct primePower
{
    uint32_t prime;
    uint32_t power;
};

struct primePower64
{
	uint64_t prime;
	uint64_t power;
};

void writePrimesToFile(const char* fileName, vector<uint32_t> &primes);
void readPrimesFromFile(const char* fileName, vector<uint32_t> &primes, uint32_t max);
void readPrimesFromFile(const char* fileName, unordered_set<uint32_t> &primes, uint32_t max);
void primeSieve(uint32_t max, vector<uint32_t> &primes);
void primeSieve(uint64_t max, vector<uint64_t> &primes);
void primeSieve(uint32_t min, uint32_t max, vector<uint32_t> &primes);
void primeSieve(uint32_t max, unordered_set<uint32_t> &primes);
bool isPrime(uint64_t prime, vector<uint32_t> &primes);
uint32_t primePi(uint32_t exponent);
void factorSieve(uint32_t max, vector<vector<primePower>> &values);
void factorTrialDivision(vector<uint32_t> &primes, vector<primePower> &factors, uint64_t value);
void factorTrialDivision64(vector<uint64_t> &primes, vector<primePower64> &factors, uint64_t value);