#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

using namespace std;

class Type
{
private:
    string _type;

public:
    // Конструктор
    Type(string _type)
    {
        this->_type = _type;
    }

    // Геттер
    string getType() const
    {
        return _type;
    }

    // Перегрузка оператора == для сравнения объектов
    bool operator==(const Type &other) const
    {
        return _type == other.getType();
    }
};

// Класс с типами данных
class Types
{
public:
    static Type HEX;
    static Type BIN;
    static Type DEC;
};

Type Types::HEX = Type("HEX");
Type Types::BIN = Type("BIN");
Type Types::DEC = Type("DEC");

// Функции вывода
template <typename T>
void printBytes(T value, const Type &type = Types::DEC)
{
    if (type == Types::HEX)
        cout << "0x" << setfill('0') << setw(sizeof(T) * 2) << uppercase << hex << uint64_t(value) << " ";
    else if (type == Types::BIN)
    {
        cout << "0b";
        for (int i = sizeof(T) * 8 - 1; i >= 0; i--)
            cout << ((value >> i) & 1);
        cout << " ";
    }
    else
        cout << dec << uint64_t(value) << " ";
}

template <typename T>
void printBytes(vector<T> values, const Type &type = Types::DEC)
{   
    int count = 0;
    for (const T &value : values){
        printBytes(value, type);
        count += 1;
        if (count % 16 == 0)
            cout << endl;
    }
        
}

// Функции записи
template <typename T>
void writeBytes(string path, vector<T> values)
{
    ofstream file(path, ios::binary);
    for (T value : values)
    {
        file.write(reinterpret_cast<const char *>(&value), sizeof(T));
    }
    file.close();
}
