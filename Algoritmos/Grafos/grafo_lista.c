#include "../Listas/DoublyLinked.h"

#define visited 1
#define unvisited 0

struct graph
{
    int num_vertex;
    bool *marked;
    list **l;
};
typedef struct graph graph;

graph* create_graph(const int num_vertex)
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

int first(graph *g, int vertex)
{
    if (empty(g->l[vertex]))
        return g->num_vertex;
    return front(g->l[vertex]);
}

bool is_edge(graph *g, int vertex1, int vertex2)
{
    node *i = begin(g->l[vertex1]);
    while (i != end(g->l[vertex1]))
    {
        if (i->val == vertex2)
            return true;
        
        i = i->next;
    }
    
    return false;
}

int next(graph *g, int vertex1, int vertex2)
{
    node *i = begin(g->l[vertex1]);
    while (i != end(g->l[vertex1]))
    {
        if (i->val == vertex2 && (i->next != end(g->l[vertex1])))
            return i->next->val;
        
        i = i->next;
    }

    return g->num_vertex;
}

void set_edge(graph *g, int vertex1, int vertex2)
{
    push_back(g->l[vertex1], vertex2);
    push_back(g->l[vertex2], vertex1);
}

void del_edge(graph *g, int vertex1, int vertex2)
{
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

int get_mark(graph *g, int vertex) { return g->marked[vertex]; }
void set_mark(graph *g, int vertex, int visit) { g->marked[vertex] = visit; }

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

int main()
{
    graph *g = create_graph(5);

    return 0;
}