#include <iostream>
#include <bitset>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
    // Определение параметров
    int temp;
    cout << "Enter the first seed: ";
    cin >> temp;
    unsigned int polinom1(temp);

    cout << "Enter the second seed: ";
    cin >> temp;
    unsigned int polinom2(temp);
    
    cout << "polinom1 before: " << polinom1 << endl;
    bool bit13 = (polinom1 >> 13) & 1;
    cout << "bit13: " << bit13 << endl;
    cout << "polinom1 after: " << polinom1 << endl;
    
    system("pause");
    return 0;
}
