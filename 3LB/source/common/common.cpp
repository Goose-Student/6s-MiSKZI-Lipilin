#include <iostream>
#include <fstream>

#include <vector>
#include <numeric>
#include <bitset>
#include <stdio.h>
#include <stdint.h>

using namespace std;

class Generator
{
private:
    //* Иницилизация полиномов *//
    bitset<128> firstPolynomial;
    bitset<128> secondPolynomial;

    //* Иницилизация дефолтных значений*//
    int ids[6] = {13, 16, 17, 100, 110, 111};

public:
    //* Конструктор *//
    Generator(long long int firstSeed,
              long long int secondSeed)
    {
        firstPolynomial = bitset<128>(firstSeed);
        secondPolynomial = bitset<128>(secondSeed);
        secondPolynomial <<= ids[5] / 2;
    }

    /** Generator methods**/
    bool getBit()
    {
        //* Получение суммы по модулю 2 для полиномов*//
        bool firstSum = firstPolynomial[ids[0]] ^ firstPolynomial[ids[1]];
        bool secondSum = firstPolynomial[ids[3]] ^ firstPolynomial[ids[4]];

        //* Сдвигаем полиномы *//
        firstPolynomial <<= 1;
        secondPolynomial <<= 1;

        //* Устанавливаем нулевые биты как соответсвующую сумму *//
        firstPolynomial[0] = firstSum;
        secondPolynomial[0] = secondSum;

        //* Обрезаем полиномы по их размеру
        this->firstPolynomial &= (1ULL << ids[2]) - 1;
        this->secondPolynomial &= (1ULL << ids[5]) - 1;

        return firstSum ^ secondSum;
    }

    uint8_t getByte()
    {
        uint8_t byte = 0;
        for (int i = 0; i < 8; i++)
        {
            byte <<= 1;
            byte |= getBit();
        }
        return byte; 
    }

    vector<bool> bitSequence(int length)
    {
        vector<bool> sequence;
        for (int i = 0; i < length; i++)
            sequence.push_back(getBit());
        return sequence;
    }

    vector<uint8_t> byteSequence(int length)
    {
        vector<uint8_t> bytes;
        for (int i = 0; i < length; ++i)
            bytes.push_back(getByte());
        return bytes;
    }
};

void printVector(vector<uint8_t> bytes)
{
    for (uint8_t byte : bytes)
        printf("0x%02X ", byte);
    cout << endl;
}

void writeVector(string path, vector<uint8_t> bytes)
{
    ofstream file(path, ios::binary);
    for (uint8_t byte : bytes)
        file.put(byte);
    file.close();
}