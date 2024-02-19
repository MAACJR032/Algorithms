#include <iostream>
#include <queue>
#include <stack>
// #include <functional>
#define UNVISITED 0
#define VISITED 1
using namespace std;

class Graph
{
    private:
        int **matrix, *marked;
        int numVertices, numEdge;
    public:
        Graph(int n)
        {
            marked = new int[n];
            matrix = new int*[n];
            numEdge = 0;
            numVertices = n;

            for (int i = 0; i < n; i++)
                matrix[i] = new int[n];
            
            for (int i = 0; i < n; i++)
                marked[i] = UNVISITED;
            
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    matrix[i][j] = 0;
        }
        ~Graph()
        {
            for (int i = 0; i < numVertices; i++)
                delete[] matrix[i];
            delete[] matrix;
            delete[] marked;
        }
        
        int first(int v)
        {
            for (int i = 0; i < numVertices; i++)
            {
                if (matrix[v][i] != 0)
                    return i;
            }
            return numVertices;
        }

        int next(int v, int nxt)
        {
            for (int i = nxt + 1; i < numVertices; i++)
            {
                if (matrix[v][i] != 0)
                    return i;
            }
            return numVertices;
        }

        bool isEdge(int i, int j)
        {
            if (matrix[i][j] != 0)
                return true;
            return false;
        }

        void setEdge(int i, int j, int weight)
        {
            if (matrix[i][j] == 0)
                numEdge++;
            // if (matrix[j][i] == 0)
            //     numEdge++;
            
            matrix[i][j] = weight;
            // matrix[j][i] = weight;
        }

        void delEdge(int i, int j)
        {
            if (matrix[i][j] != 0)
                numEdge--;
            matrix[i][j] = 0;
        }

        int Degree(int v)
        {
            int degree = 0;
            for (int i = 0; i < numVertices; i++)
            {
                if (matrix[i][v] != 0)
                    degree++;
            }
            return degree;
        }

        int weight(int v1, int v2)
        {
            return matrix[v1][v2];
        }

        int getMark(int v)
        {
            return marked[v];
        }

        void setMark(int v, int visit)
        {
            marked[v] = visit;
        }

        void BFS(int start)
        {
            queue <int> Q;
            Q.push(start);
            setMark(start, VISITED);
            cout << start << " ";
            
            while (Q.size() > 0)
            {
                int v = Q.front();
                Q.pop();

                // pre-visit
                
                int w = first(v);
                while (w < numVertices)
                {
                    if (getMark(w) == UNVISITED)
                    {
                        setMark(w, VISITED);
                        cout << w << " ";
                        Q.push(w);
                    }
                    w = next (v, w);
                }
                // pos-visit
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

        void BFSTransverse(int start)
        {
            for (int i = 0; i < numVertices; i++)
                setMark(i, UNVISITED);
            for (int i = start; i < numVertices; i++)
                if (getMark(i) == UNVISITED)
                    BFS(i);
        }

        void DFSTransverse(int start)
        {
            for (int i = 0; i < numVertices; i++)
                setMark(i, UNVISITED);
            for (int i = start; i < numVertices; i++)
                if (getMark(i) == UNVISITED)
                    DFS(i);
        }

        // void Traversal(function<void(Graph&, int)> traverse, int start)
        // {
        //     for (int i = 0; i < numVertices; i++)
        //         setMark(i, UNVISITED);
        //     for (int i = start; i < numVertices; i++)
        //         if (getMark(i) == UNVISITED)
        //             Traversal(traverse, i);
        // }

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

        void PrintMatrix()
        {
            for (int i = 0; i < numVertices; i++)
            {
                for (int j = 0; j < numVertices; j++)
                    cout << matrix[i][j] << " ";
                cout << endl;    
            }
        }
        void PrintVertices()
        {
            for (int i = 0; i < numVertices; i++)
                cout << i << ": " << marked[i] << endl;
            cout << endl;
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

        g.setEdge(u, v, 1);
    }

    stack <int> s;
    g.ToposortTransverse(0, s);

    for (int i = 0; s.size() > 0; i++)
    {
        cout << s.top() + 1 << " ";
        s.pop();
    }
    cout << endl;
    
    return 0;
}