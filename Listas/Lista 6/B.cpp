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
        // bool isEdge(int i, int j)
        // {
        //     for (auto k : adj[i])
        //     {   
        //         if (k.first == j)
        //             return true;
        //     }
        //     return false;
        // }
        // int weight(int src, int dest)
        // {
        //     for (auto edge : adj[src])
        //     {
        //         if (edge.first == dest)
        //             return edge.second;
        //     }
        //     return 0;
        // }
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
            auto comp = [](pair<int, int> a, pair<int, int> b)
            {
                return a.second > b.second;
            };
            priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(comp)> minHeap(comp);
            minHeap.push({0, 0});
            dist[0] = 0;
            
            // for (int i = 0; i < numVertices; i++)
            // {
            //     int v;
            //     do
            //     {
            //         v = minHeap.top().first;

            //         if (minHeap.empty())
            //             return;
            //         minHeap.pop();
                    
            //     } while (!(getMark(v) == UNVISITED));
                
            //     setMark(v, VISITED);
            //     int w = first(v);

            //     while (w < numVertices)
            //     {
            //         if ((getMark(w) != VISITED) && (dist[w] > weight(v, w)))
            //         {
            //             dist[w] = weight(v, w);
            //             minHeap.push({w, dist[w]});
            //         }
            //         int aux = next(v, w);
            //         if (aux == w)
            //             return;
            //         else
            //             w = aux;
            //     }    
            // }

            // while (!minHeap.empty())
            for (int i = 0; i < numVertices; i++)
            {
                int v = minHeap.top().first;
                minHeap.pop();

                if (getMark(v) == VISITED)
                    continue;

                setMark(v, VISITED);

                for (int i = 0; i < adj[v].size(); i++)
                {
                    int w = adj[v][i].first;
                    int weight = adj[v][i].second;

                    if (getMark(w) != VISITED && dist[w] > weight)
                    {
                        dist[w] = weight;
                        minHeap.push({w, dist[w]});
                    }
                }
            }

            int maxEdgeWeight = 0;
            for (int i = 0; i < numVertices; i++)
                if (dist[i] != inf && dist[i] > maxEdgeWeight)
                    maxEdgeWeight = dist[i];
            if (maxEdgeWeight == 0)
                cout << "IMPOSSIBLE\n";
            else
                cout << maxEdgeWeight << '\n';      
        }
        void find_min_range()
        {
            int min_range = 0;
            for (int i = 0; i < numVertices; i++)
            {
                if (dist[i] == inf)
                {
                    cout << "IMPOSSIBLE\n";
                    return;
                }
                else if (dist[i] > min_range)
                    min_range = dist[i];
            }
            cout << min_range << '\n';
        }

        // void Floyd()
        // {
        //     // dist = new int*[numVertices];
        //     int min_range = 0;
        //     for (int i = 0; i < numVertices; i++)
        //         dist[i][i] = 0;
        //         // dist[i] = new int[numVertices];
                
        //     for (int k = 0; k < numVertices; k++)
        //     {
        //         for (int i = 0; i < numVertices; i++)
        //         {
        //             for (int j = 0; j < numVertices; j++)
        //             {
        //                 if ((dist[i][k] != inf) && (dist[k][j] != inf) && (dist[i][j] > dist[i][k] + dist[k][j]))
        //                     dist[i][j] = dist[i][k] + dist[k][j];
        //             }
        //         }
        //     }
            
        //     for (int i = 0; i < numVertices; i++)
        //     {
        //         for (int j = 0; j < numVertices; j++)
        //         {                    
        //             if (dist[i][j] == inf)
        //             {
        //                 cout << "IMPOSSIBLE\n";
        //                 return;
        //             }
        //             else if ((i != j))
        //             {
        //                 if (isEdge(i, j) && (dist[i][j] > min_range))
        //                     min_range = dist[i][j];
        //             }
        //         }
        //     }
        //     cout << min_range << '\n';
        // }
};
/*
0 1 10
0 2 3
0 3 20
1 3 5 
2 1 2
2 4 15
3 4 11

3 3
0 1 3
1 2 4
2 1 5
*/
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
        // g.find_min_range();
    }

    return 0;
}