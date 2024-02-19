#include <iostream>
#include <string.h>
#include <string>
using namespace std;

void merge(int list[], string names[], int l, int r, int size);
void mergesort(int list[], string names[], int l, int r, int size);

int main()
{
    int size;
    cin >> size;

    string names[size];
    int time[size];

    for (int i = 0; i < size; i++)
        cin >> names[i] >> time[i];

    mergesort(time, names, 0, size-1, size);

    for (int i = 0; i < size; i++)
        cout << names[i] << " " << time[i] << '\n';

    return 0;
}

void merge(int list[], string names[], int l, int r, int size)
{
    int m = (l+r)/2;
    int i = l, tmp[size];
    string tmp2[size];
    
    while (i <= r)
    {
        tmp[i] = list[i];
        tmp2[i] = names[i];
        i++;
    }

    int curr = l, i1 = l, i2 = m+1;
    while (curr <= r)
    {
        if (i1 == m+1)
        {
            memcpy(&list[curr], &tmp[i2], (r-i2+1)*sizeof(int));
            memcpy(&names[curr], &tmp2[i2], sizeof(char)*(r-i2+1)*31);
            break;
            // names[curr].assign(tmp2[i2]);
            // list[curr] = tmp[i2++];
        }
        else if (i2 > r)
        {
            memcpy(&list[curr], &tmp[i1], (m-i1+1)*sizeof(int));
            memcpy(&names[curr], &tmp2[i1], sizeof(char)*(m-i1+1)*31);
            break;
            // names[curr].assign(tmp2[i1]);
            // list[curr] = tmp[i1++];
        }
        else if (tmp[i1] < tmp[i2])
        {
            names[curr].assign(tmp2[i1]);
            list[curr] = tmp[i1++];
        }
        else if (tmp[i1] == tmp[i2])
        {
            names[curr].assign(tmp2[i1]);
            list[curr] = tmp[i1++];
        }
        else
        {
            names[curr].assign(tmp2[i2]);
            list[curr] = tmp[i2++];
        }
        curr++;
    }
}
void mergesort(int list[], string names[], int l, int r, int size)
{
    if (l < r)
    {
        int m = (l+r)/2;
        mergesort(list, names, l, m, size);
        mergesort(list, names, m+1, r, size);
        merge(list, names, l, r, size);
    }
}