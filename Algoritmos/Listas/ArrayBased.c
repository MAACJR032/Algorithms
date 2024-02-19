#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int maxSize, listSize, curr;
    int *listArray;
} List;

List *create_list(int size);
void insert(List *l, int val);
void moveToStart(List *l);
void moveToEnd(List *l);
void prev(List *l);
void next(List *l);
int Remove(List *l);

int main()
{
    List *l = create_list(5);
    insert(l, 7);
    next(l);
    insert(l, 5);
    next(l);
    insert(l, 2);

    for (int i = 0; i < l->listSize; i++)
        printf("%d ", l->listArray[i]);
    printf("\n");

    // for (int i = 0; i < l->listSize; i++)
    //     printf("%d ", l->listArray[i]);
    // printf("\n");
    
    // l->curr = l->listSize;
    l->curr = 0;
    Remove(l);

    for (int i = 0; i < l->listSize; i++)
        printf("%d ", l->listArray[i]);
    printf("\n");

    prev(l);
    Remove(l);

    for (int i = 0; i < l->listSize; i++)
        printf("%d ", l->listArray[i]);
    printf("\n");
    return 0;
}

List *create_list(int size)
{
    List *l = (List*) malloc(sizeof(List));
    
    l->maxSize = size;
    l->listSize = l->curr = 0;
    l->listArray = (int*) malloc(size*sizeof(int));

    return l;
}

void insert(List *l, int val)
{
    if (l->listSize >= l->maxSize)
        return;

    int i = l->listSize;
    while (i > l->curr)
    {
        l->listArray[i] = l->listArray[i-1];
        i--;
    }
    
    l->listArray[l->curr] = val;
    l->listSize++;
}

void moveToStart(List *l)
{
    l->curr = 0;
}

void moveToEnd(List *l)
{
    l->curr = l->listSize;
}

void prev(List *l)
{
    if (l->curr != 0)
        l->curr--;
}

void next(List *l)
{
    if (l->curr < l->listSize)
        l->curr++;
}

int Remove(List *l)
{
    if ((l->curr < 0) || (l->curr >= l->listSize))
        return NULL;
    
    int val = l->listArray[l->curr];
    int i = l->curr;

    while (i < l->listSize-1)
    {
        l->listArray[i] = l->listArray[i+1];
        i++;
    }
    l->listSize--;
    
    return val;
}