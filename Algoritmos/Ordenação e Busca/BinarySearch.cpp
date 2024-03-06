#include <iostream>
#include <chrono>
using namespace std::chrono;

int BinarySearch(int list[], int key, int size);
int main()
{
    int size, key;
    std:: cin >> size >> key;

    int list[size];
    for (int i = 0; i < size; i++)
        std::cin >> list[i];

    // Ordenar

    int found = 0;

    auto start = high_resolution_clock::now();
    found = BinarySearch(list, key, size);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << duration.count() << " microssegundos" << '\n';

    std::cout << found << '\n';
    return 0;
}

int BinarySearch(int list[], int key, int size)
{
    int l = 0, r = size-1;

    do
    {
        int m = (l+r)/2;

        if (key == list[m])
            return m;
        else if (key < list[m])
            r = m-1;
        else
            l = m+1;
    } while (l <= r);
    
    return -1;
}