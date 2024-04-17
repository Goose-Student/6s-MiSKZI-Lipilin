#include <vector>
#include <iostream>

using namespace std;

vector<char> S = {0x01, 0x07, 0x0E, 0x0D, 0x00, 0x05, 0x08, 0x03,
                  0x04, 0x0F, 0x0A, 0x06, 0x09, 0x0C, 0x0B, 0x02};
vector<char> a = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

vector<char> substitution(vector<char> a)
{
    vector<char> replaced;
    for (char bits : a)
        replaced.push_back(S[bits]);
    return replaced;
}

int main()
{
    for (unsigned char bits : a)
    {
        for (int i = 3; i >= 0; i--)
            cout << ((bits >> i) & 0x01);
        cout << ' ';
    };
    cout << endl;

    vector<char> replaced = substitution(a);

    for (unsigned char bits : replaced)
    {
        for (int i = 3; i >= 0; i--)
            cout << ((bits >> i) & 0x01);
        cout << ' ';
    };
    cout << endl;

    system("pause");
    return 0;
}
