#include <iostream>
using namespace std;

// Se não assinalar explicitamente valor para cada um, a ordem iniciará será 0, 1, 2, ..., assim como está abaixo
enum Day {segunda = 0, terca = 1, quarta = 2, quinta = 3};

int main()
{
    Day hoje = quarta;

    switch (hoje)
    {
        case segunda:
            cout << "Eh segunda\n"; break;
        case terca:
            cout << "Eh terca\n"; break;
        case quarta:
            cout << "Eh quarta\n"; break;
        case quinta:
            cout << "Eh quinta\n"; break;
    }

    return 0;
}