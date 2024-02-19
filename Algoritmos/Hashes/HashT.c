#include <stdio.h>
#include <stdlib.h>

#define TAM 31

void CreateHash(int t[])
{
    for (int i = 0; i < TAM; i++)
        t[i] = 0;   
}

int HashFunction(int key)
{
    return abs(key%TAM);
}

int search(int t[], int key)
{
    int index = HashFunction(key);

    while (t[index] != 0)
    {
        if (t[index] == key)
        {
            // Retornar indice
            return t[index];
        }
        else
            index = HashFunction(index+1);
    }
    return 0;
}

void insert(int t[], int val)
{
    int index = HashFunction(val);
    int aux;
    while (t[index] != 0)
    {   
        aux = search(t, val);
        if (aux != 0)
            return;
        index = HashFunction(index+1);
    }
    t[index] = val;
}

void print(int t[])
{
    for (int i = 0; i < TAM; i++)
        printf("%d - %d\n", i, t[i]);
}

int main()
{
    int hash[TAM];
    int x, found;
    int op=0;

    CreateHash(hash);
    do
    {
        printf("1-Inserir\n2-Buscar\n3-Imprimir\n4-Sair\n");
        scanf("%d", &op);

        switch (op)
        {
            case 1:
                scanf("%d", &x);
                insert(hash, x);
                break;
            case 2:
                scanf("%d", &x);
                found = search(hash, x);
                
                if (found != 0)
                    printf("Encontrado\n");
                else
                    printf("Nao Encontrado\n");
                break;
            case 3:
                print(hash);
                break;
            case 4:
                break;
            default:
                break;
        }
    } while (op != 4);
    
    return 0;
}