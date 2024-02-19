#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int element;
    struct Node *next;
} Node;

typedef struct
{
    Node *head, *tail, *curr;
    int size;
} List;

List *create_list();
void insert(List *l, int value);
void append(List *l, int value);
void removeAll(List *l);
int Remove(List *l);
void moveToStart(List *l);
void moveToEnd(List *l);
void prev(List *l);
void next(List *l);
int get_size(List *l);
int currPos(List *l);
int get_value(List *l);

int main()
{
    List *l = create_list();
    
    append(l, 5);

    int value=0;
    value = get_value(l);
    printf("%d\n", value);
    
    append(l, 10);
    moveToEnd(l);

    int size=0;
    size = get_size(l);
    
    printf("%d\n", size);
    Remove(l);

    size = get_size(l);
    printf("%d\n", size);

    return 0;
}

List *create_list()
{
    List *l = (List*) malloc(sizeof(List));

    l->head = (Node*) malloc(sizeof(Node));
    l->curr = l->head;
    l->tail = l->head;
    l->size = 0;

    return l;
}

void insert(List *l, int value)
{
    Node *temp = (Node*) malloc(sizeof(Node));

    temp->element = value;
    temp = l->curr->next;
    l->curr->next = temp;
    
    if (l->tail == l->curr)
        l->tail = l->curr->next;
    l->size++;    
}

void append(List *l, int value)
{
    Node *temp = (Node*) malloc(sizeof(Node));

    l->tail->next = temp;
    l->tail = l->tail->next; 
    temp->element = value;
    temp->next = NULL;
    l->size++;
}

void removeAll(List *l)
{
    while (l->head != NULL)
    {
        l->curr = l->head;
        l->head = l->head->next;
        free(l->curr);
    }   
}

int Remove(List *l)
{
    if (l->curr->next != NULL)
        return -1;
    
    printf("AAA\n");
    int it = l->curr->element;
    
    Node *ltemp = l->curr->next;

    if (l->tail == l->curr->next)
        l->tail = l->curr;
    
    l->curr = l->curr->next; 
    
    free(ltemp);
    l->size--;

    return it;
}

void moveToStart(List *l)
{ 
    l->curr = l->head; 
}

void moveToEnd(List *l)
{ 
    l->curr = l->tail; 
}

void prev(List *l)
{
    if (l->curr == l->head)
        return;
    Node *temp = l->head;

    while (temp->next != l->curr)
    {
        temp = temp->next;
    }
    
    l->curr = temp;
}

void next(List *l)
{
    if (l->curr != l->tail)
        l->curr = l->curr->next;
}

int get_size(List *l)
{
    return l->size;
}

int currPos(List *l)
{
    Node *temp = l->head;

    int i;
    for (i = 0; l->curr != temp; i++)
        temp = temp->next;
    
    return i;
}

void moveToPos(List *l, int pos)
{
    if ((pos >= 0) && (pos <= l->size))
        l->curr = l->head;
    
    for (int i = 0; i < pos; i++)
        l->curr = l->curr->next;
}

int get_value(List *l)
{
    if (l->curr->next != NULL)
        return -1;
    
    return l->curr->next->element;
}