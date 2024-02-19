#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph
{
    private:
        int numVertices;
        vector<vector<int>> matrix;
    public:

        Graph(int n) : matrix(n)
        {
            numVertices = n;
        }
        void setEdge(int i, int j)
        {
            matrix[i].push_back(j);
        }
        void Toposort(vector<int> &toposort, vector<int> &in_degree)
        {
            priority_queue<int, vector<int>, greater<int>> q;

            for (int i = 0; i < numVertices; i++)
                if (in_degree[i] == 0)
                    q.push(i);

            while (q.size() > 0)
            {
                int curr = q.top();
                toposort.push_back(curr);
                q.pop();

                for (int j : matrix[curr])
                {
                    in_degree[j]--;
                    if (in_degree[j] == 0)
                        q.push(j);
                }
            }
        }
};

int main()
{
    int n, m;
    cin >> n >> m;

    Graph g(n);

    vector<int> in_degree(n, 0);
    vector<int> toposort;

    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        
        g.setEdge(u-1, v-1);
        in_degree[v-1]++;
    }
    
    g.Toposort(toposort, in_degree);
    if (toposort.size() < n)
        cout << "Sandro fails.\n";
    else
    {
        for (int i = 0; i < toposort.size(); i++)
            cout << toposort[i] + 1 << " ";
        cout << '\n';
    }
    
    return 0;
}