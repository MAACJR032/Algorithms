#include <iostream>
#include <vector>
using namespace std;

int Knapsack(int n, int capacity, vector<int> weights, vector<int> values, vector<vector<int>> f)
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= capacity; j++)
        {
            if (i == 0 || j == 0)
                f[i][j] = 0;
            else if (weights[i] <= j)
                f[i][j] = max(f[i-1][j], values[i] + f[i-1][j-weights[i]]);
            else f[i][j] = f[i-1][j];
        }
    }
    return f[n][capacity];
}

int main()
{
    int capacity, itens;
    vector<int> weights, values;
    vector<vector<int>> f;

    cin >> capacity >> itens;
    for (int i = 0; i < itens; i++)
    {
        int w, v;
        cin >> w >> v;
        weights.push_back(w);
        values.push_back(v);
    }

    f.resize(capacity+1);
    for (int i = 0; i <= capacity; i++)
        f[i].resize(itens+1);
    
    int most_valuable = Knapsack(itens, capacity, weights, values, f);
    cout << most_valuable << '\n';
    
    return 0;
}
