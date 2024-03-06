#include <iostream>
#include <chrono>
using namespace std::chrono;

int BinarySearch(int list[], int l, int r, int key)
{
    if (r >= l)
    {
        int m = (l+r)/2;

        if (key == list[m])
            return m;
        else if (key < list[m])
            return BinarySearch(list, l, m-1, key);
        else
            return BinarySearch(list, m+1, r, key);
    }
    else
        return -1;
}

int main()
{
    int size;
    std::cin >> size;

    int list[size];
    for (int i = 0; i < size; i++)
        std::cin >> list[i];
    
    int index, key;
    std::cin >> key;

    auto start = high_resolution_clock::now();
    index = BinarySearch(list, 0, size-1, key);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << duration.count() << " microssegundos" << '\n';

    if (index == -1)
        std::cout << "Element not found\n";
    else
        std::cout << "Element at index: " << index << '\n';

    return 0;
}