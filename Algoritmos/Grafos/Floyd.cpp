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
        // first: vertice, second: peso
        vector<vector<pair<int, int>>> adj;
        vector<int> marked;
        vector<vector<int>> dist;
        int numVertices;
    public:
        Graph(int n)
        {
            numVertices = n;
            marked.resize(n);
            adj.resize(n);
            dist.resize(numVertices);
            for (int i = 0; i < numVertices; i++)
                dist[i].resize(numVertices, inf);
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
                if (adj[v][i].first == w && i + 1 < adj[v].size())
                    return adj[v][i+1].first;
            }
            return numVertices;
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

        void printGraph()
        {
            for (int i = 0; i < numVertices; i++)
            {
                cout << "\nVertex " << i << ":";
                for (auto x : adj[i])
                    cout << " -> " << x.first;
                cout << endl;
            }
        }

        void DFS(int start)
        {
            // pre-visit
            setMark(start, VISITED);
            cout << start << " ";
            int w = first(start);

            while (w < numVertices)
            {
                if (getMark(w) == UNVISITED)
                    DFS(w);
                w = next(start, w);
            }
            // pos-visit
        }
        void DFSTraverse(int start)
        {
            // for (int i = 0; i < numVertices; i++)
            //     setMark(i, UNVISITED);
            marked.resize(numVertices, UNVISITED);
            for (int i = start; i < numVertices; i++)
                if (getMark(i) == UNVISITED)
                    DFS(i);
        }

        void BFS(int start)
        {
            queue<int> q;
            q.push(start);
            setMark(start, VISITED);
            cout << start << " ";
        
            while (q.size() > 0)
            {
                int v = q.front();
                q.pop();
                // pre-visit

                int w = first(v);

                while (w < numVertices)
                {
                    if (getMark(w) == UNVISITED)
                    {
                        setMark(w, VISITED);
                        q.push(w);
                    }
                    w = next(v,  w);
                }
                // pos-visit
            }
        }
        void BFSTraverse(int start)
        {
            // for (int i = 0; i < numVertices; i++)
            //     setMark(i, UNVISITED);
            marked.resize(numVertices, UNVISITED);
            for (int i = start; i < numVertices; i++)
                if (getMark(i) == UNVISITED)
                    BFS(i);
        }

        void toposort(int v, stack <int> &s)
        {
            setMark(v, VISITED);
            int w = first(v);

            while (w < numVertices)
            {
                if (getMark(w) == UNVISITED)
                    toposort(w, s);
                w = next(v, w);        
            }
            s.push(v);
        }

        void ToposortTraverse(int start, stack <int> &s)
        {
            // for (int i = 0; i < numVertices; i++)
            //     setMark(i, UNVISITED);
            marked.resize(numVertices, UNVISITED);
            for (int i = start; i < numVertices; i++)
                if (getMark(i) == UNVISITED)
                    toposort(i, s);
        }

        void Floyd(int source)
        {
            for (int i = 0; i < numVertices; i++)
            {
                auto curr = adj[i].begin();
                for (int j = 0; curr != adj[i].end(); j++)
                {
                    if (i == j)
                        dist[i][j] = 0;
                    else if (isEdge(i, j))
                        dist[i][j] = curr->second;
                    else
                        dist[i][j] = inf;
                    curr++;
                }
            }
            
            for (int k = 0; k < numVertices; k++)
            {
                for (int i = 0; i < numVertices; i++)
                {
                    for (int j = 0; j < numVertices; j++)
                    {
                        if ((dist[i][k] != inf) && (dist[k][j] != inf) && (dist[i][j] > dist[i][k] + dist[k][j]))
                            dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }

            cout << "Distancias minimas a partir do vertice " << source << ":\n";
            for (int i = 0; i < numVertices; i++)
            {
                cout << "Para o vertice " << i << ": ";
                if (dist[source][i] == inf)
                    cout << "INF\n";
                else
                    cout << dist[source][i] << "\n";
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
    
    // g.Dijkstra(v);
    g.Floyd(v);

    return 0;
}