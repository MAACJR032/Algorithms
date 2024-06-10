#include <iostream>
#include <vector>
using namespace std;

int Knapsack(int n, int capacity, vector<int> weights, vector<int> values, vector<vector<int>> Result)
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= capacity; j++)
        {
            if (i == 0 || j == 0)
                Result[i][j] = 0;
            else if (weights[i] <= j)
                Result[i][j] = max(Result[i-1][j], values[i] + Result[i-1][j-weights[i]]);
            else Result[i][j] = Result[i-1][j];
        }
    }
    return Result[n][capacity];
}

int main()
{
    int cases = 0;
    cin >> cases;

    for (int i = 0; i < cases; i++)
    {   
        int Capacity, n_itens;
        cin >> Capacity;
        cin >> n_itens;

        vector<int> weights, values;
        vector<vector<int>> Result;

        weights.push_back(0);
        values.push_back(0);
        
        for (int j = 0; j < n_itens; j++)
        {
            int w, v;
            cin >> w >> v;
            weights.push_back(w);
            values.push_back(v);
        }    

        Result.resize(n_itens+1);
        for (int i = 0; i < n_itens+1; i++)
            Result[i].resize(Capacity+1);
        
        int MostValuable;
        MostValuable = Knapsack(n_itens, Capacity, weights, values, Result);
        cout << MostValuable << '\n';
    }
    
    return 0;
}
