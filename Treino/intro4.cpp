#include <iostream>

int main()
{
    // null pointer
    int *pointer = nullptr;
    int x = 123;

    pointer = &x;

    if (pointer == nullptr)
        std::cout << "address was not assigned!\n";
    else
    { 
        std::cout << "address was assigned!\n";
        std::cout << *pointer << '\n';
    }


    // Alocação Dinamica:
    int *pNum = NULL;

    // malloc
    pNum = new int; // alocou espaço para 1 int

    *pNum = 21;
    std::cout << "address: " << pNum << '\n';
    std::cout << "value: " << *pNum << '\n';

    // free
    delete pNum;

    // Alocando dinamicamente um array
    int *pGrades = NULL;
    int size;

    std::cout << "How many grades you want to enter in: ";
    std::cin >> size;

    pGrades = new int[size];

    for (int i = 0; i < size; i++)
    {
        std::cout << "Enter grade #" << i+1 << ": ";
        std::cin >> *(pGrades + i);
    }
    
    std::cout << "Grades:\n";
    for (int i = 0; i < size; i++)
        std::cout << *(pGrades + i) << " ";
    std::cout << '\n';

    // Para usar delete com array deve se usar "delete[]"
    delete[] pGrades;
    
    return 0;
}