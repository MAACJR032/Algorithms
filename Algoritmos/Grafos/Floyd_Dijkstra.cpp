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
        int **matrix, *marked;
        int numVertices, numEdge;
        vector<vector<int>> dist;
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

            dist.resize(numVertices);
            for (int i = 0; i < numVertices; i++)
                dist[i].resize(numVertices, inf);
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

        void delEdge(int i, int j)
        {
            if (matrix[i][j] != 0)
                numEdge--;
            matrix[i][j] = 0;
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

        void Floyd(int source)
        {
            for (int i = 0; i < numVertices; i++)
            {
                for (int j = 0; j < numVertices; j++)
                {
                    if (i == j)
                        dist[i][j] = 0;
                    else if (matrix[i][j] != 0)
                        dist[i][j] = matrix[i][j];
                    else
                        dist[i][j] = inf;
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
        
        void Dijkstra(int source)
        {
            vector<int> dist(numVertices, inf);
            vector<int> parents(numVertices, -1);

            // fila de prioridade para armazenar os vértices que precisam ser explorados
            priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, greater<pair<pair<int, int>, int>>> minHeap;
            minHeap.push({{source, source}, 0});
            dist[source] = 0;
            
            for (int i = 0; i < numVertices; i++)
            {
                int v, p;
                do
                {
                    p = minHeap.top().first.first;
                    v = minHeap.top().first.second;

                    minHeap.pop();

                    if (minHeap.empty())
                        return;
                    
                } while (getMark(v) != UNVISITED);
                
                setMark(v, VISITED);
                parents[v] = p;
                int w = first(v);

                while (w < numVertices)
                {
                    if ((getMark(w) != VISITED) && (dist[w] > dist[v] + weight(v, w)))
                    {
                        dist[w] > dist[v] + weight(v, w);
                        minHeap.push({{v, w}, dist[w]});
                    }
                    w = next(v, w);
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
/*
5 7 0
0 1 10
0 2 3
0 3 20
1 3 5 
2 1 2
2 4 15
3 4 11
*/
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
    
    g.PrintMatrix();
    g.Dijkstra(v);
    g.Floyd(v);

    return 0;
}