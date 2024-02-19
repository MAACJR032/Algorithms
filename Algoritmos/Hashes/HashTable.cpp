#include <iostream>
#include <list>
#include <cstring>
using namespace std;

class HashTable
{
    private:
        list<int> *array;
        int size;

        int GetHashPos(int element)
        {
            return (abs(element%10));
        }

    public:
        HashTable(int size) : size(size)
        {
            array = new list<int>[size];
        }
        ~HashTable()
        {
            Clear();
            delete[] array;
        }

        void Clear()
        {
            for (int i = 0; i < size; i++)
                array[i].clear();
        }

        void insert(int element)
        {
            array[GetHashPos(element)].emplace_back();
        }

        list<int> &GetList(int index)
        {
            if (index >= 0 && index < size)
                return array[index];
        }
};

int main()
{
    int tam;
    cin >> tam;

    HashTable h(tam);

    for (int i = 0; i < tam; i++)
    {
        int tmp;
        cin >> tmp;
        
        h.insert(tmp);
    }
    
    for (int i = 0; i < tam; i++)
    {
        
        
    }

    return 0;
}