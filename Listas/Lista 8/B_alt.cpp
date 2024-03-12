#include <iostream>
#include <vector>
#include <climits>
#define inf INT_MAX
using namespace std;

int minCostToReach(int N, int K, vector<int> &heights)
{
   vector<int> min_cost(N, INT_MAX);
    min_cost[0] = 0;

    // Pular da pedra i para a pedra j
    for (int i = 1; i < N; i++)
    {
        for (int j = 1; j <= K; j++)
        {
            // Pulo válido (não acessar índice negativo)
            if (i - j >= 0)
                min_cost[i] = min(min_cost[i], min_cost[i-j] + abs(heights[i-j] - heights[i]));
            else
                break;
        }
    }

    return min_cost[N-1];
}

int main()
{
    int N, K;
    cin >> N >> K;

    vector<int> heights(N);
    for (int i = 0; i < N; i++)
        cin >> heights[i];

    int min_cost = minCostToReach(N, K, heights);
    cout << min_cost << '\n';

    return 0;
}
