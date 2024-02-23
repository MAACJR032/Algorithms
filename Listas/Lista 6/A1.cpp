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
        int numVertices;
        int *marked;
        int **matrix;
    public:
        Graph(int n)
        {
            numVertices = n;

            matrix = new int*[numVertices];
            for (int i = 0; i < n; i++)
                matrix[i] = new int[numVertices];
           
           marked = new int[numVertices];
           for (int i = 0; i < n; i++)
                marked[i] = UNVISITED;
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

        void setEdge(int i, int j, int weight)
        {
            matrix[i][j] = weight;
            matrix[j][i] = weight;
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
        cout << "Case #" << cont << ": ";
        g.Dijkstra(S, T);
    }
    
    return 0;
}