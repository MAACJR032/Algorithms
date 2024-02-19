#include <iostream>

void Swap(int* a, int* b);
int Partition(int array[], int begin, int end);
void QuickSort(int array[], int begin, int end);

int main()
{
    int size=0;

    std::cin >> size;
    int list[size];

    for (int i = 0; i < size; i++)
        std::cin >> list[i];
    
    QuickSort(list, 0, size-1);

    for (int i = 0; i < size; i++)
        std::cout << list[i] << " ";
    std::cout << '\n';

    return 0;
}

void Swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int Partition(int array[], int begin, int end)
{
    int pivot = array[begin];
    int i = begin, j = end + 1;
    do
    {
        do
        {
            i++;
        }while(pivot > array[i]);
        
        do
        {
            j--;
        }while(pivot < array[j]);

        Swap(&array[i], &array[j]);
    }while(i < j);
    Swap(&array[i], &array[j]);
    Swap(&array[begin], &array[j]);
    return j;
}

void QuickSort(int array[], int begin, int end)
{
    if(begin < end)
    {
        int pivot = Partition(array, begin, end);
        QuickSort(array, begin, pivot - 1);
        QuickSort(array, pivot + 1, end);
    }
}
