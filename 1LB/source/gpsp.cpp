#include <iostream>
#include <bitset>
#include <fstream>

using namespace std;

bool generate(std::bitset<17> &polinom1, std::bitset<111> &polinom2){
    bool sum1 = polinom1[13] ^ polinom1[16];
    bool sum2 = polinom2[100] ^ polinom2[110];
    bool res = sum1 ^ sum2;

    polinom1 <<= 1;  // Сдвиг влево на 1 позицию
    polinom1[0] = sum1;
    polinom2 <<= 1;  // Сдвиг влево на 1 позицию
    polinom2[0] = sum2;

    return res;
}

int main() {
    int seed;
    
    cout << "Enter second seed: ";
    cin >> seed;
    bitset<17> polinom1(seed); 
    
    cout << "Enter second seed: ";
    cin >> seed;
    bitset<111> polinom2(seed); 

    ifstream inputFile("input.txt", ios::binary);
    ofstream outputFile("output.bin", ios::binary);

    char c;
    while (inputFile.get(c)) {
        bitset<8> byte(c); // конвертация в биты
        for (int i = 0; i < 8; i++) {
            bool random_bit = generate(polinom1, polinom2);
            bool original_bit = byte[i];
            bool masked_bit = original_bit ^ random_bit;
            byte[i] = masked_bit;
        }
        c = static_cast<char>(byte.to_ulong()); // конвертация в символ
        outputFile.put(c);
    }

    inputFile.close();
    outputFile.close();


    system("pause");
    return 0;
}