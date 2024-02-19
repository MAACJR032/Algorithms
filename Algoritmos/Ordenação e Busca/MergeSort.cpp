#include <iostream>
using namespace std;

void merge(int list[], int l, int m, int r, int tam);
void merge_sort(int list[], int l, int r);

int main()
{
    int list[4];

    for (int i = 0; i < 4; i++)
        cin >> list[i];
    
    int tam = sizeof(list)/sizeof(int);

    merge_sort(list, 0, tam-1);

    for (int i = 0; i < tam; i++)
        std::cout << list[i]<<" ";
    std::cout<<'\n';
    
    return 0;
}

void merge(int list[], int l, int m, int r, int tam)
{
    int i = l; // índice inicial da metade esquerda
    int j = m+1; // índice inicial da metade direita
    int k = l; // índice inicial do temporário

    int tmp[tam]; // temporário

    while (i <= m && j <= r)
    {
        if (list[i] <= list[j])
            tmp[k++] = list[i++];
        else
            tmp[k++] = list[j++];
    }
    
    while (i <= m)
    {
        tmp[k++] = list[i++]; // Copiando os elementos da metade esquerda p/ o temporário
    }
    while (j <= r)
    {
        tmp[k++] = list[j++]; // Copiando os elementos da metade direita p/ o temporário
    }
    
    for (int s = l; s <= r; s++)
        list[s] = tmp[s];
}

void merge_sort(int list[], int l, int r)
{
    if (l < r)
    {
        // Find the middle point.
        int m = (l+r)/2;

        merge_sort(list, l, m);
        merge_sort(list, m+1, r);
        merge(list, l, m, r, r+1);
    }
}