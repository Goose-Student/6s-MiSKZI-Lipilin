#include <iostream>
#include <bitset>
#include <vector>
#include <cmath>
#include "common.cpp"

using namespace std;

int main()
{
    // Определение параметров
    int first_seed, second_seed;
    cout << "Enter the first seed: ";
    cin >> first_seed;

    cout << "Enter the second seed: ";
    cin >> second_seed;

    prsGen generator(first_seed, second_seed);
    auto sequence = generator.sequence(pow(10, 4));

    // * Определение объема выборки
    cout << "\n# -------- Sampling -------- #:\n";
    for (int i : vector<int>{1, 3, 6})
    {
        vector<double> samples = sampling(generator, pow(10, i));
        cout << "10^" << i << ", 1: " << samples[0] << ", 0: " << samples[1] << endl;
    }

    // Определение вероятностей появления от 1 до 4 бит
    cout << "\n# ------ Probability ------- #:\n";
    for (int i = 1; i <= 4; i++)
    {
        auto patterns = genPatterns(i);
        for (auto bits : patterns)
        {
            printIter(bits);
            cout << ": " << probability(sequence, bits) << "\n";
        };
        cout << endl;
    }

    // Определение корреляции
    cout << "\n# ------ Correlation ------- #:\n";
    for (int i = 0; i <= 32; i++)
        cout << "t = " << i << ", " << correlation(sequence, i) << endl;

    // Подсчет символов ASCII
    cout << "\n# ---- ASCII Probability --- #:\n";
    string path = "./file.txt";
    for (int number = 0; number <= 255; number++)
        cout << number << ": " << ascii(path, number) << "\n";

    // Маскирование файла
    string outpath =  "./mask.txt";
    mask(path, outpath, generator);

    // Подсчет символов ASCII
    cout << "\n# - Mask ASCII Probability - #:\n";
    for (int number = 0; number <= 255; number++)
        cout << number << ": " << ascii(outpath, number) << "\n";

    // Маскирование файла с инверсией
    string predominance =  "./predominance_mask.txt";
    mask(path, predominance, generator, 5);

    // Подсчет символов ASCII
    cout << "\n# - predominance Mask ASCII Probability - #:\n";
    for (int number = 0; number <= 255; number++)
        cout << number << ": " << ascii(predominance, number) << "\n";

    system("pause");
    return 0;
}
