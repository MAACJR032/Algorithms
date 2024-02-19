#include <iostream>

int partition(int list[], int l, int r, int tam);
void quicksort(int list[], int l, int r, int size);

int main()
{
    int entradas, size;
    std::cin >> entradas;

    for (int i = 0; i < entradas; i++)
    {
        std::cin >> size;
        int list[size];
        for (int i = 0; i < size; i++)
            std::cin >> list[i];

        quicksort(list, 0, size-1, size);

        for (int i = 0; i < size; i++)
            std::cout << list[i] << " ";
        std::cout << '\n';
    }
    
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
        } while (!(list[i] <= pivot || i >= r));

        do
        {
            j--;
        } while (!(list[j] >= pivot));

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