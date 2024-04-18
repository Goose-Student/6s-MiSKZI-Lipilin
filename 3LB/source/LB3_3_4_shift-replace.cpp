#include <vector>
#include <iostream>

using namespace std;

vector<unsigned char> a = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
vector<unsigned char> S = {0x01, 0x07, 0x0E, 0x0D, 0x00, 0x05, 0x08, 0x03,
                           0x04, 0x0F, 0x0A, 0x06, 0x09, 0x0C, 0x0B, 0x02};
int p = 4;

vector<unsigned char> encrypt(vector<unsigned char> &sequence)
{
    vector<unsigned char> encrypted;
    for (unsigned char bits : sequence)
    {
        // Извлечение бит
        unsigned char juniorBits = bits & 0x0F;
        unsigned char elderBits = (bits & 0xF0) >> 4;
        unsigned char joinBits = (S[elderBits] << 4) | S[juniorBits];

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

    for (unsigned char bits : a)
    {
        for (int i = 7; i >= 0; i--)
        {
            cout << ((bits >> i) & 0x01);
            if (i % 4 == 0)
                cout << ' ';
        };
    }
    cout << endl;

    vector<unsigned char> encrypted = encrypt(a);

    for (unsigned char bits : encrypted)
    {
        for (int i = 7; i >= 0; i--)
        {
            cout << ((bits >> i) & 0x01);
            if (i % 4 == 0)
                cout << ' ';
        }
    }

    system("pause");
    return 0;
}
