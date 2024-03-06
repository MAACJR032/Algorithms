#include <iostream>
#include <list>
#include <vector>
#include <cstring>
using namespace std;

template<typename K, typename V>
class PAIR
{
    public:
        K first;
        V second;
};

class HashTable
{
    private:
        static const int hashGroups = 10; // Nº de listas q vão ser usadas
        // vector<PAIR<int, string>> table[hashGroups];
        list<PAIR<string, int>> table[hashGroups]; // List 1, index 0, list 2, index 1...

    public:
        bool isEmpty()
        {
            int sum = 0;
            for (int i = 0; i < hashGroups; i++)
            { 
                sum += table[i].size();
                if (sum != 0)
                    return true;
            }
            return false;
        }

        int HashFunction(string key)
        {
            int s = key.length();
            int sum = 0;
            for (int i = 0; i < s-1; i++)
                sum += (key[i]);
            
            return abs(sum)%hashGroups;
        }

        void insert(string key, int value)
        {
            int hashValue = HashFunction(key);
            auto& cell = table[hashValue];
            auto curr = begin(cell);
            bool KeyExist = false;

            for (; curr != end(cell); curr++)
            {
                if (curr->first == key)
                {
                    KeyExist = true;
                    curr->second = value;
                    break;
                }
            }
            if (!KeyExist)
                cell.emplace_back(key, value);

            return;   
        }

        void Remove(string key)
        {
            int hashValue = HashFunction(key);
            auto& cell = table[hashValue];
            auto curr = begin(cell);
            bool KeyExist = false;

            for (; curr != end(cell); curr++)
            {
                if (curr->first == key)
                {
                    KeyExist = true;
                    curr = cell.erase(curr);
                    break;
                }
            }

            return;
        }

        // int search(string key);

        void print()
        {
            for (int i{}; i < hashGroups; i++)
            {
                if (table[i].size() == 0)
                    continue;
                
                for (auto curr = table[i].begin(); curr != table[i].end(); curr++)
                    cout << "Key: " << curr->first << " Value: " << curr->second << '\n';
            }
            return;
        }
};

int main()
{
    HashTable HT;

    if (HT.isEmpty() == true)
        cout << "Its empty\n";
    else
        cout << "Not empty\n";

    return 0;
}