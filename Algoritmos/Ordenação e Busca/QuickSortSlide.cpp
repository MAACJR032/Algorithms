#include <iostream>
#include <chrono>

using namespace std::chrono;
int partition(int list[], int l, int r, int tam);
void quicksort(int list[], int l, int r, int size);
int BinarySearch(int list[], int l, int r, int key);

int main()
{
    int size;
    std::cin >> size;

    int list[size];
    for (int i = 0; i < size; i++)
    {
        list[i] = rand() % 10000005;
        std::cout << list[i] << " ";
    }
    std::cout << '\n';

    quicksort(list, 0, size-1, size);

    for (int i = 0; i < size; i++)
        std::cout << list[i] << " ";
    std::cout << '\n';

    int key;
    std::cin >> key;
    
    auto start = high_resolution_clock::now();
    int index = BinarySearch(list, 0, size-1, key);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    std::cout << duration.count() << " microssegundos" << '\n';
    std::cout << index << '\n';
    return 0;
}

int partition(int list[], int l, int r, int tam)
{
    int pivot = list[l], i = l, j = r+1;

    do
    {
        do
        {
            i++;
        } while (!(list[i] >= pivot || i >= r));

        do
        {
            j--;
        } while (!(list[j] <= pivot));

        std::swap(list[i], list[j]);

    } while (!(i >= j));
    
    std::swap(list[i], list[j]);
    std::swap(list[l], list[j]);

    return j;
}

void quicksort(int list[], int l, int r, int size)
{
    if (l < r)
    {
        int s = partition(list, l, r, size);
        quicksort(list, l, s-1, size);
        quicksort(list, s+1, r, size);
    }
}

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