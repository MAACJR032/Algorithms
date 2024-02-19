#include <iostream>

int BinarySearch(int list[], int keys, int size);

int main()
{
    int size;
    std:: cin >> size;

    int list[size];
    for (int i = 0; i < size; i++)
        std::cin >> list[i];

    int m;
    std::cin >> m;
    int keys[m];

    for (int i = 0; i < m; i++)
        std:: cin >> keys[i];
    
    int found = 0;
    for (int i = 0; i < m; i++)
    {
        found = BinarySearch(list, keys[i], size);
        if (found != -1)
            std::cout << found << '\n';
        else 
            std::cout << "x\n";
    }
    
    return 0;
}

int BinarySearch(int list[], int key, int size)
{
    int l=0, r = size-1;

    do
    {
        int m = (l+r)/2;

        if (key == list[m])
            return m;
        else if (key < list[m])
            r = m-1;
        else
            l = m+1;
    } while (l <= r);
    
    return -1;
}