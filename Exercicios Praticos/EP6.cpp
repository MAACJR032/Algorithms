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
        }
        void setEdge(int src, int dest, int weight)
        {
            adj[src].push_back({dest, weight});
        }
        int getMark(int v)
        {
            return marked[v];
        }
        void setMark(int v, int visit)
        {
            marked[v] = visit;
        }

        void Dijkstra(int source)
        {
            marked.resize(numVertices, UNVISITED);
            dist.resize(numVertices, inf);

            auto comp = [](pair<int, int> a, pair<int, int> b)
            {
                return a.second > b.second;
            };
            priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> minHeap(comp);
            minHeap.push({source, 0});
            dist[source] = 0;
            
            for (int i = 0; i < numVertices; i++)
            {
                int v;
                do
                {
                    if (minHeap.empty())
                    {
                        for (int i = 0; i < numVertices; i++)
                        {
                            if (dist[i] != inf)
                                cout << dist[i] << '\n';
                            else
                                cout << "-1\n";
                        }
                        return;
                    }
                    
                    v = minHeap.top().first;
                    minHeap.pop();
                } while (getMark(v) == VISITED);
                
                setMark(v, VISITED);

                for(auto &w : adj[v])
                {
                    if ((getMark(w.first) == UNVISITED) && (dist[w.first] > dist[v] + w.second))
                    {
                        dist[w.first] = dist[v] + w.second;
                        minHeap.push({w.first, dist[w.first]});
                    }
                }
            }
            for (int i = 0; i < numVertices; i++)
            {
                if (dist[i] != inf)
                    cout << dist[i] << '\n';
                else
                    cout << "-1\n";
            }
        }
};

int main()
{
    int c;
    cin >> c;

    for (int k = 0; k < c; k++)
    {
        int v, a;
        cin >> v >> a;

        Graph g(v);
        for (int arestas = 0; arestas < a; arestas++)
        {
            int i, v, w;
            cin >> i >> v >> w;

            g.setEdge(i, v, w);
        }
        int s;
        cin >> s;
        cout << "Caso " << k+1 << '\n';
        g.Dijkstra(s);
    }
    
    return 0;
}