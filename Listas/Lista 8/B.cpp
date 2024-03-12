#include <iostream>
#include <vector>
#define inf INT_MAX
using namespace std;

int minCost(vector<int> &heights, int N, int K)
{
    vector<int> distances(N, inf);
    distances[0] = 0;

    for (int i = 1; i < N; i++)
        for (int j = 1; j <= min(i, K) ; j++)
            distances[i] = min(distances[i], distances[i-j] + abs(heights[i] - heights[i-j]));
        
    return distances[N-1];
}

int main()
{
    int N, k;
    cin >> N >> k;

    vector<int> heights(N);
    for (int i = 0; i < N; i++)
        cin >> heights[i];
    
    int min_cost = minCost(heights, N, k);
    cout << min_cost << '\n';
    
    return 0;
}