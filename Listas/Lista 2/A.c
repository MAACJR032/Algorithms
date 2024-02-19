#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char val;
    struct Node *next;
} Node;

typedef struct
{
    Node *head, *curr, *tail;
    int size;
} Lista;

Node *create_node1(char val, Node *nextval);
Node *create_node2(Node *nextval);
Lista *create_list();
void add_end(Lista *l, char val);
void add_by_index(Lista *l, char val);
void print_list(Lista *l);
void moveToEnd(Lista *l);
void removeAll(Lista *l);

int main()
{
    Lista *l = create_list();
    char beiju[100002];

    while (scanf(" %s", beiju))
    {
        int i = 0;
        while (i < strlen(beiju))
        {
            if (beiju[i] =='[')
            {
                l->curr = l->head;
                i++;
                while (beiju[i] != ']' && beiju[i] != '[')
                {
                    add_by_index(l, beiju[i]);
                    if (l->curr != l->tail)
                        l->curr = l->curr->next;
                    i++;
                }
            }
            else if (beiju[i] ==']')
                moveToEnd(l);
            else
                add_end(l, beiju[i]);
            i++;
        }
        print_list(l);
        removeAll(l);
        l->curr = l->tail = l->head = create_node2(NULL);
    }
    
    return 0;
}

Node *create_node1(char val, Node *nextval)
{
    Node *novo = (Node*) malloc(sizeof(Node));

    novo->val = val;
    novo->next = nextval;

    return novo;
}

Node *create_node2(Node *nextval)
{
    Node *novo = (Node*) malloc(sizeof(Node));

    novo->next = nextval;
    return novo;
}

Lista *create_list()
{
    Lista *l = (Lista*) malloc(sizeof(Lista));

    l->curr = l->tail = l->head = create_node2(NULL);
    l->size = 0;

    return l;
}

void add_end(Lista *l, char val)
{
    Node *novo = (Node*) malloc(sizeof(Node));
    novo->val = val;
    novo->next = NULL;

    if (l->head == NULL) // Lista vazia
        l->head = novo;
    else // Lista não-vazia
        l->tail->next = novo;
    
    l->tail = novo;
    l->size++;
}

void add_by_index(Lista *l, char val)
{
    l->curr->next = create_node1(val, l->curr->next);

    // cursor está no fim
    if (l->tail == l->curr)
        l->tail = l->curr->next;
    
    l->size++;
}

void print_list(Lista *l)
{
    // Se a lista não está vazia
    if (l->head != NULL)
    {
        Node *temp = l->head->next;

        while (temp != NULL)
        {
            printf("%c", temp->val);
            temp = temp->next;
        }
        printf("\n");
    }
}

void moveToEnd(Lista *l)
{
    if (l->curr->next == NULL)
        return;
    
    while (l->curr->next != l->tail)
    {
        if (l->curr != l->tail)
            l->curr = l->curr->next;
    } 
}

void removeAll(Lista *l)
{
    while (l->head != NULL)
    {
        l->curr = l->head;
        l->head = l->head->next;
        free(l->curr);
    }
    l->size = 0;
}