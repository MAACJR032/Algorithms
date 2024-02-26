#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <climits>
#define VISITED 1
#define UNVISITED 0
#define inf INT_MAX
using namespace std;

class Graph
{
    private:
        int numVertices, numEdge;
        vector<int> marked;
        vector<vector<int>> Dist;
        // vertice, peso
        vector<vector<pair<int, int>>> adj;
    public:
        Graph(int n)
        {
            numEdge = 0;
            numVertices = n;

            adj.resize(numVertices);
            Dist.resize(numVertices);
            for (int i = 0; i < numVertices; i++)
                Dist[i].resize(numVertices, inf);
            
            marked.resize(numVertices, UNVISITED);
        }
        
        int first(int v)
        {
            if (adj[v].size() == 0)
                return numVertices;
            return adj[v].front().first;
        }

        int next(int v, int nxt)
        {
            for(auto &w : adj[v])
            {
                if (w.first == nxt)
                    return w.first;
            }
            return numVertices;
        }

        bool isEdge(int i, int j)
        {
            for(auto &w : adj[i])
            {
                if (w.first == j)
                    return true;
            }
            return false;
        }

        void setEdge(int i, int j, int weight)
        {
            adj[i].push_back({j, weight});
            adj[j].push_back({i, weight});
        }

        int weight(int v1, int v2)
        {
            for(auto &w : adj[v1])
            {
                if (w.first == v2)
                    return w.second;
            }
            return inf;
        }

        int getMark(int v)
        {
            return marked[v];
        }

        void setMark(int v, int visit)
        {
            marked[v] = visit;
        }

        void Floyd(int source)
        {
            for (int i = 0; i < numVertices; i++)
            {
                for (int j = 0; j < numVertices; j++)
                {
                    if (i == j)
                        Dist[i][j] = 0;
                    else if (isEdge(i, j))
                        continue;
                    else
                        Dist[i][j] = inf;
                }
            }
            
            for (int k = 0; k < numVertices; k++)
            {
                for (int i = 0; i < numVertices; i++)
                {
                    for (int j = 0; j < numVertices; j++)
                    {
                        if ((Dist[i][k] != inf) && (Dist[k][j] != inf) && (Dist[i][j] > Dist[i][k] + Dist[k][j]))
                            Dist[i][j] = Dist[i][k] + Dist[k][j];
                    }
                }
            }

            cout << "Distancias minimas a partir do vertice " << source << ":\n";
            for (int i = 0; i < numVertices; i++)
            {
                cout << "Para o vertice " << i << ": ";
                if (Dist[source][i] == inf)
                    cout << "INF\n";
                else
                    cout << Dist[source][i] << "\n";
            }
        }
        
        void Dijkstra(int source)
        {
            marked.resize(numVertices, UNVISITED);
            vector<int> dist(numVertices, inf);
            vector<int> parents(numVertices, -1);

            auto comp = [](pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
            {
                return a.second > b.second;
            };
            priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, decltype(comp)> minHeap(comp);
            minHeap.push({{source, source}, 0});
            dist[source] = 0;
            
            for (int i = 0; i < numVertices; i++)
            {
                int v, p;
                do
                {
                    p = minHeap.top().first.first;
                    v = minHeap.top().first.second;

                    if (minHeap.empty())
                        return;
                    minHeap.pop();
                    
                } while (!(getMark(v) == UNVISITED));
                
                setMark(v, VISITED);
                parents[v] = p;
                int w = first(v);

                for(auto &w : adj[v])
                {
                    if ((getMark(w.first) == UNVISITED) && (dist[w.first] > w.second))
                    {
                        dist[w.first] = w.second;
                        minHeap.push({{v, w.first},  dist[w.first]});
                    }
                }
            }

            cout << "Distancias minimas a partir do vertice " << source << ":\n";
            for (int i = 0; i < numVertices; i++)
            {
                cout << "Para o vertice " << i << ": ";
                if (dist[i] == inf)
                    cout << "INF\n";
                else
                    cout << dist[i] << "\n";
            }
        }

        void BellmanFord(int source)
        {
            vector<int> dist(numVertices, inf);
            dist[source] = 0;

            for (int k = 0; k < numVertices-1; k++)
            {
                for (int i = 0; i < numVertices; i++)
                {
                    int j = first(i);

                    for(auto &w : adj[i])
                    {
                        if (dist[j] > dist[i] + weight(i, j))
                            dist[j] = dist[i] + weight(i, j);
                    }
                }
            }
            
            for (int i = 0; i < numVertices; i++)
            {
                int j = first(i);

                for(auto &w : adj[i])
                {
                    if (dist[j] > dist[i] + weight(i, j))
                    {
                        cout << "negative cycle detected\n";
                        return;
                    }
                }
            }

            cout << "Distancias minimas a partir do vertice " << source << ":\n";
            for (int i = 0; i < numVertices; i++)
            {
                cout << "Para o vertice " << i << ": ";
                if (dist[i] == inf)
                    cout << "INF\n";
                else
                    cout << dist[i] << "\n";
            }
        }

        void Prim()
        {
            marked.resize(numVertices, UNVISITED);
            vector<int> dist(numVertices, inf);
            vector<int> V(numVertices, -1);

            auto comp = [](pair<pair<int, int>, int> a, pair<pair<int, int>, int> b)
            {
                return a.second > b.second;
            };
            priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, decltype(comp)> minHeap(comp);
            minHeap.push({{0, 0}, 0});
            dist[0] = 0;
            
            for (int i = 0; i < numVertices; i++)
            {
                int v, p;
                do
                {
                    p = minHeap.top().first.first;
                    v = minHeap.top().first.second;

                    if (minHeap.empty())
                        return;
                    minHeap.pop();
                    
                } while (!(getMark(v) == UNVISITED));
                
                setMark(v, VISITED);
                V[v] = p;
                int w = first(v);

                for(auto &w : adj[v])
                {
                    if ((getMark(w.first) == UNVISITED) && (dist[w.first] > w.second))
                    {
                        dist[w.first] = w.second;
                        minHeap.push({{v, w.first},  dist[w.first]});
                    }
                }
            }

            for (int i = 0; i < numVertices; i++)
            {
                cout << "Para o vertice " << i << ": ";
                if (dist[i] == inf)
                    cout << "INF\n";
                else
                    cout << dist[i] << "\n";
            }
        }

        
};

int main()
{
    int n, m, v;
    cin >> n >> m >> v;

    Graph g(n);
    for (int i = 0; i < m; i++)
    {
        int a, b, w;
        cin >> a >> b >> w;
        g.setEdge(a, b, w);
    }

    g.Prim();

    return 0;
}