#include <iostream>
using namespace std;

class Node
{
    public:
        int val;
        Node *next;

        Node(int Val, Node *Next)
        {
            val = Val;
            next = Next;
        }
        Node(Node *Next)
        {
            next = Next;
        }
};

class List
{
    private:
        // Node *head, *curr, *tail;
        int size;

    public:
        List()
        {
            // curr = tail = head = CreateNode(NULL);
            size = 0;
        }
        ~List()
        {
            // while (head != NULL)
            // {

            // }
        }

        Node *CreateNode(Node *Next)
        {
            next = Next;
        } 
};

typedef struct
{
    Node *head, *curr, *tail;
    int size;
} Lista;


Lista *create_list();
void add_begin(Lista *l, int val);
void add_end(Lista *l, int val);
void add_by_index(Lista *l, int val);
void print_list(Lista *l);
int remove_first(Lista *l);
int remove_by_index(Lista *l);
void moveToStart(Lista *l);
void prev(Lista *l);
void next(Lista *l);
void moveToEnd(Lista *l);

int main()
{
    
    return 0;
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
    // Node *novo = (Node*) malloc(sizeof(Node));
    // novo->val = val;
    // novo->next = l->curr->next;

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
    l->curr = l->head;
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