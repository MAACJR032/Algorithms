#include <iostream>

void merge(int list[], int l, int m, int r, int size);
void merge_sort(int list[], int l, int r);

int main()
{
    int *pGrades = NULL;
    int size;

    std::cout << "How many grades you want to enter in: ";
    std::cin >> size;

    pGrades = new int[size];

    for (int i = 0; i < size; i++)
    {
        std::cout << "Enter grade #" << i+1 << ": ";
        std::cin >> pGrades[i];
    }
    
    std::cout << "Grades:\n";
    for (int i = 0; i < size; i++)
        std::cout << pGrades[i] << " ";
    std::cout << "\n\n";

    merge_sort(pGrades, 0, size-1);

    std::cout << "Sorted Grades:\n";
    for (int i = 0; i < size; i++)
        std::cout << *(pGrades + i) << " ";
    std::cout << '\n';

    delete[] pGrades;

    return 0;
}

void merge(int list[], int l, int m, int r, int size)
{
    int i = l, j = m+1, k = l;

    int tmp[size];

    while (i <= m && j <= r)
    {
        if (list[i] <= list[j])
            tmp[k++] = list[i++];
        else
            tmp[k++] = list[j++];
    }
    
    while (i <= m)
    {
        tmp[k++] = list[i++];
    }
    while (j <= r)
    {
        tmp[k++] = list[j++];
    }
    
    for (int s = l; s <= r; s++)
        list[s] = tmp[s];
}

void merge_sort(int list[], int l, int r)
{
    if (l < r)
    {
        int m = (l+r)/2;

        merge_sort(list, l, m);
        merge_sort(list, m+1, r);
        merge(list, l, m, r, r+1);
    }
}