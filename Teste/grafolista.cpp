#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <functional>
#define VISITED 1
#define UNVISITED 0
using namespace std;

class Graph
{
    private:
        vector<int> marked;
        vector<int> *adj;
        int numVertices;

    public:
        Graph(int n)
        {
            numVertices = n;
            adj = new vector<int>[n];
            marked.resize(n);
        }

        int first(int v)
        {
            if (adj[v].size() == 0)
                return numVertices;
            return adj[v].front();
        }
        int next(int v, int w)
        {
            if (isEdge(v, w))
            {
                for (size_t i = 0; i < adj[v].size(); i++)
                {
                    if (adj[v][i] == w && i + 1 < adj[v].size())
                    {
                        return adj[v][i + 1];
                    }
                }
            }
            return numVertices;
        }
        void setEdge(int src, int dest)
        {
            adj[src].push_back(dest);
        }
        void delEdge(int src, int dest)
        {
            if (isEdge(src, dest))
            {
                for (size_t i = 0; i < adj[src].size(); i++)
                {
                    if (adj[src][i] == dest)
                    {
                        adj[src].erase(adj[src].begin() + i);
                        break;
                    }
                }
            }
        }
        bool isEdge(int i, int j)
        {
            for (size_t k = 0; k < adj[i].size(); k++)
            {
                if (adj[i][k] == j)
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
                cout << "\nVertex " << i + 1 << ":";
                for (auto x : adj[i])
                    cout << " -> " << x + 1;
                cout << endl;
            }
        }

        void DFS(int start)
        {
            setMark(start, VISITED);
            cout << start << " ";
            int w = first(start);

            while (w < numVertices)
            {
                if (getMark(w) == UNVISITED)
                    DFS(w);
                w = next(start, w);
            }
        }
        void DFSTransverse(int start)
        {
            for (int i = 0; i < numVertices; i++)
                setMark(i, UNVISITED);
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

            while (!q.empty())
            {
                int v = q.front();
                q.pop();

                int w = first(v);
                while (w < numVertices)
                {
                    if (getMark(w) == UNVISITED)
                    {
                        setMark(w, VISITED);
                        q.push(w);
                    }
                    w = next(v, w);
                }
            }
        }
        void BFSTransverse(int start)
        {
            for (int i = 0; i < numVertices; i++)
                setMark(i, UNVISITED);
            for (int i = start; i < numVertices; i++)
                if (getMark(i) == UNVISITED)
                    BFS(i);
        }

        void toposort(int v, stack<int> &s)
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

        void ToposortTransverse(int start, stack<int> &s)
        {
            for (int i = 0; i < numVertices; i++)
                setMark(i, UNVISITED);
            for (int i = start; i < numVertices; i++)
                if (getMark(i) == UNVISITED)
                    toposort(i, s);
        }

        
};

int main()
{
    int n, m;
    cin >> n >> m;

    Graph g(n);

    for (int j = 0; j < m; j++)
    {
        int u, v;
        cin >> u >> v;

        g.setEdge(u, v);
    }

    stack <int> s;
    g.ToposortTransverse(0, s);

    for (int i = 0; s.size() > 0; i++)
    {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;

    return 0;
}
