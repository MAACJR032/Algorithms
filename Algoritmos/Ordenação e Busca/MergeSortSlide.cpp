#include <iostream>
#include <cstring>
#include <chrono>

using namespace std::chrono;
void merge(int list[], int l, int r, int size);
void mergesort(int list[], int l, int r, int size);

int main()
{
    int size;
    std::cin >> size;

    int list[size];
    for (int i = 0; i < size; i++)
    {
        list[i] = rand() % 100000;
        // std::cout << list[i] << " ";
    }
    std::cout << '\n';

    auto start = high_resolution_clock::now();
    mergesort(list, 0, size-1, size);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << duration.count() << " microssegundos" << '\n';
    // for (int i = 0; i < size; i++)
    //     std::cout << list[i] << " ";
    // std::cout << '\n';

    return 0;
}

void merge(int list[], int l, int r, int size)
{
    int m = (l+r)/2;
    int i = l, tmp[size];

    
    // while (i <= r)
    // {
    //     tmp[i] = list[i];
    //     i++;
    // }
    std::memcpy(tmp, list, sizeof(tmp));

    int curr = l, i1 = l, i2 = m+1;
    while (curr <= r)
    {
        if (i1 == m+1){
            std::memcpy(&list[curr], &tmp[i2], (r-i2+1)*sizeof(int));
            break;
            // std::memcpy(&list[curr], &tmp[i2], (r-i2+1)*sizeof(int));
            // break;
            // list[curr] = tmp[i2++];
        }    
        else if (i2 > r){
            std::memcpy(&list[curr], &tmp[i1], (m-i1+1)*sizeof(int));
            break;
            // std::memcpy(&list[curr], &tmp[i1], (m-i1+1)*sizeof(int));
            // break;
            // list[curr] = tmp[i1++];
        }
        else if (tmp[i1] <= tmp[i2])
            list[curr] = tmp[i1++];
        else
            list[curr] = tmp[i2++];
        curr++;
    }
}
void mergesort(int list[], int l, int r, int size)
{
    if (l < r)
    {
        int m = (l+r)/2;
        mergesort(list, l, m, size);
        mergesort(list, m+1, r, size);
        merge(list, l, r, size);
    }
}
