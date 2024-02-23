#include <iostream>
#include <queue>
#include <vector>
#define VISITED 1
#define UNVISITED 0
#define inf 10100
using namespace std;

class Graph
{
    private:
        // first: vertice, second: peso
        vector<vector<pair<int, int>>> adj;
        vector<int> marked;
        int numVertices;
    public:
        Graph(int n)
        {
            numVertices = n;
            marked.resize(n, UNVISITED);
            adj.resize(n);
        }

        int first(int v)
        {
            if (adj[v].size() == 0)
                return numVertices;
            return adj[v].front().first;
        }
        int next(int v, int w)
        {
            for (int i = 0; i < adj[v].size(); i++)
            {
                if ((adj[v][i].first == w) && (i + 1 < adj[v].size()))
                    return adj[v][i+1].first;
            }
            return numVertices;
        }
        void setEdge(int src, int dest, int weight)
        {
            adj[src].push_back({dest, weight});
            adj[dest].push_back({src, weight});
        }
        int weight(int src, int dest)
        {
            for (auto edge : adj[src])
            {
                if (edge.first == dest)
                    return edge.second;
            }
            return 0;
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
            vector<int> dist(numVertices, inf);

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
                    minHeap.pop();
                    
                } while (!(getMark(v) == UNVISITED));
                
                setMark(v, VISITED);
                int w = first(v);

                while (w < numVertices)
                {
                    if ((getMark(w) != VISITED) && (dist[w] > dist[v] + weight(v, w)))
                    {
                        dist[w] = dist[v] + weight(v, w);
                        minHeap.push({w, dist[w]});
                    }
                    w = next(v, w);
                }    
            }

            if (dist[dest] == inf)
                cout << "unreachable\n";
            else
                cout << dist[dest] << '\n';
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

        Graph g(n);
        for (int j = 0; j < m; j++)
        {
            int a, b, w;
            cin >> a >> b >> w;

            g.setEdge(a, b, w);
        }

        cont++;
        cout << "Case #" << cont << " ";
        g.Dijkstra(S, T);
    }
    
    return 0;
}