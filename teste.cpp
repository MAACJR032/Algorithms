#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#define inf INT_MAX
using namespace std;

class Graph
{
private:
    vector<vector<pair<int, int>>> adj;
    vector<vector<int>> dist;
    vector<vector<int>> maxWeight; // To store the maximum weight on shortest paths
    int numVertices;

public:
    Graph(int n) : numVertices(n), adj(n)
    {
        dist.resize(n);
        maxWeight.resize(n);
        for (int i = 0; i < n; i++)
        {
            dist[i].resize(n, inf);
            maxWeight[i].resize(n, -1); // Initialize to -1
        }
    }

    void setEdge(int src, int dest, int weight)
    {
        adj[src].push_back({dest, weight});
        adj[dest].push_back({src, weight});

        dist[src][dest] = weight;
        dist[dest][src] = weight;
    }

    void dijkstra(int src)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});
        dist[src][src] = 0;

        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            for (auto &neighbor : adj[u])
            {
                int v = neighbor.first;
                int weight = neighbor.second;
                if (dist[src][v] > dist[src][u] + weight)
                {
                    dist[src][v] = dist[src][u] + weight;
                    pq.push({dist[src][v], v});
                }
            }
        }
    }

    void findMaxWeight()
    {
        for (int i = 0; i < numVertices; ++i)
        {
            dijkstra(i); // Run Dijkstra's algorithm from each vertex

            for (int j = 0; j < numVertices; ++j)
            {
                if (dist[i][j] != inf)
                {
                    maxWeight[i][j] = -1; // Initialize to -1
                    for (auto &neighbor : adj[j])
                    {
                        int v = neighbor.first;
                        int weight = neighbor.second;
                        if (dist[i][v] == dist[i][j] - weight)
                        {
                            maxWeight[i][j] = max(maxWeight[i][j], weight); // Update maxWeight
                        }
                    }
                }
            }
        }
    }

    int getMinRange()
    {
        int minRange = inf;
        for (int i = 0; i < numVertices; ++i)
        {
            for (int j = 0; j < numVertices; ++j)
            {
                if (maxWeight[i][j] != -1)
                    minRange = max(minRange, maxWeight[i][j]);
            }
        }
        return (minRange == inf) ? -1 : minRange;
    }
};

int main()
{
    int n, m, city1, city2, w;

    while (true)
    {
        cin >> n >> m;

        if ((n == 0) && (m == 0))
            break;

        if (m == 0)
        {
            cout << "IMPOSSIBLE\n";
            continue;
        }

        Graph g(n);
        for (int j = 0; j < m; j++)
        {
            cin >> city1 >> city2 >> w;
            g.setEdge(city1, city2, w);
        }

        g.findMaxWeight();
        int minRange = g.getMinRange();
        if (minRange == -1)
            cout << "IMPOSSIBLE\n";
        else
            cout << minRange << endl;
    }

    return 0;
}
