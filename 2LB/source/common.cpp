#include <iostream>
#include <vector>
#include <numeric>
#include <fstream>
#include <bitset>

using namespace std;

class prsGen
{
private:
    //* Иницилизация полиномов *//
    bitset<128> firstPolynomial;
    bitset<128> secondPolynomial;

    //* Иницилизация дефолтных значений*//
    int ids[6] = {13, 16, 17, 100, 110, 111};

public:
    //* Конструктор *//
    prsGen(long long int firstSeed,
           long long int secondSeed)
    {
        firstPolynomial = bitset<128>(firstSeed);
        secondPolynomial = bitset<128>(secondSeed);
    }

    /** Generator methods**/
    bool getBit()
    {
        //* Получение суммы по модулю 2 для полиномов*//
        bool firstSum = firstPolynomial[ids[0]] ^ firstPolynomial[ids[1]];
        bool secondSum = firstPolynomial[ids[3]] ^ firstPolynomial[ids[4]];

        //* Сдвигаем полиномы *//
        firstPolynomial <<= 1;
        secondPolynomial <<= 1;

        //* Устанавливаем нулевые биты как соответсвующую сумму *//
        firstPolynomial[0] = firstSum;
        secondPolynomial[0] = secondSum;

        //* Обрезаем полиномы по их размеру
        this->firstPolynomial &= (1ULL << ids[2]) - 1;
        this->secondPolynomial &= (1ULL << ids[5]) - 1;

        return firstSum ^ secondSum;
    }
    vector<bool> sequence(int length)
    {
        vector<bool> seq;
        for (int i = 0; i < length; i++)
            seq.push_back(getBit());
        return seq;
    }
};

// Расчет вероятности появления битов 1 и 0 в последовательности
vector<double> sampling(prsGen &generator, int length)
{
    double counter = 0.0;
    for (int i = 0; i < length; i++)
    {
        if (generator.getBit())
            counter++;
    }
    return vector<double>{counter / length, (length - counter) / length};
}

// Генерация паттернов
vector<vector<bool>> genPatterns(int length)
{
    vector<vector<bool>> patterns;
    for (int i = 0; i < (1 << length); ++i)
    {
        vector<bool> pattern;
        for (int j = length - 1; j >= 0; --j)
        {
            bool bit = (i >> j) & 1;
            pattern.push_back(bit);
        }
        patterns.push_back(pattern);
    }
    return patterns;
}

// Расчет вероятности появления числа в последовательности
double probability(vector<bool> &sequence, vector<bool> &bits)
{
    // Проверка есть ли биты в веторе
    if (bits.empty())
        return 0.0;

    // Подсчет вхождений последовательности битов в сгенерированную последовательность
    double counter = 0.0;
    for (int i = 0; i <= sequence.size() - bits.size(); i++)
    {
        // Определение среза
        auto begin = sequence.begin() + i;
        auto end = begin + bits.size();
        vector<bool> slice(begin, end);

        // Сравнение среза и битов
        if (equal(bits.begin(), bits.end(), slice.begin()))
            counter++;
    }
    return counter / sequence.size();
}

// Функция определения корреляции
double correlation(vector<bool> &sequence, int &t)
{
    // Сдвигаем последовательность бит на t бит относительно друг друга
    vector<bool> slice_seq(sequence.begin() + t, sequence.end());
    vector<bool> shift_seq(sequence.begin(), sequence.end() - t);

    // Подсчитываем количество совпадений
    double A = inner_product(slice_seq.begin(), slice_seq.end(),
                             shift_seq.begin(), 0, plus<>(), equal_to<>());
    double B = sequence.size() - A;

    // Расчет корреляции
    return (A - B) / (A + B);
}

// Подсчет вероятности встречи в файле ASCII символа
double ascii(const std::string &path, const int &number)
{
    unsigned char buffer;
    double counter = 0.0;
    ifstream file(path, ios::binary | ios::ate);
    long long int size = file.tellg();
    file.seekg(0);
    while (file.get((char &)buffer))
        if (int(buffer) == number)
            counter++;
    file.close();
    return counter / size;
}

void mask(string &inpath, string &outpath, prsGen &generator, int invertEveryNth = 0)
{
    char buffer;
    ifstream inFile(inpath, ios::binary);
    ofstream outFile(outpath, ios::binary);

    long long int bitCount = 0;
    while (inFile.get(buffer))
    {
        for (int i = 0; i < 8; i++)
        {
            // Если invertEveryNth > 0 и текущий бит является n-м битом, инвертируем его
            if (invertEveryNth > 0 && bitCount % invertEveryNth == 0)
                buffer ^= 1 << i;

            bool bit = generator.getBit();
            buffer ^= (-bit ^ buffer) & (1 << i);
            bitCount++;
        }
        outFile.put(buffer);
    }

    inFile.close();
    outFile.close();
}

template <typename T>
void printIter(const T &iterable)
{
    for (const auto &element : iterable)
        cout << element;
}