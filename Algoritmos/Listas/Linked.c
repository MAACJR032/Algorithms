#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int val;
    struct Node *next;
} Node;

typedef struct
{
    Node *head, *curr, *tail;
    int size;
} Lista;

Node *create_node1(int val, Node *nextval);
Node *create_node2(Node *nextval);
Lista *create_list();
void push_front(Lista *l, int val);
void push_back(Lista *l, int val);
void push_after_curr(Lista *l, int val);
void print_list(Lista *l);
int pop_front(Lista *l);
// int remove_last();
int pop_after_curr(Lista *l);
void moveToStart(Lista *l);
void prev(Lista *l);
void next(Lista *l);
void moveToEnd(Lista *l);

int main()
{
    Lista *l;
    int val;

    l = create_list();

    push_after_curr(l, 7);
    print_list(l);
    next(l);

    push_after_curr(l, 5);
    print_list(l);
    prev(l);
    
    push_after_curr(l, 2);
    print_list(l);

    moveToStart(l);
    push_after_curr(l, 10);
    print_list(l);

    pop_after_curr(l);
    print_list(l);

    next(l);
    pop_front(l);
    print_list(l);

    next(l);
    pop_after_curr(l);
    print_list(l);
    
    prev(l);
    pop_after_curr(l);
    print_list(l);

    return 0;
}

Node *create_node1(int val, Node *nextval)
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

    l->head = create_node2(NULL);
    l->tail = l->head;
    l->curr = l->head;
    l->size = 0;

    return l;
}

void push_front(Lista *l, int val)
{
    Node *novo = (Node*) malloc(sizeof(Node));

    novo->val = val;
    novo->next = NULL;

    if (l->head == NULL) // Lista vazia
        l->tail = novo;
    else // Lista não-vazia
        novo->next = l->head;

    l->head = novo;
    l->size++;
}

void push_back(Lista *l, int val)
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

void push_after_curr(Lista *l, int val)
{
    // Insere após o cursor

    l->curr->next = create_node1(val, l->curr->next);

    // cursor está no fim
    if (l->tail == l->curr)
        l->tail = l->curr->next;
    
    l->size++;
}

void print_list(Lista *l)
{
    Node *temp = l->head->next;

    printf("Head -> ");

    while (temp != NULL)
    {
        printf("%d ", temp->val);
        temp = temp->next;
    }
    printf("<- tail\n\n");
}

int pop_front(Lista *l)
{
    Node *temp = l->head;
    int val;

    if (temp == NULL) // Lista vazia
    {
        printf("Lista vazia\n\n");
        return -1;
    }
    else // Lista não-vazia
    {
        l->head = l->head->next;
        temp->next = NULL;
        val = temp->val;
        free(temp);
        l->size--;

        return val;
    }    
}

// int remove_last(Lista *l)
// {

// }

int pop_after_curr(Lista *l)
{
    // Remove o elemento após o cursor

    // O cursor está no último elemento
    if (l->curr->next == NULL)
        return -1;
    
    int val = l->curr->next->val;

    // Volta em um elemento o tail
    if (l->tail == l->curr->next)
        l->tail = l->curr;

    l->curr->next = l->curr->next->next;
    l->size--;

    return val;
}

void moveToStart(Lista *l)
{
    l->curr = l->head;
}

void prev(Lista *l)
{
    Node *temp;

    if (l->curr == l->head)
    {
        printf("O cursor ja esta no inicio\n\n");
        return;
    }
    else
    {
        temp = l->head;   

        while (temp->next != l->curr)
        {
            temp = temp->next;
        }
        l->curr = temp;
    }
}


void next(Lista *l)
{
    // Se não está no fim
    if (l->curr != l->tail)
        l->curr = l->curr->next;
}

void moveToEnd(Lista *l)
{
    do
    {
        next(l);
    } while (l->curr->next != l->tail); 
}
