#include <iostream>
#include <cmath>
using namespace std;

void BottomUp(int arr[], int size)
{
    for (int i = floor(size/2); i >= 1; i--)
    {
        int k = i;
        int v = arr[k];
        bool heap = false;

        while ((!heap) && (2*k <= size))
        {
            int j = 2*k;

            if (j < size)
            {
                if (arr[j+1] < arr[j])
                    j++;
            }
            if (v <= arr[j])
                heap = true;
            else
            {
                arr[k] = arr[j];
                k = j;
            }
        }
        arr[k] = v;    
    }
}

void Heapify(int arr[], int size, int i)
{
    int smallest = i;
    int left = 2*i;
    int right = 2*i + 1;

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

long long CalculateCost(int arr[], int size)
{
    long long cost = 0;

    while (size > 2)
    {
        int min1 = arr[1];
        size--;
        swap(arr[1], arr[size]);
        Heapify(arr, size, 1);

        int min2 = arr[1];
		size--;
        swap(arr[1], arr[size]);
        Heapify(arr, size, 1);

        cost += (min1 + min2);
        arr[size] = min1 + min2;
        size++;
        Heapify(arr, size, 1);
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
        for (int i = 1; i < n+1; i++)
            cin >> nums[i];

		BottomUp(nums, n);
        long long cost = CalculateCost(nums, n+1);

        cout << cost << '\n';
        cin >> n;
    }

    return 0;
}