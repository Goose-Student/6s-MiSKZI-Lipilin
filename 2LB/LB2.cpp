#include <iostream>
#include <bitset>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>
#include "common.cpp"
#include <algorithm>

using namespace std;

int main(){
    // Определение параметров
    int temp;
    cout << "Enter first seed: ";
    cin >> temp;
    bitset<17> polinom1(temp); 
    
    cout << "Enter second seed: ";
    cin >> temp;
    bitset<111> polinom2(temp); 

    // cout << "Enter len: ";
    // cin >> temp;

    vector<bool> seq; // Объявление вектора перед циклом

    // Оперделение обьема выборки
    for(int i : vector<int> {1, 3, 6}) {
        seq = sequence(polinom1, polinom2, pow(10, i));
        cout << 10 << "^" << i << ": " << count(seq.begin(), seq.end(), true) / pow(10, i) << endl;
    }; cout << endl;

    // Определение появления вероятности
    int len = pow(10, 5);
    seq = sequence(polinom1, polinom2, len);
    map<string, int> counts;
    for(int bits = 1; bits <= 4; bits++){
        for(int i = 0; i <= seq.size() - bits; i++){
            string combination;
            for(int j = 0; j < bits; j++){
                combination += seq[i + j] ? '1' : '0';
            }
            counts[combination]++;
        }
    }

    for(auto &pair : counts){
        std::cout << "combination: " << pair.first << ", Probability: " << 
        (double)pair.second / (seq.size() - pair.first.size() + 1) << std::endl;
    }cout << endl;

    system("pause");
    return 0;
}
