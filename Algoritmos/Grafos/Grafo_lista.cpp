#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>
#include <set>
#define VISITED 1
#define UNVISITED 0
using namespace std;

class Graph
{
    private:
        int *marked;
    
    public:
        list<int> *l;
        int numVertices;
        Graph(int n)
        {
            numVertices = n;
            l = new list<int>[n];
            marked = new int[n];
        }

        int first(int v)
        {
            if (l[v].size() == 0)
                return numVertices;
            return l[v].front();
        }
        int next(int v, int w)
        {
            if (isEdge(v, w))
            {
                list<int>::iterator curr;
                curr = l[v].begin();
                while (*curr != w)
                {
                    curr++;
                }

                for (int i = *curr + 1; i < numVertices; i++)
                {
                    if (*curr >= 0)
                        return (*curr + 1);
                    curr++;
                }   
            }
            return numVertices;
        }
        void setEdge(int src, int dest)
        {
            l[src].push_back(dest);
            // l[dest].push_back(src);
        }
        void delEdge(int src, int dest)
        {
            if (isEdge(src, dest))
                l[src].pop_back();
                // l[dest].pop_back();
        }
        bool isEdge(int i, int j)
        {
            for (auto k = l[i].begin(); k != l[i].end(); k++)
            {   
                if (*k == j)
                    return true;
            }
            return false;
        }

        // int weight(int v1, int v2)
        // {
        //     if (isEdge(v1, v2))
        //         return 1;
        // }

        int getMark(int v)
        {
            return marked[v];
        }
        void setMark(int v, int visit)
        {
            marked[v] = visit;
        }

        int Degree(int v)
        {
            int degree = 0;
            for (int i = 0; i < numVertices; i++)
            {
                list<int>::iterator curr;
                curr = l[i].begin();
                for (int j = 0; j < l[i].size(); j++)
                {

                    if (*curr == v)
                    {
                        degree++;
                        break;
                    }
                    else
                        curr++;
                }
            }
            return degree;
        }

        void printGraph()
        {
            for (int i = 0; i < numVertices; i++)
            {
                cout << "\nVertex " << i+1 << ":";
                for (auto x : l[i])
                    cout << " -> " << x+1;
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
        void BFSTransverse(int start)
        {
            for (int i = 0; i < numVertices; i++)
                setMark(i, UNVISITED);
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

        void ToposortTransverse(int start, stack <int> &s)
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

    Graph g(n+1);
    int in_degree[n] = {0};
    for (int j = 0; j < m; j++)
    {
        int u, v;
        cin >> u >> v;

        g.setEdge(u, v);
        in_degree[v]++;
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