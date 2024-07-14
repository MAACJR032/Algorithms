#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

struct node
{
    int val;
    struct node *next;
    struct node *prev;
};
typedef struct node node;

struct list
{
    size_t size;
    node *head;
    node *tail;
};
typedef struct list list;

node* new_empty_node()
{
    node *n = (node *) malloc(sizeof(node));
    assert(n != NULL);

    return n;
}

node* new_node(int val, node *next, node *prev)
{
    node *n = (node *) malloc(sizeof(node));
    assert(n != NULL);
    
    n->val = val;
    n->next = next;
    n->prev = prev;

    return n;
}

list* create_list()
{
    list *l = (list *) malloc(sizeof(list));
    assert(l != NULL);

    l->head = new_empty_node();
    l->tail = new_empty_node();

    l->head->next = l->tail;
    l->head->prev = NULL;

    l->tail->next = NULL;
    l->tail->prev = l->head;

    l->size = 0;

    return l;
}

bool empty(const list *l) { return l->head->next == l->tail; }

void push_back(list *l, int val)
{
    node *n = new_node(val, l->tail, l->tail->prev);
    
    n->prev->next = n;
    l->tail->prev = n;

    l->size++;
}

void push_front(list *l, int val)
{
    node *n = new_node(val, l->head->next, l->head);

    l->head->next = n;
    n->next->prev = n;

    l->size++;
}

int pop_back(list *l)
{
    assert(!empty(l));
    node *temp = l->tail->prev;

    temp->prev->next = l->tail;
    l->tail->prev = temp->prev;

    int val = temp->val;
    free(temp);

    l->size--;
    return val;
}

int pop_front(list *l)
{
    assert(!empty(l));
    node *temp = l->head->next;

    l->head->next = temp->next;
    temp->next->prev = l->head;

    int val = temp->val;
    free(temp);

    l->size--;
    return val;
}

int pop_node(list *l, node *n)
{
    assert(!empty(l));

    n->next->prev = n->prev;
    n->prev->next = n->next;
    
    int val = n->val;
    free(n);

    l->size--;
    return val;
}

size_t size(const list *l) { return l->size; }

node* begin(const list *l) { return l->head->next; }

node* end(const list *l) { return l->tail; }

node* rbegin(const list *l) { return l->tail->prev; }

node* rend(const list *l) { return l->head; }

void remove_val(list *l, int val)
{
    for (node *curr = begin(l); curr != end(l); curr = curr->next)
    {
        if (curr->val == val)
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
    node *curr = rbegin(l);
    while (curr != rend(l))
    {   
        free(curr->next);
        curr = curr->prev;
    }
    
    free(curr);
    free(l);
}

void print_list(const list *l)
{
    for (node *i = begin(l); i != end(l); i = i->next)
        printf("%d ", i->val);
    printf("\n");
}

void rprint_list(const list *l)
{
    for (node *i = rbegin(l); i != rend(l); i = i->prev)
        printf("%d ", i->val);
    printf("\n");
}

int main()
{
    list *l = create_list();

    return 0;
}
