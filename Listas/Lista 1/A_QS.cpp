#include <iostream>
using namespace std;

int partition(long long list[], int l, int r, int tam);
void quicksort(long long list[], int l, int r, int size);

int main()
{
    int n=0, m=0;
    long long soma=0;

    cin >> n;
    long long list[n];

    for (int i = 0; i < n; i++)
    {
        cin >> list[i];
        soma+=list[i];
    }

    quicksort(list, 0, n-1, n);
    
    cin >> m;
    int list2[m];

    for (int i = 0; i < m; i++)
    {
        cin >> list2[i];
        // long long result = soma - list[n-list2[i]];
        // printf("%lld\n", result);
        cout << soma - list[n-list2[i]] << '\n';
    }

    return 0;
}

int partition(long long list[], int l, int r, int tam)
{
    long long pivot = list[l], i = l, j = r+1;

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

void quicksort(long long list[], int l, int r, int size)
{
    if (l < r)
    {
        int s = partition(list, l, r, size);
        quicksort(list, l, s-1, size);
        quicksort(list, s+1, r, size);
    }
}