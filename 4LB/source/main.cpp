#include <iostream>
#include <fstream>
#include <vector>
#include "./common/io.cpp"

using namespace std;

vector<uint8_t> S[8] = {
    {12, 4, 6, 2, 10, 5, 11, 9, 14, 8, 13, 7, 0, 3, 15, 1},
    {6, 8, 2, 3, 9, 10, 5, 12, 1, 14, 4, 7, 11, 13, 0, 15},
    {11, 3, 5, 8, 2, 15, 10, 13, 14, 1, 7, 4, 12, 9, 6, 0},
    {12, 8, 2, 1, 13, 4, 15, 6, 7, 0, 10, 5, 3, 14, 9, 11},
    {7, 15, 5, 10, 8, 1, 6, 13, 0, 9, 3, 14, 11, 4, 2, 12},
    {5, 13, 15, 6, 9, 2, 12, 10, 11, 7, 8, 1, 4, 3, 14, 0},
    {8, 14, 2, 5, 6, 9, 1, 12, 15, 4, 11, 0, 13, 10, 3, 7},
    {1, 7, 14, 13, 0, 5, 8, 3, 4, 15, 10, 6, 9, 12, 11, 2}};

template <typename T>
T substitution(const T &value)
{
    T replaced = 0;
    for (int i = 0; i < sizeof(value); i++)
    {
        uint8_t bits = (value >> (i * 4)) & 0xF;
        replaced |= (S[i][bits] << (i * 4));
    }
    return replaced;
}

template <typename T>
T circular_shift(const T &value, const int &shift)
{
    const size_t bits = sizeof(T) * 8;
    if (shift < 0)
        return (value << -shift) | (value >> (bits + shift));
    return (value >> shift) | (value << (bits - shift));
}

class RoundKey
{
private:
    vector<uint8_t> bytes;
    mutable uint32_t counter = 0;
    uint32_t sync = 4096; // Количество вызовов RoundKey[] на 1 Кб данных

public:
    RoundKey(const string &path)
    {
        bytes = readBytes<uint8_t>(path);
        if (bytes.size() != 7)
            throw range_error("\nThe key must be 56 bits in size\n");
    };

    uint32_t operator[](int index) const
    {
        if (index < 0 || index > 31)
            throw range_error("\nThe index must be in range [0, 32)\n");

        counter += 1;
        if (counter == sync * 10)
            cout << "\nWarning!!! The key is about to expire!\n";
        if (counter >= sync * 20)
            throw length_error("\nThe validity period of the key has expired.\n");

        if (index > 23)
            index = 31 - index;
        uint32_t nkey = 0;
        for (int i = 0; i < 4; i++)
            nkey |= (bytes[(index * 4 + i) % 7] << (3 - i) * 8);
        return nkey;
    }
};

uint64_t CryptoRound(const uint32_t &xkey, const uint64_t &block)
{
    uint32_t N1 = block & 0xFFFFFFFF;     // Правые 32 бита блока
    uint32_t N2 = block >> 32;            // Левые 32 бита блока
    uint32_t N1s = N1 + xkey;             // Сложение с ключем
    uint32_t R = substitution(N1s);       // Подстановка
    uint32_t Rs = circular_shift(R, -11); // Перестановка
    uint32_t N2s = Rs ^ N2;               // XOR
    return (uint64_t(N1) << 32) | N2s;    // Объединяем N1 и N2s в одно 64-битное число
}

int main()
{
    // Чтение файла
    vector<uint64_t> data64 = readBytes<uint64_t>("./files/open.txt");

    // Зашифрование
    RoundKey key("./files/key.key");
    for (int i = 0; i < data64.size(); i++)
    {
        for (uint8_t round = 0; round < 31; round++)
            data64[i] = CryptoRound(key[round], data64[i]);
        data64[i] = circular_shift(CryptoRound(key[31], data64[i]), 32);
    };
    writeBytes("./files/encrypt.enc", data64);
    delete &key;

    // Расшифрование
    key = RoundKey("./files/key.key");
    for (int i = 0; i < data64.size(); i++)
    {
        for (int round = 31; round > 0; round--)
            data64[i] = CryptoRound(key[round], data64[i]);
        data64[i] = circular_shift(CryptoRound(key[0], data64[i]), 32);
    }
    writeBytes("./files/decrypt.txt", data64);

    system("pause");
    return 0;
};
