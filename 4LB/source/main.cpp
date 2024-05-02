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
    RoundKey(string path)
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
    vector<uint8_t> key = readBytes("key.key");
    printBytes(key, Types::HEX);

    cout << endl;

    RoundKey round_key("key.key");
    for (int i = 0; i < 32; i++)
    {
        if (i % 8 == 0)
            cout << endl;
        printBytes(round_key[i], Types::HEX);
        cout << endl;
    }

    system("pause");
    return 0;
}