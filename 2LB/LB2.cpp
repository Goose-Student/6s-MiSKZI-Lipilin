#include <iostream>
#include <bitset>
#include <vector>
#include <cmath>
#include "common.cpp"

using namespace std;

int main()
{
    // Определение параметров
    int temp;
    cout << "Enter the first seed: ";
    cin >> temp;
    bitset<17> polinom1(temp);

    cout << "Enter the second seed: ";
    cin >> temp;
    bitset<111> polinom2(temp);
    cout << "\n# -------- Sampling -------- #:\n";
    // Определение объема выборки
    
    for (int i : vector<int>{1, 3, 6})
    {
        auto state = sampling(polinom1, polinom2, pow(10, i));
        cout << "10^" << i << ", 0x1: " << state.first << ", 0x0: " << state.second << endl;
    };
    cout << "\n# ------ Probability ------- #:\n";

    // Определение вероятностей появления от 1 до 4 бит
    auto seq = genSequence(polinom1, polinom2, pow(10, 6));
    for (int i = 1; i <= 4; i++)
    {
        auto patterns = genPatterns(i);
        for (auto bits : patterns)
        {
            printIter(bits);
            cout << ": " << probability(seq, bits) << "\n";
        }; cout << endl;
    };
    cout << "\n# ------ Correlation ------- #:\n";

    // Определение корреляции
    for (int i = 0; i <= 32; i++)
        cout << "t = " << i << ", " << correlation(seq, i) << endl;

    system("pause");
    return 0;
}
