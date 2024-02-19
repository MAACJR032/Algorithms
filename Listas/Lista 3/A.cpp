#include <iostream>
#include <string>
using namespace std;

#define MAX 101

class HashTable
{
    private:
        int Hashing(string key)
        {
            int h = 0;

            for (int i = 0; (i < key.length()); i++)
                h += key[i] * (i+1);
            h *= 19;

            return (h%MAX);
        }
        int find(string key, int index)
        {
            int tmp = index;
            for (int i = 0; i < 20; i++)
            {
                if (t[tmp] == key)
                    return tmp;
                else
                    tmp = colision(key, index, i+1, tmp);
            }
            return -1;
        }
        int colisionADD(string key, int index, int j, int tmp)
        {
            int col = (index + j*j + 23*j) % MAX;
            if ((t[col] == "") || (t[col] == "01"))
                return col;
            else
                return tmp;
        }
        int colision(string key, int index, int j, int tmp)
        {
            int col = (index + j*j + 23*j) % MAX;
            if ((t[col] == key))
                return col;
            else
                return tmp;
        }
    public:
        string t[MAX];
        int count;
        HashTable()
        {
            for (int i = 0; i < MAX; i++)
                t[i] = "";
            count = 0;
        }
        void insert(string key)
        {
            int index = Hashing(key), aux, tmp;
            tmp = index;

            aux = find(key, index);
            if (aux >= 0)
                return;
            else if (aux < 0)
            {
                for (int i = 0; i < 20; i++)
                {
                    if ((t[tmp] == "") || (t[tmp] == "01"))
                    {
                        t[tmp] = key;
                        count++;
                        return;
                    }
                    else
                        tmp = colisionADD(key, index, i+1, tmp);
                }
            }    
        }
        void Delete(string key)
        {
            int index = Hashing(key), aux, tmp;
            tmp = index;

            aux = find(key, index);
            if (aux < 0)
                return;
            else
            {
                // for (int i = 0; i < 20; i++)
                // {
                //     if (t[tmp] == key)
                //     {
                //         t[tmp] = "01";
                //         count--;
                //         return;
                //     }
                //     else
                //         tmp = colision(key, index, i+1, tmp);
                // }
                t[aux] = "01";
                count--;
                return;
            }
        }
        void print()
        {
            cout << count << '\n';
            for (int i = 0; i < MAX; i++)
            {
                if (t[i] == "01")
                    t[i] = "";
                
                if((t[i] != "") && (t[i] != "01"))
                {
                    cout << i << ':' << t[i] << '\n';
                    t[i] = "";
                }
            }
        }
};

int main()
{
    HashTable t = HashTable();
    string key, op;
    int cases;
    cin >> cases;

    for (int i = 0; i < cases; i++)
    {
        int tests;
        cin >> tests;

        for (int i = 0; i < tests; i++)
        {
            cin >> key;
            op = key.substr(0, 4);

            key.erase(0, 4);
            if (key == "")
                continue;
            
            if (op.compare("ADD:") == 0)
                t.insert(key);
            else if (op.compare("DEL:") == 0)
                t.Delete(key);
        }
        if (tests != 0)
            t.print();

        t.count = 0;
    }
    return 0;
}