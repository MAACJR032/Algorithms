#include <iostream>

int partition(int list[], int l, int r, int tam);
void quicksort(int list[], int l, int r, int size);
int BinarySearch(int list[], int key, int size, int *qtd);

int main()
{
    int n=0, k=0;

    std::cin >> n >> k;
    int list[n];

    for (int i = 0; i < n; i++)
        std::cin >> list[i];

    int x = 0;
    int *qtd = &x;

    quicksort(list, 0, n-1, n);
    BinarySearch(list, k, n, qtd);
    
    std::cout << x << '\n';
    
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

int BinarySearch(int list[], int key, int size, int *qtd)
{
    int l=0, r = 1;
    do
    {
        do
        {
            if (list[r] - list[l] == key)
                *(qtd)+=1;
            r++;
        } while (list[r] - list[l] <= key);        
        l++;
        r = l+1;
    } while (l < size-1);
    return -1;
}