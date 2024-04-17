#include <vector>
#include <iostream>

using namespace std;

vector<char> S = {0x01, 0x07, 0x0E, 0x0D, 0x00, 0x05, 0x08, 0x03,
                  0x04, 0x0F, 0x0A, 0x06, 0x09, 0x0C, 0x0B, 0x02};
vector<bool> a = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1,
                  0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1,
                  1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1,
                  1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1};

vector<bool> substitution(vector<bool> a)
{
    vector<bool> replaced;
    for (int i = 0; i < 64; i += 4)
    {
        int index = 0;
        for (int j = 0; j < 4; j++)
            index = (index << 1) + a[i + j];

        char new_bits = S[index];
        for (int j = 3; j >= 0; j--)
            replaced.push_back(new_bits & (1 << j));
    }
    return replaced;
}

int main()
{
    for (int i = 0; i < 64; i += 4)
    {
        for (int j = 0; j < 4; j++)
            cout << a[i + j];
        cout << " ";
    }
    cout << endl;

    vector<bool> replaced = substitution(a);
    for (int i = 0; i < 64; i += 4)
    {
        for (int j = 0; j < 4; j++)
            cout << replaced[i + j];
        cout << " ";
    }

    system("pause");
    return 0;
}
