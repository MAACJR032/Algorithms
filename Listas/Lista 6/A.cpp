#include <iostream>
#include <queue>
#include <vector>
#include <climits>
#define VISITED 1
#define UNVISITED 0
#define inf INT_MAX
using namespace std;

class Graph
{
    private:
        // first: vertice, second: peso
        vector<vector<pair<int, int>>> adj;
        vector<int> dist;
        vector<int> marked;
        int numVertices;
    public:
        Graph(int n)
        {
            numVertices = n;
            dist.resize(n, inf);
            marked.resize(n, UNVISITED);
            adj.resize(n);
        }

        void setEdge(int src, int dest, int weight)
        {
            adj[src].emplace_back(dest, weight);
            adj[dest].emplace_back(src, weight);
        }

        int getMark(int v)
        {
            return marked[v];
        }
        void setMark(int v, int visit)
        {
            marked[v] = visit;
        }

        void Dijkstra(int source, int dest)
        {
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
                        cout << "unreachable\n";
                        return;
                    }
                    
                    v = minHeap.top().first;
                    if (v == dest)
                    {
                        cout << dist[dest] << '\n';
                        return;
                    }
                    minHeap.pop();
                    
                } while (getMark(v) == VISITED);
                
                setMark(v, VISITED);

                for(auto& w : adj[v])
                {
                    if ((getMark(w.first) == UNVISITED) && (dist[w.first] > dist[v] + w.second))
                    {
                        dist[w.first] = dist[v] + w.second;
                        minHeap.push({w.first, dist[w.first]});
                    }
                }    
            }
            cout << "unreachable\n";
        }
};

int main()
{
    int cases, cont = 0;
    cin >> cases;

    for (int i = 0; i < cases; i++)
    {
        int n, m, S, T;
        cin >> n >> m >> S >> T;
        
        cont++;
        if (m == 0)
        {
            cout << "Case #" << cont << ": ";
            cout << "unreachable\n";
            continue;
        }
        
        Graph g(n);
        for (int j = 0; j < m; j++)
        {
            int a, b, w;
            cin >> a >> b >> w;

            g.setEdge(a, b, w);
        }

        cout << "Case #" << cont << ": ";
        g.Dijkstra(S, T);
    }
    
    return 0;
}