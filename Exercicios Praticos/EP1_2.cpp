#include <iostream>
#include <string.h>
using namespace std;

int BinarySearch (char list[][31], int l, int r, char keys[]);

int main()
{
    int size_estud;
    cin >> size_estud;

    char names[size_estud][31];

    for (int i = 0; i < size_estud; i++)
        cin >> names[i];
    
    int size_keys;
    cin >> size_keys;

    int index=0;
    char keys[size_keys][31];
    for (int i = 0; i < size_keys; i++)
    {
        cin >> keys[i];
        index = BinarySearch(names, 0, size_estud-1, keys[i]);

        if (index != -1) 
            cout << "+\n";
        else
            cout << "-\n";
    }

    return 0;
}

int BinarySearch (char list[][31],  int l, int r, char keys[])
{
    if (r >= l)
    {
        int m = (l+r)/2;

        if (strcmp(keys, list[m]) == 0)
            return m;
        else if (strcmp(keys, list[m]) < 0)
            return BinarySearch(list, l, m-1, keys);
        else
            return BinarySearch(list, m+1, r, keys);
    }
    return -1;
}