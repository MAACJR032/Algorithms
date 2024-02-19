#include <iostream>
using namespace std;

void merge(long long list[], int l, int m, int r, int tam);
void merge_sort(long long list[], int l, int r);

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

    merge_sort(list, 0, n-1);

    cin >> m;
    int list2[m];

    for (int i = 0; i < m; i++)
    {
        cin >> list2[i];
        long long result = soma - list[n-list2[i]];
        printf("%lld\n", result);
    }

    return 0;
}

void merge(long long list[], int l, int m, int r, int tam)
{
    int i = l; // índice inicial da metade esquerda
    int j = m+1; // índice inicial da metade direita
    int k = l; // índice inicial da lista temporária

    long long tmp[tam]; // lista temporária

    // Enquanto o index da esq for menor que o index do meio e o index da direita for menor que o último index
    while (i <= m && j <= r)
    {
        // Comparar qual elemento é menor entre e colocá-los na lista temporária
        if (list[i] <= list[j])
            tmp[k++] = list[i++];
        else
            tmp[k++] = list[j++];
    }
    
    // Copiar os restantes dos elementos da metade esquerda ou da metade direita para a lista temporária
    while (i <= m)
    {
        tmp[k++] = list[i++]; // Copiando os elementos da metade esquerda p/ o temporário
    }
    while (j <= r)
    {
        tmp[k++] = list[j++]; // Copiando os elementos da metade direita p/ o temporário
    }
    
    // Copia de volta do temporário p/ a lista original
    for (int s = l; s <= r; s++)
        list[s] = tmp[s];
}

void merge_sort(long long list[], int l, int r)
{
    if (l < r)
    {
        // Encontrando o ponto do meio
        int m = (l+r)/2;

        merge_sort(list, l, m); // Ordenando a metade esquerda
        merge_sort(list, m+1, r); // Ordenando a metade direita
        merge(list, l, m, r, r+1); // Ordenando ambas as metades
    }
}