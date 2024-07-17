#include "../Listas/DoublyLinked.h"
#include "../Listas/Linked_stack.h"
#include "../Listas/LinkedQueue.h"
#include <stdarg.h>

#define visited 1
#define unvisited 0

struct graph
{
    int num_vertex;
    bool *marked;
    list **l;
};
typedef struct graph graph;

graph* create_graph(const size_t num_vertex)
{
    graph *g = (graph *) malloc(sizeof(graph));
    assert(g != NULL);

    g->l = (list **) malloc(sizeof(list) * num_vertex);
    assert(g->l != NULL);

    for (size_t i = 0; i < num_vertex; i++)
        g->l[i] = create_list();
    
    g->marked = (bool *) malloc(sizeof(bool) * num_vertex);
    assert(g->marked != NULL);;

    g->num_vertex = num_vertex;
    return g;
}

int first(graph *g, size_t vertex)
{
    assert(vertex <= g->num_vertex);

    if (empty(g->l[vertex]))
        return g->num_vertex;
    return front(g->l[vertex]);
}

bool is_edge(graph *g, size_t vertex1, size_t vertex2)
{
    assert(vertex1 <= g->num_vertex && vertex2 <= g->num_vertex);

    node *i = begin(g->l[vertex1]);
    while (i != end(g->l[vertex1]))
    {
        if (i->val == vertex2)
            return true;
        
        i = i->next;
    }
    
    return false;
}

int next(graph *g, size_t vertex1, size_t vertex2)
{
    assert(vertex1 <= g->num_vertex && vertex2 <= g->num_vertex);

    node *i = begin(g->l[vertex1]);
    while (i != end(g->l[vertex1]))
    {
        if (i->val == vertex2 && (i->next != end(g->l[vertex1])))
            return i->next->val;
        
        i = i->next;
    }

    return g->num_vertex;
}

void set_edge(graph *g, size_t vertex1, size_t vertex2)
{
    assert(vertex1 <= g->num_vertex && vertex2 <= g->num_vertex);

    push_back(g->l[vertex1], vertex2);
    push_back(g->l[vertex2], vertex1);
}

void set_n_edges(graph *g, size_t vertex, size_t n, ...)
{
    assert(vertex <= g->num_vertex && n >= 0);
    
    va_list args;
    va_start(args, n);

    for (size_t i = 0; i < n; i++)
    {
        int v = va_arg(args, int);

        push_back(g->l[vertex], v);
        push_back(g->l[vertex], v);
    }
    
    va_end(args);
}

void del_edge(graph *g, size_t vertex1, size_t vertex2)
{
    assert(vertex1 <= g->num_vertex && vertex2 <= g->num_vertex);

    node *i = begin(g->l[vertex1]);
    while (i != end(g->l[vertex1]))
    {
        if (i->val == vertex2)
        {
            pop_node(g->l[vertex1], i);
            break;
        }
            
        i = i->next;
    }

    i = begin(g->l[vertex2]);
    while (i != end(g->l[vertex2]))
    {
        if (i->val == vertex1)
        {
            pop_node(g->l[vertex2], i);
            break;
        }
            
        i = i->next;
    }
}

int get_mark(graph *g, size_t vertex)
{
    assert(vertex <= g->num_vertex);
    return g->marked[vertex];
}

void set_mark(graph *g, size_t vertex, int visit)
{
    assert(vertex <= g->num_vertex);
    g->marked[vertex] = visit;
}

void init_marked(graph *g, int visit)
{
    for (size_t i = 0; i < g->num_vertex; i++)
        g->marked[i] = visit;
}

void print_graph(const graph *g)
{
    for (size_t i = 0; i < g->num_vertex; i++)
    {
        printf("%d: ", i);
        for (node *n = begin(g->l[i]); n != end(g->l[i]); n = n->next)
            printf("%d -> ", n->val);
        printf("\n");
    }
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
        setMark(i, unvisited);
    for (int i = start_vertex; i < g->num_vertex; i++)
        if (getMark(i) == unvisited)
            toposort(g, i, s);
}

int main()
{
    graph *g = create_graph(5);

    return 0;
}
