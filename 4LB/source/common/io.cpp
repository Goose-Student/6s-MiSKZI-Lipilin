#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

class Type
{
private:
    string type;

public:
    // __init__
    Type(const string type)
    {
        this->type = type;
    }

    // __str__
    operator string() const
    {
        return type;
    }

    // Перегрузка оператора == для сравнения объектов
    bool operator==(const Type &type) const
    {
        return this->type == string(type);
    }
};

// Класс с типами данных
class By
{
public:
    static Type HEX;
    static Type BIN;
    static Type DEC;
    static Type STR;
};

Type By::HEX = Type("HEX");
Type By::BIN = Type("BIN");
Type By::DEC = Type("DEC");
Type By::STR = Type("STR");

// Функции вывода
template <typename T>
void printBytes(const T value, const Type &type = By::DEC)
{
    uint8_t size = sizeof(T);
    if (type == By::HEX)
        cout << "0x" << setfill('0') << setw(size * 2) << uppercase << hex << uint64_t(value) << " ";
    else if (type == By::BIN)
    {
        cout << "0b";
        for (int i = size * 8 - 1; i >= 0; i--)
            cout << ((value >> i) & 1);
        cout << " ";
    }
    else if (type == By::DEC)
        cout << dec << uint64_t(value) << " ";
    else if (type == By::STR)
    {
        for (int i = size - 1; i >= 0; --i)
            cout << static_cast<char>((value >> (8 * i)) & 0xFF);
        cout << " ";
    }
}

template <typename T>
void printBytes(const vector<T> values, const Type &type = By::DEC)
{
    for (int i = 0; i < values.size(); i++)
    {   
        if (i * sizeof(values[i]) >= 16)
            cout << endl;
        printBytes(values[i], type);
        
    }
}

// Функции конвертации
template <typename T>
vector<T> convert(const vector<uint8_t> &bytes)
{
    vector<T> result;
    for (size_t i = 0; i < bytes.size(); i += sizeof(T))
    {
        T value = 0;
        for (size_t j = 0; j < sizeof(T) && i + j < bytes.size(); ++j)
        {
            value |= static_cast<T>(bytes[i + j]) << (8 * (sizeof(T) - 1 - j));
        }
        result.push_back(value);
    }
    return result;
}

template <typename T>
vector<uint8_t> convert(const vector<T> &values)
{
    vector<uint8_t> bytes;
    for (const T &value : values)
    {
        for (int i = sizeof(T) - 1; i >= 0; --i)
            bytes.push_back(static_cast<uint8_t>(value >> (8 * i)));
    }
    return bytes;
}

// Функции записи
template <typename T>
void writeBytes(const string &path, const vector<T> &values)
{
    ofstream file(path, ios::binary);
    if (!file)
        throw runtime_error(path);
    vector<uint8_t> bytes = convert(values);
    file.write(reinterpret_cast<const char *>(bytes.data()), bytes.size());
    file.close();
}

// Функции чтения
template <typename T>
vector<T> readBytes(const string &path)
{
    ifstream file(path, ios::binary);
    if (!file)
        throw runtime_error(path);
    vector<uint8_t> bytes((istreambuf_iterator<char>(file)),
                          istreambuf_iterator<char>());
    return convert<T>(bytes);
}
