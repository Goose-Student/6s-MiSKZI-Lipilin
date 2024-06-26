#include <vector>
#include <iostream>
#include "./common/generator.cpp"
#include "./common/io.cpp"

using namespace std;

vector<uint8_t> SS = {0x11, 0x17, 0x1E, 0x1D, 0x10, 0x15, 0x18, 0x13, 0x14, 0x1F, 0x1A, 0x16, 0x19, 0x1C, 0x1B, 0x12,
                      0x71, 0x77, 0x7E, 0x7D, 0x70, 0x75, 0x78, 0x73, 0x74, 0x7F, 0x7A, 0x76, 0x79, 0x7C, 0x7B, 0x72,
                      0xE1, 0xE7, 0xEE, 0xED, 0xE0, 0xE5, 0xE8, 0xE3, 0xE4, 0xEF, 0xEA, 0xE6, 0xE9, 0xEC, 0xEB, 0xE2,
                      0xD1, 0xD7, 0xDE, 0xDD, 0xD0, 0xD5, 0xD8, 0xD3, 0xD4, 0xDF, 0xDA, 0xD6, 0xD9, 0xDC, 0xDB, 0xD2,
                      0x01, 0x07, 0x0E, 0x0D, 0x00, 0x05, 0x08, 0x03, 0x04, 0x0F, 0x0A, 0x06, 0x09, 0x0C, 0x0B, 0x02,
                      0x51, 0x57, 0x5E, 0x5D, 0x50, 0x55, 0x58, 0x53, 0x54, 0x5F, 0x5A, 0x56, 0x59, 0x5C, 0x5B, 0x52,
                      0x81, 0x87, 0x8E, 0x8D, 0x80, 0x85, 0x88, 0x83, 0x84, 0x8F, 0x8A, 0x86, 0x89, 0x8C, 0x8B, 0x82,
                      0x31, 0x37, 0x3E, 0x3D, 0x30, 0x35, 0x38, 0x33, 0x34, 0x3F, 0x3A, 0x36, 0x39, 0x3C, 0x3B, 0x32,
                      0x41, 0x47, 0x4E, 0x4D, 0x40, 0x45, 0x48, 0x43, 0x44, 0x4F, 0x4A, 0x46, 0x49, 0x4C, 0x4B, 0x42,
                      0xF1, 0xF7, 0xFE, 0xFD, 0xF0, 0xF5, 0xF8, 0xF3, 0xF4, 0xFF, 0xFA, 0xF6, 0xF9, 0xFC, 0xFB, 0xF2,
                      0xA1, 0xA7, 0xAE, 0xAD, 0xA0, 0xA5, 0xA8, 0xA3, 0xA4, 0xAF, 0xAA, 0xA6, 0xA9, 0xAC, 0xAB, 0xA2,
                      0x61, 0x67, 0x6E, 0x6D, 0x60, 0x65, 0x68, 0x63, 0x64, 0x6F, 0x6A, 0x66, 0x69, 0x6C, 0x6B, 0x62,
                      0x91, 0x97, 0x9E, 0x9D, 0x90, 0x95, 0x98, 0x93, 0x94, 0x9F, 0x9A, 0x96, 0x99, 0x9C, 0x9B, 0x92,
                      0xC1, 0xC7, 0xCE, 0xCD, 0xC0, 0xC5, 0xC8, 0xC3, 0xC4, 0xCF, 0xCA, 0xC6, 0xC9, 0xCC, 0xCB, 0xC2,
                      0xB1, 0xB7, 0xBE, 0xBD, 0xB0, 0xB5, 0xB8, 0xB3, 0xB4, 0xBF, 0xBA, 0xB6, 0xB9, 0xBC, 0xBB, 0xB2,
                      0x21, 0x27, 0x2E, 0x2D, 0x20, 0x25, 0x28, 0x23, 0x24, 0x2F, 0x2A, 0x26, 0x29, 0x2C, 0x2B, 0x22};
vector<uint8_t> a = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};

vector<uint8_t> substitution(vector<uint8_t> &bytes)
{
    vector<uint8_t> replaced;
    for (uint8_t byte : bytes)
        replaced.push_back(SS[byte]);
    return replaced;
}

int main()
{
    cout << "A: ";
    printBytes(a, Types::HEX);
    cout << endl;

    vector<uint8_t> replaced = substitution(a);

    cout << "R: ";
    printBytes(replaced, Types::HEX);
    cout << endl;

    system("pause");
    return 0;
}