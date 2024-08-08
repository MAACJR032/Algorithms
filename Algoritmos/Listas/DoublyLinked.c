#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

struct list;

struct node
{
    int elem;
    struct node *next;
    struct node *prev;
    struct list *origin;
};
typedef struct node node;

struct list
{
    size_t size;
    node *head;
    node *tail;
};
typedef struct list list;

node* new_node(int elem, node *next, node *prev)
{
    node *n = (node *) malloc(sizeof(node));
    assert(n != NULL);
    
    n->elem = elem;
    n->next = next;
    n->prev = prev;

    return n;
}

list* new_list()
{
    list *l = (list *) malloc(sizeof(list));
    assert(l != NULL);

    l->head = new_node(0, NULL, NULL);
    l->tail = new_node(0, NULL, NULL);

    l->head->next = l->tail;
    l->head->prev = NULL;

    l->tail->next = NULL;
    l->tail->prev = l->head;

    l->size = 0;

    return l;
}

bool empty(const list *l) { return l->head->next == l->tail; }

size_t size(const list *l) { return l->size; }

node* begin(const list *l) { return l->head->next; }

node* end(const list *l) { return l->tail; }

node* rbegin(const list *l) { return l->tail->prev; }

node* rend(const list *l) { return l->head; }

int front(const list *l)
{
    assert(l != NULL || !empty(l));
    return l->head->next->elem;
}

int back(const list *l)
{
    assert(l != NULL || !empty(l));
    return l->tail->prev->elem;
}

void push_back(list *l, int elem)
{
    node *n = new_node(elem, l->tail, l->tail->prev);
    
    n->prev->next = n;
    l->tail->prev = n;

    l->size++;
}

void push_front(list *l, int elem)
{
    node *n = new_node(elem, l->head->next, l->head);

    l->head->next = n;
    n->next->prev = n;

    l->size++;
}

void push_back_list(list *l, const list *src)
{
    assert(l != NULL || src != NULL);

    if (empty(src))
        return;

    for (node *n = begin(src); n != end(src); n = n->next)
        push_back(l, n->elem);
}

void push_front_list(list *l, const list *src)
{
    assert(l != NULL || src != NULL);

    if (empty(src))
        return;

    for (node *n = rbegin(src); n != rend(src); n = n->prev)
        push_front(l, n->elem);
}

int pop_back(list *l)
{
    assert(l != NULL || !empty(l));
    node *temp = l->tail->prev;

    temp->prev->next = l->tail;
    l->tail->prev = temp->prev;

    int elem = temp->elem;
    free(temp);

    l->size--;
    return elem;
}

int pop_front(list *l)
{
    assert(l != NULL || !empty(l));
    node *temp = l->head->next;

    l->head->next = temp->next;
    temp->next->prev = l->head;

    int elem = temp->elem;
    free(temp);

    l->size--;
    return elem;
}

int pop_node(list *l, node *n)
{
    assert(l != NULL || !empty(l));

    n->next->prev = n->prev;
    n->prev->next = n->next;
    
    int elem = n->elem;
    free(n);

    l->size--;
    return elem;
}

void remove_elem(list *l, int elem)
{
    for (node *curr = begin(l); curr != end(l); curr = curr->next)
    {
        if (curr->elem == elem)
        {
            node *aux = curr->prev;
            pop_node(l, curr);
            curr = aux;
        }
    }
}

void clear(list *l)
{
    node *curr = rbegin(l);
    while (curr != rend(l))
    {   
        pop_node(l, curr);
        curr = rbegin(l);
    }
}

void destroy_list(list *l)
{
    clear(l);
    free(l);
}

void print_list(const list *l)
{
    for (node *i = begin(l); i != end(l); i = i->next)
        printf("%d ", i->elem);
    printf("\n");
}

void rprint_list(const list *l)
{
    for (node *i = rbegin(l); i != rend(l); i = i->prev)
        printf("%d ", i->elem);
    printf("\n");
}
