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
void add_begin(Lista *l, int val);
void add_end(Lista *l, int val);
void add_by_index(Lista *l, int val);
void print_list(Lista *l);
int remove_first(Lista *l);
// int remove_last();
int remove_by_index(Lista *l);
void moveToStart(Lista *l);
void prev(Lista *l);
void next(Lista *l);
void moveToEnd(Lista *l);

int main()
{
    Lista *l;
    int val;

    l = create_list();

    add_by_index(l, 7);
    print_list(l);
    next(l);

    add_by_index(l, 5);
    print_list(l);
    next(l);
    
    add_by_index(l, 2);
    print_list(l);
    next(l);

    add_by_index(l, 10);
    print_list(l);

    // prev(l);

    remove_by_index(l);
    print_list(l);

    prev(l);
    remove_by_index(l);
    print_list(l);

    prev(l);
    remove_by_index(l);
    print_list(l);
    

    // int op = -1;

    // do
    // {
    //     printf("1 - add inicio\n"
    //            "2 - add fim\n"
    //            "3 - remove inicio\n"
    //            "4 - print\n"
    //            "0 - stop\n");
    //     scanf("%d", &op);

    //     switch (op)
    //     {
    //         case 0:
    //             break;
    //         case 1:
    //             printf("inicio: ");
    //             scanf("%d", &val);

    //             add_begin(l, val);
    //             break;
    //         case 2:
    //             printf("fim: ");
    //             scanf("%d", &val);
                
    //             add_end(l, val);
    //             break;
    //         case 3:
    //             val = remove_first(l);
    //             if (val != -1)
    //                 printf("removido inicio: %d\n", val);
    //             break;
    //         case 4:
    //             print_list(l);
    //             break;
    //         default:
    //             printf("invalido\n\n");
    //             break;
    //     }
    // } while (op != 0);
    
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

void add_begin(Lista *l, int val)
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

void add_end(Lista *l, int val)
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

void add_by_index(Lista *l, int val)
{
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

int remove_first(Lista *l)
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

int remove_by_index(Lista *l)
{
    // Remove o elemento apos o cursor

    // O cursor está no último elemento
    if (l->curr->next == NULL)
        return NULL;
    
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
    l->curr = l->head->next;
}

void prev(Lista *l)
{
    Node *temp;

    if (l->curr == l->head)
    {
        printf("Erro. o cursor ja esta no inicio\n\n");
        return;
    }
    else
    {
        temp = l->head;   

        do
        {
            temp = temp->next;
        } while (temp->next != l->curr);
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