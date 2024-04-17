#include <vector>
#include <iostream>

using namespace std;

vector<char> S = {0x01, 0x07, 0x0E, 0x0D, 0x00, 0x05, 0x08, 0x03,
                  0x04, 0x0F, 0x0A, 0x06, 0x09, 0x0C, 0x0B, 0x02};
vector<char> SS = {0x03, 0x01, 0x07, 0x0E, 0x0D, 0x05, 0x0F, 0x08,
                   0x02, 0x04, 0x0C, 0x0A, 0x00, 0x06, 0x09, 0x0B};

vector<unsigned char> a = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};

vector<unsigned char> substitution(vector<unsigned char> a)
{
    vector<unsigned char> replaced;
    for (unsigned char bits : a)
    {
        // Извлечение бит
        cout << "bits: " << bits << endl;
        unsigned char lastFourBits = bits & 0x0F;
        unsigned char firstFourBits = (bits & 0xF0) >> 4;

        // Замена бит
        cout << "lastFourBits: " << lastFourBits << endl;
        cout << "S[firstFourBits]: " << S[firstFourBits] << endl;
    }
    return replaced;
}

int main()
{
    // // ВЫвод ветора А
    // for (unsigned char bits : a)
    // {
    //     for (int i = 3; i >= 0; i--)
    //         cout << ((bits >> i) & 0x01);
    //     cout << ' ';
    //     for (int i = 7; i >= 4; i--)
    //         cout << ((bits >> i) & 0x01);
    //     cout << ' ';
    // };
    // cout << endl;

    vector<unsigned char> replaced = substitution(a);

    // // Вывод ветора replaced
    // for (unsigned char bits : replaced)
    // {
    //     for (int i = 3; i >= 0; i--)
    //         cout << ((bits >> i) & 0x01);
    //     cout << ' ';
    //     for (int i = 7; i >= 4; i--)
    //         cout << ((bits >> i) & 0x01);
    //     cout << ' ';
    // };
    // cout << endl;

    system("pause");
    return 0;
}