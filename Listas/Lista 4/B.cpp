#include <iostream>
#include <cmath>
using namespace std;

void Heapify(int arr[], int size, int i)
{
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if (left < size && arr[left] < arr[smallest])
        smallest = left;
    if (right < size && arr[right] < arr[smallest])
        smallest = right;
    if (smallest != i)
    {
        swap(arr[i], arr[smallest]);
        Heapify(arr, size, smallest);
    }
}

void BuildHeap(int arr[], int size)
{
    for (int i = (size/2) - 1; i >= 0; i--)
        Heapify(arr, size, i);
}

void HeapSort(int arr[], int size)
{
    BuildHeap(arr, size);
    for (int i = size-1; i >= 0; i--)
    {
        swap(arr[0], arr[i]);
        Heapify(arr, i, 0);
    }
}

long long CalculateCost(int arr[], int size)
{
    long long cost = 0;

    while (size > 1)
    {
        int min1 = arr[0];
        size--;
        swap(arr[0], arr[size]);
        Heapify(arr, size, 0);

        int min2 = arr[0];
        size--;
        swap(arr[0], arr[size]);
        Heapify(arr, size, 0);

        cost += (min1 + min2);
        arr[size] = min1 + min2;
        size++;
        Heapify(arr, size, 0);
    }

    return cost;
}

int main()
{
    int n;
    cin >> n;

    while (n != 0)
    {
        int nums[5003];
        for (int i = 0; i < n; i++)
            cin >> nums[i];

        BuildHeap(nums, n);
        long long cost = CalculateCost(nums, n);

        cout << cost << '\n';
        cin >> n;
    }

    return 0;
}