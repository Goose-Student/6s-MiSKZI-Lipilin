#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

vector<uint8_t> SSS = {0x11, 0x71, 0xE1, 0xD1, 0x01, 0x51, 0x81, 0x31, 0x41, 0xF1, 0xA1, 0x61, 0x91, 0xC1, 0xB1, 0x21,
                       0x17, 0x77, 0xE7, 0xD7, 0x07, 0x57, 0x87, 0x37, 0x47, 0xF7, 0xA7, 0x67, 0x97, 0xC7, 0xB7, 0x27,
                       0x1E, 0x7E, 0xEE, 0xDE, 0x0E, 0x5E, 0x8E, 0x3E, 0x4E, 0xFE, 0xAE, 0x6E, 0x9E, 0xCE, 0xBE, 0x2E,
                       0x1D, 0x7D, 0xED, 0xDD, 0x0D, 0x5D, 0x8D, 0x3D, 0x4D, 0xFD, 0xAD, 0x6D, 0x9D, 0xCD, 0xBD, 0x2D,
                       0x10, 0x70, 0xE0, 0xD0, 0x00, 0x50, 0x80, 0x30, 0x40, 0xF0, 0xA0, 0x60, 0x90, 0xC0, 0xB0, 0x20,
                       0x15, 0x75, 0xE5, 0xD5, 0x05, 0x55, 0x85, 0x35, 0x45, 0xF5, 0xA5, 0x65, 0x95, 0xC5, 0xB5, 0x25,
                       0x18, 0x78, 0xE8, 0xD8, 0x08, 0x58, 0x88, 0x38, 0x48, 0xF8, 0xA8, 0x68, 0x98, 0xC8, 0xB8, 0x28,
                       0x13, 0x73, 0xE3, 0xD3, 0x03, 0x53, 0x83, 0x33, 0x43, 0xF3, 0xA3, 0x63, 0x93, 0xC3, 0xB3, 0x23,
                       0x14, 0x74, 0xE4, 0xD4, 0x04, 0x54, 0x84, 0x34, 0x44, 0xF4, 0xA4, 0x64, 0x94, 0xC4, 0xB4, 0x24,
                       0x1F, 0x7F, 0xEF, 0xDF, 0x0F, 0x5F, 0x8F, 0x3F, 0x4F, 0xFF, 0xAF, 0x6F, 0x9F, 0xCF, 0xBF, 0x2F,
                       0x1A, 0x7A, 0xEA, 0xDA, 0x0A, 0x5A, 0x8A, 0x3A, 0x4A, 0xFA, 0xAA, 0x6A, 0x9A, 0xCA, 0xBA, 0x2A,
                       0x16, 0x76, 0xE6, 0xD6, 0x06, 0x56, 0x86, 0x36, 0x46, 0xF6, 0xA6, 0x66, 0x96, 0xC6, 0xB6, 0x26,
                       0x19, 0x79, 0xE9, 0xD9, 0x09, 0x59, 0x89, 0x39, 0x49, 0xF9, 0xA9, 0x69, 0x99, 0xC9, 0xB9, 0x29,
                       0x1C, 0x7C, 0xEC, 0xDC, 0x0C, 0x5C, 0x8C, 0x3C, 0x4C, 0xFC, 0xAC, 0x6C, 0x9C, 0xCC, 0xBC, 0x2C,
                       0x1B, 0x7B, 0xEB, 0xDB, 0x0B, 0x5B, 0x8B, 0x3B, 0x4B, 0xFB, 0xAB, 0x6B, 0x9B, 0xCB, 0xBB, 0x2B,
                       0x12, 0x72, 0xE2, 0xD2, 0x02, 0x52, 0x82, 0x32, 0x42, 0xF2, 0xA2, 0x62, 0x92, 0xC2, 0xB2, 0x22};

vector<uint8_t> encrypt(vector<uint8_t> &bytes)
{
    vector<uint8_t> encrypted;
    for (uint8_t byte : bytes)
        encrypted.push_back(SSS[byte]);
    return encrypted;
}

int main()
{
    ifstream input("input.txt", ios::binary);
    ofstream output("output6-7.txt", ios::binary);

    vector<uint8_t> a((istreambuf_iterator<char>(input)),
                      istreambuf_iterator<char>());

    vector<uint8_t> encrypted = encrypt(a);

    for (uint8_t bits : encrypted)
        output << bits;
    output.close();
    input.close();

    system("pause");
    return 0;
}
