#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct vector
{
    int size, max_size;
    int *arr;
};
typedef struct vector vector;

// Constructors
void vector_init(vector *v)
{    
    v->max_size = 10; 
    v->size = 0;

    v->arr = (int *) malloc(sizeof(int) * v->max_size);
    if (v->arr == NULL)
        printf("Error allocating memory\n");
}
void vector_init_size(vector *v, int init_size)
{    
    if (init_size > 0)
        v->max_size = init_size;
    else
        v->max_size = 20; 
    
    v->size = 0;
    v->arr = (int *) malloc(sizeof(int) * v->max_size);
    if (v->arr == NULL)
        printf("Error allocating memory\n");
}
void vector_init_elem(vector *v, int init_size, int init_elem)
{
    if (init_size > 0)
        v->max_size = init_size;
    else
        v->max_size = 20; 
    
    v->size = v->max_size;
    v->arr = (int *) malloc(sizeof(int) * v->max_size);
    if (v->arr == NULL)
    {   
        printf("Error allocating memory\n");
        return;
    }
    
    for (size_t i = 0; i < v->max_size; i++)
        v->arr[i] = init_elem;
}

// Destructor
void destroy_vector(vector *v)
{
    free(v->arr);
}

// Return functions
int size(const vector *v)
{
    return v->size;
}
bool empty(const vector *v)
{
    return (v->size == 0);
}
int capacity(const vector *v)
{
    return v->max_size;
}

// Inserction functions
void push_back(vector *v, int val)
{
    if (v->size == v->max_size)
    {
        v->max_size *= 2;
    
        int *temp = v->arr;
        temp = (int *) realloc(v->arr, sizeof(int) * v->max_size);

        if (temp == NULL)
        {
            printf("Error Reallocating\n");
            free(v->arr);
            return;
        }

        v->arr = temp;
    }
    
    v->arr[v->size] = val;
    v->size++;
}
void insert(vector *v, int val, int index)
{
    if (index > v->max_size|| index < 0)
        return;

    if (v->size == v->max_size)
    {
        v->max_size *= 2;

        int *temp = v->arr;
        temp = (int *) realloc(v->arr, sizeof(int) * v->max_size);

        if (temp == NULL)
        {
            printf("Error Reallocating\n");
            free(v->arr);
            return;
        }

        v->arr = temp;
    }
    
    for (int i = v->size; i > index; i--)
        v->arr[i] = v->arr[i-1];
        
    v->arr[index] = val;
    v->size++;
}

// Remove functions
int pop_back(vector *v)
{
    if (v->size == 0)
    {
        printf("Vector is already empty\n");
        return -1;
    }
    
    int tmp = v->arr[v->size-1];
    v->size--;

    return tmp;
}
void erase(vector *v, int start, int end)
{
    if (start < 0 || start > v->size || end < 0 || end > v->size || end < start)
    {
        printf("Out of range\n");
        return;
    }

    if (end == start)
    {
        v->size = start;
        return;
    }
    
    for (size_t i = start, j = end; i < v->size; i++, j++)
        v->arr[i] = v->arr[j];

    v->size -= end - start;
}

// Non-returns functions
void clear(vector *v)
{
    free(v->arr);
    v->size = 0;
    v->max_size = 10;
    
    v->arr = (int *) malloc(sizeof(int) * v->max_size);
    if (v->arr == NULL)
    {
        printf("Error allocating memory\n");
        return;
    }
}
void vector_print(const vector *v)
{
    for (size_t i = 0; i < v->size; i++)
        printf("%d ", v->arr[i]);
    printf("\n");
}
void resize(vector *v, int size)
{
    if (size < 0)
    {
        printf("Out of range\n");
        return;
    }

    if (size <= v->size)
        v->size = size;
    else
    {
        v->max_size = size;

        int *temp = v->arr;
        temp = (int *) realloc(v->arr, sizeof(int) * v->max_size);

        if (temp == NULL)
        {
            printf("Error Reallocating\n");
            free(v->arr);
            return;
        }

        v->arr = temp;
        v->size = v->max_size;
    }
}
void resize_elem(vector *v, int size, int elem)
{
    if (size < 0)
    {
        printf("Out of range\n");
        return;
    }
    
    free(v->arr);
    
    v->size = size;
    v->max_size = size;

    v->arr = (int *) malloc(sizeof(int) * v->max_size);
    if (v->arr == NULL)
    {
        printf("Error allocating memory\n");
        return;
    }
    
    for (size_t i = 0; i < v->max_size; i++)
        v->arr[i] = elem;
}
void swap(int *param1, int *param2)
{
    int temp = *param1;
    *param1 = *param2;
    *param2 = temp;
}
void vetor_swap(vector *v1, vector *v2)
{    
    swap(&v1->size, &v2->size);
    swap(&v1->max_size, &v2->max_size);
    swap(v1->arr, v2->arr);
}
