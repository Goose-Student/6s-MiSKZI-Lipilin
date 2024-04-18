#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

vector<unsigned char> S = {0x01, 0x07, 0x0E, 0x0D, 0x00, 0x05, 0x08, 0x03,
                           0x04, 0x0F, 0x0A, 0x06, 0x09, 0x0C, 0x0B, 0x02};
vector<unsigned char> S6 = {0x07, 0x01, 0x0D, 0x0E, 0x05, 0x00, 0x03, 0x08,
                            0x0F, 0x04, 0x06, 0x0A, 0x0C, 0x09, 0x02, 0x0B};
int p = 4;

vector<unsigned char> encrypt(vector<unsigned char> &sequence)
{
    vector<unsigned char> encrypted;
    for (unsigned char bits : sequence)
    {
        unsigned char juniorBits = bits & 0x0F;
        unsigned char elderBits = (bits & 0xF0) >> 4;
        unsigned char joinBits = (S6[elderBits] << 4) | S6[juniorBits];

        juniorBits = joinBits >> p;
        elderBits = joinBits << (8 - p);

        encrypted.push_back(juniorBits | elderBits);
    }
    return encrypted;
}

int main()
{
    ifstream input("input.txt", ios::binary);
    ofstream output("output.txt", ios::binary);

    vector<unsigned char> a((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());

    vector<unsigned char> encrypted = encrypt(a);

    for (unsigned char bits : encrypted)
    {
        output << bits;
    }

    system("pause");
    return 0;
}
