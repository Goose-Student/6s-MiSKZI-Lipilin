#include <vector>
#include <iostream>

using namespace std;

vector<unsigned char> a = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
int p = 4;

vector<unsigned char> shift(vector<unsigned char> &sequence)
{
    vector<unsigned char> shifted;
    for (unsigned char bits : sequence)
    {
        unsigned char juniorBits = bits >> p;
        unsigned char elderBits = bits << (8 - p);
        shifted.push_back(juniorBits | elderBits);
    }
    return shifted;
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

    vector<unsigned char> shifted = shift(a);

    for (unsigned char bits : shifted)
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