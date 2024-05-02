#include <iostream>
#include <fstream>
#include "./common/io.cpp"
#include "./common/generator.cpp"

using namespace std;

int main()
{
    long long int firstSeed, secondSeed;
    cout << "\n# ------- Start keygen ------- #\n";
    cout << "\nEnter integers seeds to generate the key:\nEnter first seed: ";
    cin >> firstSeed;
    cout << "Enter second seed: ";
    cin >> secondSeed;

    // Генерируем ключ
    Generator generator(firstSeed, secondSeed);
    vector<uint8_t> key = generator.byteSequence(7);

    // Записываем биты ключа в файл
    writeBytes("./key.key", key);
    cout << "The key has been successfully generated and saved to the key.key file\nYour key: ";
    printBytes(key, Types::HEX);
    
    system("pause");
    return 0;
}
