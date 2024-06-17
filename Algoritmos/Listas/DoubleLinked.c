#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char val;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct
{
    Node *head, *curr, *tail;
    long long size;
} Lista;

Node *create_node1(char val, Node *nextval);
Node *create_node2(Node *nextval);
Lista *create_list();
void add_by_index(Lista *l, char val);
void add_end(Lista *l, char val);
void prev(Lista *l);
void next(Lista *l);
char remove_by_index(Lista *l);
void print_list(Lista *l);

int main()
{
    Lista *l = create_list();
    
    return 0;
}

Node *create_node1(char val, Node *nextval)
{
    Node *novo = (Node*) malloc(sizeof(Node));
    novo->val = val;
    novo->next = nextval;
    novo->prev = NULL;
    return novo;
}

Node *create_node2(Node *nextval)
{
    Node *novo = (Node*) malloc(sizeof(Node));
    novo->next = nextval;
    novo->prev = NULL;
    return novo;
}

Lista *create_list()
{
    Lista *l = (Lista*) malloc(sizeof(Lista));
    l->curr = l->tail = l->head = create_node2(NULL);
    l->head->prev = NULL;
    l->size = 0;

    return l;
}

void add_by_index(Lista *l, char val)
{
    l->curr->next = create_node1(val, l->curr->next);
    l->curr->next->prev = l->curr;    

    if (l->tail == l->curr)
        l->tail = l->curr->next;
    else
        l->curr->next->next->prev = l->curr->next;
    l->size++;

    // next
    if (l->curr != l->tail)
        l->curr = l->curr->next;
}

void add_end(Lista *l, char val)
{
    Node *novo = (Node*) malloc(sizeof(Node));
    novo->val = val;
    novo->next = NULL;
    novo->prev = l->tail;

    l->tail->next = novo;
    l->tail = novo;
    l->size++;
}

void prev(Lista *l)
{
    if (l->curr->prev != NULL)
        l->curr = l->curr->prev;
}

void next(Lista *l)
{
    if (l->curr->next != NULL)
        l->curr = l->curr->next;
}

char remove_by_index(Lista *l)
{
    if (l->curr->next == NULL)
        return -1;

    Node *tmp = l->curr->next;
    char val = tmp->val;
    
    if (tmp == l->tail)
        l->tail = l->curr;
    else
        tmp->next->prev = l->curr;
    l->curr->next = tmp->next;

    free(tmp);
    l->size--;
    
    return val;
}

void print_list(Lista *l)
{
    Node *temp = l->head->next;

    while (temp != NULL)
    {
        printf("%c", temp->val);
        temp = temp->next;
    }
    printf("\n");
}