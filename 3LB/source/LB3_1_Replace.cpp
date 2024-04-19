#include <vector>
#include <iostream>
#include "./common/common.cpp"

using namespace std;

vector<uint8_t> S = {0x01, 0x07, 0x0E, 0x0D, 0x00, 0x05, 0x08, 0x03,
                  0x04, 0x0F, 0x0A, 0x06, 0x09, 0x0C, 0x0B, 0x02};
vector<uint8_t> a = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                  0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

vector<uint8_t> substitution(vector<uint8_t> &sequence)
{
    vector<uint8_t> replaced;
    for (uint8_t byte : sequence)
        replaced.push_back(S[byte]);
    return replaced;
}

int main()
{
    printVector(a);
    cout << endl;
    vector<uint8_t> replaced = substitution(a);
    printVector(replaced);
    cout << endl;

    system("pause");
    return 0;
}
