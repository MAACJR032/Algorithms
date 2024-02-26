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
        int numVertices;
    public:
        Graph(int n)
        {
            numVertices = n;
            marked.resize(n);
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
                if (adj[v][i].first == w && i + 1 < adj[v].size())
                    return adj[v][i+1].first;
            }
            return numVertices;
        }
        void setEdge(int src, int dest, int weight)
        {
            adj[src].push_back({dest, weight});
            // adj[dest].push_back({src, weight});
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

        int weight(int src, int dest)
        {
            for (auto edge : adj[src])
            {
                if (edge.first == dest)
                    return edge.second; // Return the weight of the edge if it exists
            }
            return inf; // Return -1 if the edge doesn't exist
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
            marked.resize(numVertices, UNVISITED);
            for (int i = start; i < numVertices; i++)
                if (getMark(i) == UNVISITED)
                    toposort(i, s);
        }

        void Dijkstra(int source)
        {
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

                for(auto &w : adj[v])
                {
                    if ((getMark(w.first) == UNVISITED) && (dist[w.first] > w.second))
                    {
                        dist[w.first] = w.second;
                        minHeap.push({{v, w.first},  dist[w.first]});
                    }
                }
            }

            // Imprime as distâncias mínimas a partir da fonte
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
    
    g.Dijkstra(v);

    return 0;
}