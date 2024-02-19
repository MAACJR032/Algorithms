#include <iostream>

void merge(long long list[], int l, int r, int size);
void mergesort(long long list[], int l, int r, int size);

int main()
{
    int n=0, m=0;
    long long soma=0;

    std::cin >> n;
    long long list[n];

    for (int i = 0; i < n; i++)
    {
        std::cin >> list[i];
        soma+=list[i];
    }

    mergesort(&list[0], 0, n-1, n);
    
    std::cin >> m;
    int list2[m];

    for (int i = 0; i < m; i++)
    {
        std::cin >> list2[i];
        std::cout << soma - list[n-list2[i]] << '\n';
    }
    
    return 0;
}

void merge(long long list[], int l, int r, int size)
{
    int m = (l+r)/2;
    int i = l, tmp[size];

    
    while (i <= r)
    {
        tmp[i] = list[i];
        i++;
    }

    int curr = l, i1 = l, i2 = m+1;
    while (curr <= r)
    {
        if (i1 == m+1)
            list[curr] = tmp[i2++];
        else if (i2 > r)
            list[curr] = tmp[i1++];
        else if (tmp[i1] <= tmp[i2])
            list[curr] = tmp[i1++];
        else
            list[curr] = tmp[i2++];
        curr++;
    }
}
void mergesort(long long list[], int l, int r, int size)
{
    if (l < r)
    {
        int m = (l+r)/2;
        mergesort(list, l, m, size);
        mergesort(list, m+1, r, size);
        merge(list, l, r, size);
    }
}
