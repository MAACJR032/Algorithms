#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
    int element;
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
    Node *tail;
    int size;
} Queue;

Queue *create_queue();
int getSize(Queue *q);
int peek(Queue *q, bool *status);
void enqueue(Queue *q, int value);
int dequeue(Queue *q, bool *status);
void destroy_queue(Queue *q);

int main()
{
    Queue *q = create_queue();

    if (q->size == 0)
        printf("Empty\n");

    enqueue(q, 4);

    if (q->size != 0)
        printf("Not Empty\n");

    enqueue(q, 5);
    enqueue(q, 6);
    printf("size: %d\n", getSize(q));

    bool status = false;
    int x = 0;

    x = peek(q, &status);
    if (status) printf("peeked: %d\n", x);
    x = dequeue(q, &status);
    if (status) printf("Dequeued: %d\n", x);

    x = peek(q, &status);
    if (status) printf("peeked: %d\n", x);
    x = dequeue(q, &status);
    if (status) printf("Dequeued: %d\n", x);

    x = peek(q, &status);
    if (status) printf("peeked: %d\n", x);
    x = dequeue(q, &status);
    if (status) printf("Dequeued: %d\n", x);

    x = peek(q, &status);
    if (!status) printf("unsuccessful peek\n");
    x = dequeue(q, &status);
    if (!status) printf("unsuccessful Dequeue\n");
    
    destroy_queue(q);
    return 0;
}

Queue *create_queue()
{
    Queue *q = (Queue*) malloc(sizeof(Queue));

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;

    return q;
}

int getSize(Queue *q)
{
    return q->size;
}

int peek(Queue *q, bool *status)
{
    if (q->size == 0)
    {
        (*status) = false;
        return NULL;
    }

    (*status) = true;
    return q->head->element;
}

void enqueue(Queue *q, int value)
{
    Node *newNode = (Node*) malloc(sizeof(Node));

    newNode->element = value;
    newNode->next = NULL;

    if (q->size == 0)
    {
        q->head = newNode;
        q->tail = newNode;
    }
    else
    {   
        q->tail->next = newNode;
        q->tail = newNode;
    }
    q->size++;
}

int dequeue(Queue *q, bool *status)
{
    if (q->size == 0)
    {
        *status = false;
        return NULL;
    }

    *status = true;

    Node *temp = q->head;
    int value = q->head->element;

    if (q->size == 1)
    {
        q->head = NULL;
        q->tail = NULL;
    }
    else
        q->head = q->head->next;    

    free(temp);
    q->size--;
    
    return value;
}

void destroy_queue(Queue *q)
{
    Node *curr = q->head;

    while (curr != NULL)
    {
        Node *temp = curr;
        curr = curr->next;
        free(temp);
    }
    free(q);   
}