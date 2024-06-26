#include <iostream>
using namespace std;

void Swap(int *a, int *b);
int Partition(int array[], int begin, int end);
void QuickSort(int array[], int begin, int end);

int main()
{
    int size = 0;

    cin >> size;
    int list[size];

    for (int i = 0; i < size; i++)
        cin >> list[i];
    
    QuickSort(list, 0, size-1);

    for (int i = 0; i < size; i++)
        cout << list[i] << " ";
    cout << '\n';

    return 0;
}

int Partition(int array[], int begin, int end)
{
    int pivot = array[begin];
    int i = begin, j = end + 1;
    do
    {
        do {
            i++;
        } while(pivot > array[i]);
        
        do {
            j--;
        } while(pivot < array[j]);
    
        swap(array[i], array[j]);
    } while(i < j);

    swap(array[i], array[j]);
    swap(array[begin], array[j]);

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
