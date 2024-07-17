#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

struct vector
{
    int size, max_size;
    int *arr;
};
typedef struct vector vector;

// Constructors
vector* vector_init()
{    
    vector *v;
    v->max_size = 10; 
    v->size = 0;

    v->arr = (int *) malloc(sizeof(int) * v->max_size);
    assert(v->arr != NULL);
    
    return v;
}
void vector_init_size(vector *v, int init_size)
{    
    if (init_size > 0)
        v->max_size = init_size;
    else
        v->max_size = 20; 
    
    v->size = 0;
    v->arr = (int *) malloc(sizeof(int) * v->max_size);
    assert(v->arr != NULL);
}
void vector_init_elem(vector *v, int init_size, int init_elem)
{
    if (init_size > 0)
        v->max_size = init_size;
    else
        v->max_size = 20; 
    
    v->size = v->max_size;
    v->arr = (int *) malloc(sizeof(int) * v->max_size);
    assert(v->arr != NULL);
    
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
int at(const vector *v, int index)
{
    assert(index > 0 && index < v->size);
    return v->arr[index];
}

// Inserction functions
void push_back(vector *v, int val)
{
    if (v->size == v->max_size)
    {
        v->max_size += v->max_size/2;
    
        int *temp = v->arr;
        temp = (int *) realloc(v->arr, sizeof(int) * v->max_size);

        if (temp == NULL)
        {
            free(v->arr);
            assert(temp != NULL);
        }

        v->arr = temp;
    }
    
    v->arr[v->size] = val;
    v->size++;
}
void insert(vector *v, int val, int index)
{
    assert(index <= v->max_size && index > 0);

    if (v->size == v->max_size)
    {
        v->max_size += v->max_size/2;

        int *temp = v->arr;
        temp = (int *) realloc(v->arr, sizeof(int) * v->max_size);

        if (temp == NULL)
        {
            free(v->arr);
            assert(v->arr != NULL);
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
    assert(v->size > 0);
    
    int tmp = v->arr[v->size-1];
    v->size--;

    return tmp;
}
void erase(vector *v, int start, int end)
{
    assert(v->size > 0 && start < v->size && end > 0 && end < v->size && end >= start);

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
    assert(v->arr != NULL);
}
void vector_print(const vector *v)
{
    for (size_t i = 0; i < v->size; i++)
        printf("%d ", v->arr[i]);
    printf("\n");
}
void resize(vector *v, int size)
{
    assert(v->size > 0);

    if (size <= v->size)
        v->size = size;
    else
    {
        v->max_size = size;

        int *temp = v->arr;
        temp = (int *) realloc(v->arr, sizeof(int) * v->max_size);

        if (temp == NULL)
        {
            free(v->arr);
            assert(temp != NULL);
        }

        v->arr = temp;
        v->size = v->max_size;
    }
}
void resize_elem(vector *v, int size, int elem)
{
    assert(size > 0);
    
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
void vector_swap(vector *v1, vector *v2)
{    
    swap(&v1->size, &v2->size);
    swap(&v1->max_size, &v2->max_size);
    swap(v1->arr, v2->arr);
}

vector* vector_copy(vector *dest, const vector *src)
{
    free(dest->arr);
    dest->max_size = src->max_size;
    dest->size = src->size;

    dest->arr = (int *) malloc(sizeof(int) * dest->max_size);
    if (dest->arr == NULL)
    {
        printf("Error allocating memory\n");
        return;
    }
    
    for (size_t i = 0; i < dest->size; i++)
        dest->arr[i] = src->arr[i];
    
    return dest;
}
