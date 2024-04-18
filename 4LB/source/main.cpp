#include <iostream>
#include <fstream>
#include <vector>
#include <random>

using namespace std;

uint64_t t(uint64_t input)
{
    return ~input;
}

uint64_t g(vector<uint8_t> key, uint64_t input)
{
    return ~input;
}

vector<uint8_t> keyExpansion(vector<uint8_t> key)
{
    if (key.size() != 7)
        throw range_error("The key must be 56 bits in size");

    vector<uint8_t> extendedKey;
    for (int i = 0; i < 32; ++i)
        extendedKey.push_back(key[i % 7]);
    return extendedKey;
}