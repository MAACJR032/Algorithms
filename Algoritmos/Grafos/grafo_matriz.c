#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../Listas/Linked_stack.h"
#include "../Listas/LinkedQueue.h"
#include <assert.h>

#define visited 1
#define unvisited 0

struct graph
{
    int num_vertex;
    int *marked;
    int **matrix;
};
typedef struct graph graph;

graph* create_graph(size_t num_vertex)
{
    graph *g = (graph *) malloc(sizeof(graph));
    assert(g != NULL);

    g->num_vertex = num_vertex;
    g->marked = (int *) malloc(sizeof(int) * num_vertex);
    assert(g->marked != NULL);

    g->matrix = (int **) malloc(sizeof(int) * num_vertex);
    assert(g->matrix != NULL);

    for (size_t i = 0; i < num_vertex; i++)
    {
        g->matrix[i] = (int *) malloc(sizeof(int) * num_vertex);
        assert(g->matrix[i] != NULL);

        for (size_t j = 0; j < num_vertex; j++)
            g->matrix[i][j] = 0;
    }

    return g;
}

int first(const graph *g, size_t vertex)
{
    for (size_t i = 0; i < g->num_vertex; i++)
    {
        if (g->matrix[vertex][i] != 0)
            return i;
    }

    return g->num_vertex;
}

int next(const graph *g, size_t vertex1, size_t vertex2)
{
    for (int i = vertex2 + 1; i < g->num_vertex; i++)
    {
        if (g->matrix[vertex1][i] != 0)
            return i;
    }
    return g->num_vertex;
}

bool is_edge(const graph *g, size_t vertex1, size_t vertex2)
{
    if (g->matrix[vertex1][vertex2] != 0)
        return true;
    return false;
}

void set_edge(const graph *g, size_t vertex1, size_t vertex2)
{
    if (g->matrix[vertex1][vertex2] == 0 && g->matrix[vertex2][vertex1] == 0)
    {
        g->matrix[vertex1][vertex2] = 1;
        g->matrix[vertex2][vertex1] = 1;
    }
}

void del_edge(const graph *g, size_t vertex1, size_t vertex2)
{
    g->matrix[vertex1][vertex2] = 0;
    g->matrix[vertex2][vertex1] = 0;
}

int get_mark(const graph *g, size_t vertex)
{
    assert(vertex <= g->num_vertex);
    return g->marked[vertex];
}

void set_mark(const graph *g, size_t vertex, int visit)
{
    assert(vertex <= g->num_vertex);
    g->marked[vertex] = visit;
}

void init_marked(graph *g, int visit)
{
    for (size_t i = 0; i < g->num_vertex; i++)
        g->marked[i] = visit;
}

void DFS(graph *g, size_t start_vertex)
{
    assert(start_vertex <= g->num_vertex);

    set_mark(g, start_vertex, visited);
    int w = first(g, start_vertex);

    while (w < g->num_vertex)
    {
        if (get_mark(g, w) == unvisited)
            DFS(g, w);
        
        w = next(g, start_vertex, w);
    }
    
}

void DFS_traverse(graph *g, size_t start_vertex)
{
    assert(start_vertex <= g->num_vertex);
    init_marked(g, unvisited);

    for (size_t i = start_vertex; i < g->num_vertex; i++)
        if (get_mark(g, i) == unvisited)
            DFS(g, i);
}

void BFS(graph *g, size_t start_vertex)
{
    assert(start_vertex <= g->num_vertex);
    Queue *q = create_queue();

    enqueue(q, start_vertex);
    set_mark(g, start_vertex, visited);

    while (getSize(q) > 0)
    {
        int v = dequeue(q);
        int w = first(g, v);

        while (w < g->num_vertex)
        {
            if (get_mark(g, w) == unvisited)
            {
                set_mark(g, w, visited);
                enqueue(q, w);
            }

            w = next(g, v,  w);
        }
    }
}

void BFS_traverse(graph *g, size_t start_vertex)
{
    assert(start_vertex <= g->num_vertex);
    init_marked(g, unvisited);

    for (size_t i = start_vertex; i < g->num_vertex; i++)
        if (get_mark(g, i) == unvisited)
            BFS(g, i);
}

void toposort(graph *g, size_t v, stack *s)
{
    assert(v <= g->num_vertex);
    set_mark(g, v, visited);
    int w = first(g, v);

    while (w < g->num_vertex)
    {
        if (get_mark(g, w) == unvisited)
            toposort(g, w, s);
        w = next(g, v, w);        
    }
    push(s, v);
}

void Toposort_Traverse(graph *g, size_t start_vertex, stack *s)
{
    assert(start_vertex <= g->num_vertex);
    
    for (int i = 0; i < g->num_vertex; i++)
        set_mark(g, i, unvisited);
    for (int i = start_vertex; i < g->num_vertex; i++)
        if (get_mark(g, i) == unvisited)
            toposort(g, i, s);
}

int main()
{
    graph *g = create_graph(10);

    return 0;
}
