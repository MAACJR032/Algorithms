#include <iostream>
#include <cmath>
using namespace std;

void Heapify(int H[], int size)
{
    for (int i = floor(size/2); i >= 0; i--)
    {
        int k = i;
        int v = H[k];
        bool heap = false;

        while ((!heap) && (2*k <= size))
        {
            int j = 2*k;

            if (j < size)
                if (H[j] < H[j+1])
                    j++;
            if (v >= H[j])
                heap = true;
            else
            {
                H[k] = H[j];
                k = j;
            }
        }
        H[k] = v;
    }
}

void Dequeue(int H[], int *size)
{
    swap(H[0], H[(*size)]);
    cout << H[(*size)] << ' ';
    // int aux = H[(*size)];
    (*size)--;

    Heapify(H, (*size));
}

int main()
{
    int h[] = {2, 9, 7, 6, 5, 8, 10};

    Heapify(h, 7);

    for (int i = 0; i < 7; i++)
        cout << h[i] << ' ';
    cout << endl;
    
    int size = 7;
    for (int i = 0; i < 7; i++)
        Dequeue(h, &size);
    cout << endl;

    for (int i = 0; i < 8; i++)
        cout << h[i] << ' ';
    cout << endl;
    return 0;
}