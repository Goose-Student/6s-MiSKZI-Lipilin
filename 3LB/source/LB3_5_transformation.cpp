#include <vector>
#include <iostream>
#include <fstream>
#include "common/io.cpp" 
using namespace std;

vector<uint8_t> S = {0x01, 0x07, 0x0E, 0x0D, 0x00, 0x05, 0x08, 0x03,
                     0x04, 0x0F, 0x0A, 0x06, 0x09, 0x0C, 0x0B, 0x02};

int p = 4;

vector<uint8_t> encrypt(vector<uint8_t> &bytes)
{
    vector<uint8_t> encrypted;
    for (uint8_t bits : bytes)
    {
        // Извлечение бит
        uint8_t juniorBits = bits & 0x0F;
        uint8_t elderBits = (bits & 0xF0) >> 4;
        uint8_t joinBits = (S[elderBits] << 4) | S[juniorBits];

        // Сдвиг бит
        juniorBits = joinBits >> p;
        elderBits = joinBits << (8 - p);

        // Склеиваем биты
        encrypted.push_back(juniorBits | elderBits);
    }
    return encrypted;
}


int main()
{
    ifstream input("input.txt", ios::binary);
    ofstream output("output.txt", ios::binary);

    vector<uint8_t> a((istreambuf_iterator<char>(input)),
                      istreambuf_iterator<char>());

    vector<uint8_t> encrypted = encrypt(a);

    printBytes(encrypted, Types::HEX);

    for (uint8_t bytes : encrypted)
        output << bytes;
    output.close();
    input.close();

    system("pause");
    return 0;
}
