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

void writePrimesToFile(const char* fileName, vector<uint32_t> &primes);
void readPrimesFromFile(const char* fileName, vector<uint32_t> &primes, uint32_t max);
void readPrimesFromFile(const char* fileName, unordered_set<uint32_t> &primes, uint32_t max);
void primeSieve(uint32_t max, vector<uint32_t> &primes);
void primeSieve(uint32_t max, unordered_set<uint32_t> &primes);
bool isPrime(uint64_t prime, vector<uint32_t> &primes);
uint32_t primePi(uint32_t exponent);
void factorSieve(uint32_t max, vector<vector<primePower>> &values);