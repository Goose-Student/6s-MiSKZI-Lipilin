#include <iostream>
#include <bitset>
#include <fstream>
#include <vector>

using namespace std;

bool generate(bitset<17> &polinom1, bitset<111> &polinom2){
    bool sum1 = polinom1[13] ^ polinom1[16];
    bool sum2 = polinom2[100] ^ polinom2[110];
    bool res = sum1 ^ sum2;

    polinom1 <<= 1;  // Сдвиг влево на 1 позицию
    polinom1[0] = sum1;
    polinom2 <<= 1;  // Сдвиг влево на 1 позицию
    polinom2[0] = sum2;

    return res;
}

vector<bool> sequence(bitset<17> &polinom1, bitset<111> &polinom2, int len){
    vector<bool> seq;
    for(int i = 0; i < len; i++){
        seq.push_back(generate(polinom1, polinom2));
    }
    return seq;
}

