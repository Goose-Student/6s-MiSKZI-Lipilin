#include <vector>
#include <iostream>
#include "./common/common.cpp"

using namespace std;

vector<uint8_t> a = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
int p = 4;

// Функция сдвига
vector<uint8_t> shift(vector<uint8_t> &bytes)
{
    vector<uint8_t> shifted;
    for (uint8_t byte : bytes)
    {
        uint8_t juniorBits = byte >> p;
        uint8_t elderBits = byte << (8 - p);
        shifted.push_back(juniorBits | elderBits);
    }
    return shifted;
}

int main()
{
    // Вывод ветора a
    printVector(a);
    cout << endl;

    // Сдвиг 
    vector<unsigned char> shifted = shift(a);

    // Вывод ветора shifted
    printVector(shifted);
    cout << endl;

    system("pause");
    return 0;
}