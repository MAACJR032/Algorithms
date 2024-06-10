#include <iostream>
#define UNVISITED 0
#define VISITED 1
using namespace std;

class Graph
{
    private:
        int **matrix, *marked;
    public:
        int numVertices, numEdge;
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
            if (matrix[j][i] == 0)
                numEdge++;
            
            matrix[i][j] = weight;
            matrix[j][i] = weight;
        }

        int getMark(int v)
        {
            return marked[v];
        }

        void setMark(int v, int visit)
        {
            marked[v] = visit;
        }

        void DFS(int start)
        {
            setMark(start, VISITED);
            int w = first(start);

            while (w < numVertices)
            {
                if (getMark(w) == UNVISITED)
                    DFS(w);
                w = next(start, w);
            }
        }
        int DFSTraverse()
        {
            int count = 0;
            for (int i = 0; i < numVertices; i++)
                setMark(i, UNVISITED);
            for (int i = 0; i < numVertices; i++)
            {
                if (getMark(i) == UNVISITED)
                {
                    DFS(i);
                    count++;
                }
            }
            return count;
        }
};

int main()
{
    int casos;
    cin >> casos;

    for (int i = 0; i < casos; i++)
    {
        int v, a;
        cin >> v >> a;
        Graph g(v);

        for (int j = 0; j < a; j++)
        {
            int k, s;
            cin >> k >> s;
            g.setEdge(k, s, 1);
        }

        int count = 0;
        count = g.DFSTraverse();
        cout << count << '\n';
    }

    return 0;
}
