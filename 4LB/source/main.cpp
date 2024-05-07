#include <iostream>
#include <fstream>
#include <vector>
#include "./common/io.cpp"

using namespace std;

vector<uint8_t> S[8] = {{12, 4, 6, 2, 10, 5, 11, 9, 14, 8, 13, 7, 0, 3, 15, 1},
                        {6, 8, 2, 3, 9, 10, 5, 12, 1, 14, 4, 7, 11, 13, 0, 15},
                        {11, 3, 5, 8, 2, 15, 10, 13, 14, 1, 7, 4, 12, 9, 6, 0},
                        {12, 8, 2, 1, 13, 4, 15, 6, 7, 0, 10, 5, 3, 14, 9, 11},
                        {7, 15, 5, 10, 8, 1, 6, 13, 0, 9, 3, 14, 11, 4, 2, 12},
                        {5, 13, 15, 6, 9, 2, 12, 10, 11, 7, 8, 1, 4, 3, 14, 0},
                        {8, 14, 2, 5, 6, 9, 1, 12, 15, 4, 11, 0, 13, 10, 3, 7},
                        {1, 7, 14, 13, 0, 5, 8, 3, 4, 15, 10, 6, 9, 12, 11, 2}};

class RoundKey
{
private:
    vector<uint8_t> bytes;

public:
    RoundKey(const string &path)
    {
        bytes = readBytes(path);
        if (bytes.size() != 7)
            throw range_error("The key must be 56 bits in size");
    };

    uint32_t operator[](int index) const
    {
        if (index < 0 || index > 31)
            throw range_error("The index must be in range [0, 32)");

        if (index > 23)
            index = 31 - index;

        uint32_t nkey = 0;
        for (int i = 0; i < 4; i++)
            nkey |= (bytes[(index * 4 + i) % 7] << (3 - i) * 8);
        return nkey;
    }
};

int main()
{   
    // Чтение файла
    vector<uint8_t> data8 = readBytes("input.txt");
    while (data8.size() % 64 != 0)
        data8.push_back(0x00);

    // развертывание байтоваго веектора в вектор vector<vector<part1, part1>> 
    vector<vector<uint32_t>> blocks;
    for (size_t i = 0; i < data8.size(); i += 8)
    {
        uint32_t part1 = 0, part2 = 0;
        for (size_t j = 0; j < 4; ++j)
        {
            part1 |= (data8[i + j] << ((3 - j) * 8));
            part2 |= (data8[i + j + 4] << ((3 - j) * 8));
        }
        blocks.push_back({part1, part2});
    };

    // Зашифрование
    RoundKey key("key.key");
    for (int i = 0; i < blocks.size(); i++)
    {   
        vector<uint32_t> block = blocks[i];
        for (int round = 0; round < 32; round++)
        {
            uint32_t N1 = block[0];
            uint32_t N2 = block[1];
            uint32_t X = key[round];

            // Сложение с ключем
            uint32_t N1s = N1 + X;

            // Подстановка
            uint32_t R = 0;
            for (int j = 0; j < 8; j++)
            {
                uint8_t bits4 = (N1s >> (j * 4)) & 0xF; // Извлекаем 4 бита
                R |= (S[j][bits4] << (j * 4));          // Применяем подстановку и добавляем в R
            }

            // Перестановка
            uint32_t Rs = (R << 11) | (R >> (32 - 11));

            uint32_t N2s = Rs ^ N2; //XOR
            block[1] = N1;
            block[0] = N2s;
        };
        blocks[i] = block;
    };

    vector<uint8_t> data8_reconstructed;
    for (const auto &block : blocks)
    {
        for (const auto &part : block)
        {
            for (int i = 3; i >= 0; --i)
                data8_reconstructed.push_back((part >> (i * 8)) & 0xFF);
        };
    }
    writeBytes("input.bin", data8_reconstructed);

    system("pause");
    return 0;
};