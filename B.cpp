#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#define inf INT_MAX
#define UNVISITED 0
#define VISITED 1
using namespace std;

class Graph
{
    private:
        // first: vertice, second: peso
        vector<vector<pair<int, int>>> adj;
        vector<int> marked;
        vector<int> dist;
        int numVertices;
    public:
        Graph(int n) : numVertices(n), adj(n)
        {
            marked.resize(n, UNVISITED);
            dist.resize(numVertices, inf);
        }
        void setEdge(int src, int dest, int weight)
        {
            adj[src].push_back({dest, weight});
            adj[dest].push_back({src, weight});
        }
        bool isEdge(int i, int j)
        {
            for (auto k : adj[i])
            {   
                if (k.first == j)
                    return true;
            }
            return false;
        }
        int getMark(int v)
        {
            return marked[v];
        }
        void setMark(int v, int visit)
        {
            marked[v] = visit;
        }

        void Prim()
        {
            int range = 0;
            auto comp = [](pair<int, int> a, pair<int, int> b)
            {
                return a.second > b.second;
            };
            priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> minHeap(comp);
            minHeap.push({0, 0});
            dist[0] = 0;
            
            for (int i = 0; i < numVertices; i++)
            {
                int v;
                do
                {
                    if (minHeap.empty())
                    {
                        cout << "IMPOSSIBLE\n";
                        return;
                    }
                    
                    v = minHeap.top().first;
                    minHeap.pop();                  
                } while (getMark(v) == VISITED);
                
                setMark(v, VISITED);

                for(auto w : adj[v])
                {
                    if ((getMark(w.first) == UNVISITED) && (dist[w.first] > w.second))
                    {
                        dist[w.first] = w.second;
                        minHeap.push({w.first, dist[w.first]});
                    }
                }
            }
            for (int i = 0; i < numVertices; i++)
            {
                if (dist[i] > range)
                    range = dist[i];
            }
            if (range == inf)
                cout << "IMPOSSIBLE\n";
            else
                cout << range << '\n';
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
        g.Prim();
    }

    return 0;
}
