#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <numeric>

using namespace std;

// Генераторы 
bool genBit(unsigned int &seed1, unsigned int &seed2,
            )
{
    bool sum1 = ((polinom1 >> 13) & 1) ^ ((polinom1 >> 16) & 1);
    bool sum2 = ((polinom2 >> 100) & 1) ^ ((polinom1 >> 110) & 1);
    bool res = sum1 ^ sum2;

    polinom1 <<= 1; // Сдвиг влево на 1 позицию
    polinom1 |= (sum1 << 0); // Устанавливаем 0-й бит
    polinom2 <<= 1; // Сдвиг влево на 1 позицию
    polinom2 |= (sum2 << 0); // Устанавливаем 0-й бит

    return res;
}

vector<bool> genSequence(bitset<17> &polinom1, bitset<111> &polinom2, int len)
{
    vector<bool> seq;
    for (int i = 0; i < len; i++)
    {
        seq.push_back(genBit(polinom1, polinom2));
    }
    return seq;
}

vector<vector<bool>> genPatterns(int &n)
{
    vector<vector<bool>> patterns;
    for (int i = 0; i < (1 << n); ++i)
    {
        vector<bool> pattern;
        for (int j = n - 1; j >= 0; --j)
        {
            bool bit = (i >> j) & 1;
            pattern.push_back(bit);
        }
        patterns.push_back(pattern);
    }
    return patterns;
}

// Расчет статистики
pair<double, double> sampling(bitset<17> &polinom1, bitset<111> &polinom2, int len)
{
    double counter = 0.0;
    for (int i = 0; i < len; i++)
    {
        if (genBit(polinom1, polinom2))
            counter++;
    }
    return make_pair(counter / len, (len - counter) / len);
}

double probability(vector<bool> &sequence, vector<bool> &bits)
{
    if (bits.empty())
        return 0.0;

    double counter = 0.0;
    for (int i = 0; i <= sequence.size() - bits.size(); i++)
    {
        auto start = sequence.begin() + i;
        auto end = start + bits.size();
        vector<bool> slice(start, end);
        bool isEqual = equal(bits.begin(), bits.end(), slice.begin());
        if (isEqual)
            counter++;
    }
    return counter / sequence.size();
}



double correlation(vector<bool> &sequence, int &t)
{
    vector<bool> slice_seq(sequence.begin() + t, sequence.end());
    vector<bool> shift_seq(sequence.begin(), sequence.end() - t);

    double A = inner_product(slice_seq.begin(), slice_seq.end(),
                             shift_seq.begin(), 0, plus<>(), equal_to<>());
    double B = sequence.size() - A;
    return (A - B) / (A + B);
}

double ascii(string &path, int &number){
    char temp_symbol;
    double counter = 0;
    int size = 0;
    ifstream file(path, ios::binary);
    while (file.get(temp_symbol)){
        unsigned char symbol = temp_symbol;
        if (int(symbol) == number) counter++;
        size++;
    }; file.close();
    return counter / size;
        
}

void mask(string &inpath, string &outpath, 
bitset<17> polinom1, bitset<111> polinom2){

}

template <typename T>
void printIter(const T &iterable)
{
    for (const auto &element : iterable)
        cout << element;
}