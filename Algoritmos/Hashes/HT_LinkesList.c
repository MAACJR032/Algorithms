#include <stdio.h>
#include <stdlib.h>

#define TAM 5

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
int remove_by_index(Lista *l);
int SearchList(Lista *l, int val);
void moveToStart(Lista *l);
void prev(Lista *l);
void next(Lista *l);
void moveToEnd(Lista *l);

void CreateHash(Lista t[])
{
    for (int i = 0; i < TAM; i++)
        create_list(&t[i]);  
}

int HashFunction(int key)
{
    return abs(key%TAM);
}

int search(Lista t[], int key)
{
    int index = HashFunction(key);
    return SearchList(&t[index], key);
}

void insert(Lista t[], int val)
{
    int index = HashFunction(val);
    int aux;
    if ((aux = search(t, val)) != 0)
        add_by_index(&t[index], val);
}

void print(Lista t[])
{
    for (int i = 0; i < TAM; i++)
    {
        printf("%2d = ", i);
        print_list(&t[i]);
    }
    printf("\n");
}

int main()
{
    Lista hash[TAM];
    int x, found;
    int op=0;

    CreateHash(hash);
    do
    {
        printf("1-Inserir\n2-Buscar\n3-Imprimir\n4-Sair\n");
        scanf("%d", &op);

        switch (op)
        {
            case 1:
                scanf("%d", &x);
                insert(hash, x);
                break;
            case 2:
                scanf("%d", &x);
                found = search(hash, x);
                
                if (found != 0)
                    printf("Encontrado\n");
                else
                    printf("Nao Encontrado\n");
                break;
            case 3:
                print(hash);
                break;
            case 4:
                break;
            default:
                break;
        }
    } while (op != 4);
    
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

    // printf("Head -> ");
    printf("tam: %d: ", l->size);
    while (temp != NULL)
    {
        printf("%d ", temp->val);
        temp = temp->next;
    }
    // printf("<- tail\n\n");
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

int SearchList(Lista *l, int val)
{
    Node *aux = l->head;

    while ((aux != NULL) && aux->val != val)
    {
        aux = aux->next;
    }
    if (aux)
        return aux->val;
    return 0;
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