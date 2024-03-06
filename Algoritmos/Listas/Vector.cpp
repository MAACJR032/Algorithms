#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> num1, num2;
    int size;

    // Inserir no fim do vector
    num1.push_back(1);
    num1.push_back(2);
    num1.push_back(3);
    num1.push_back(4);

    num2.push_back(5);
    num2.push_back(6);
    num2.push_back(7);
    num2.push_back(8);

    // Swap também funciona para vector
    // num1.swap(num2);

    size = num1.size();
    cout << "Tamanho: " << size << '\n';

    for (int i = 0; i < size; i++)
        cout << num1[i] << " ";
    cout << '\n';

    for (int i = 0; i < size; i++)
        cout << num2[i] << " ";
    cout << '\n';   
    
    cout << "Primeiro elemento: " << num1.front() << '\n';
    cout << "Ultimo elemento: " << num1.back() << '\n';

    // at serve para acessar um índice do vector
    cout << "Elemento do meio: " << num1.at(size/2) << '\n';

    num1.at(2) = 20;
    return 0;
}