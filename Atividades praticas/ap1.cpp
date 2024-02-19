#include <iostream>
using namespace std;

void merge(int list[], int l, int m, int r, int tam);
void merge_sort(int list[], int l, int r);

int main()
{
    int c = 0, count=0;
    
    do
    {
        // cout << "Numero de casos(1-10): ";
        cin >> c;
    } while (c > 10 || c < 1);
    
    do
    {
        int n;
        cin >> n;

        int list[n];

        for (int i = 0; i < n; i++)
            cin >> list[i];
        
        int tam = sizeof(list)/sizeof(int);

        merge_sort(list, 0, tam-1);

        for (int i = 0; i < tam; i++)
            std::cout << list[i]<<" ";
        std::cout<<'\n';

        count++;
    } while (count < c);
    
    return 0;
}

void merge(int list[], int l, int m, int r, int tam)
{
    int i = l; // índice inicial da metade esquerda
    int j = m+1; // índice inicial da metade direita
    int k = l; // índice inicial da lista temporária

    int tmp[tam]; // lista temporária

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

void merge_sort(int list[], int l, int r)
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