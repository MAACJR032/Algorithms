#include <iostream>
#include <list>
using namespace std;

bool par(int x)
{
    return ((x%2) == 0);
}
int main()
{
    // Diferentes formas de iniciar uma lista:
    list<int> list1; // Lista vazia
    list<int> list2(10, 0); // insere 10 vezes o nº 0
    list<int> list3(list2); // lista3 é igual a lista2
    list<int> list4 = {1, 2, 3, 4}; // inicializar com elementos

    for (auto i = list4.begin(); i != list4.end() ; i++)
        cout << *i << " ";
    cout << endl;

    cout << "tamanho: " << list4.size() << endl;
    cout << "capacidade maxima: " << list4.max_size() << endl;
    cout << "1o elemento: " << list4.front() << endl;
    cout << "ultimo elemento: " << list4.back() << endl;

    if(list4.empty())
        cout << "lista vazia\n";
    else
        cout << "lista nao esta vazia\n";
    

    // Inserir e Remover:

    // Insere 10 elementos 0, substituindo, os elementos existentes, caso a lista ñ esteja vazia
    list2.assign(10, 0);

    // Insere a lista 4 na 2
    list2.assign(list4.begin(), list4.end());

    // Insere no fim da lista
    list4.push_back(8);

    // Insere no início da lista
    list4.push_front(21);

    for (auto x:list4)
        cout << x << " ";
    cout << endl;

    // Remove no fim da lista
    list4.pop_back();

    // Remove no início da lista
    list4.pop_front();

    for (auto x:list4)
        cout << x << " ";
    cout << endl;

    // Esvaziando lista:
    while (!list4.empty())
        list4.pop_back();
    
    for (auto x:list4)
        cout << x << " ";
    cout << endl;
    
    // 
    list<int>::iterator curr; // Declarando cursor
    curr = list4.begin(); // cursor aponta para o começo
    curr++; // next

    list4.insert(curr, 8); // insere na 2ª posição
    cout << *curr << '\n';

    for (auto x:list4)
        cout << x << " ";
    cout << endl;

    curr--;
    list4.erase(curr); // remove o elemento da 2ª posição
    for (auto x:list4)
        cout << x << " ";
    cout << endl;

    list2.resize(5); // Redimensiona para 5 elementos
    list2.clear(); // Deleta tudo

    list4.emplace(list4.begin(), 9);
    for (auto x:list4)
        cout << x << " ";
    cout << endl;

    list4.emplace_back(11);
    for (auto x:list4)
        cout << x << " ";
    cout << endl;

    list4.emplace_front(17);
    for (auto x:list4)
        cout << x << " ";
    cout << endl;

    list4.remove(11); // Remove todos os elem. 11
    list4.remove_if(par); // Remove todos os elem. pares

    for (auto x:list4)
        cout << x << " ";
    cout << endl;

    list4.sort(); // Ordena de forma crescente
    for (auto x:list4)
        cout << x << " ";
    cout << endl;

    list4.unique(); // Remove elem. com + de 1 ocorrencia
    list1.merge(list4); // Une os elem. de 1 com 4 ordenadamente

    list4.reverse(); // Inverte a lista

    return 0;
}