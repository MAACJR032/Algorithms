#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

struct hash
{
    bool empty;
    int val;
};
typedef struct hash hash;

struct hash_table
{
    int max_size;
    int size;
    hash *dict;
};
typedef struct hash_table hash_table;

hash_table* create_table()
{
    hash_table *h = (hash_table *) malloc(sizeof(hash_table));
    assert(h != NULL);

    h->max_size = 10;
    h->size = 0;

    h->dict = (hash *) malloc(sizeof(hash) * h->max_size);
    assert(h->dict != NULL);

    for (size_t i = 0; i < h->max_size; i++)
    {
        h->dict[i].empty = true;
        h->dict[i].val = 0;
    }
    
    return h;
}

void destroy_table(hash_table *h)
{
    free(h->dict);
    free(h);
}

void rehash(hash_table *h)
{
    h->max_size *= 2;

    hash *tmp = h->dict;
    h->dict = (hash *) realloc(h->dict, sizeof(hash) * h->max_size);
    
    if (h->dict == NULL)
    {
        free(tmp);
        destroy_table(h);
        exit(1);
    }

    for (size_t i = h->max_size/2; i < h->max_size; i++)
    {
        h->dict[i].empty = true;
        h->dict[i].val = 0;
    }
}

int hash_func(const hash_table *h, int key)
{
    int init_index = key - (h->max_size * (key / h->max_size));
    int index = init_index;

    if (h->dict[init_index].empty)
        return init_index;
    else
    {
        int i = 1;
        while (!h->dict[index].empty && i <= h->max_size) 
        {
            int tmp = (i*i + i) / 2; 
            index = (init_index + tmp) % h->max_size;
            i++;
        }

        if (i > h->max_size)
            return -1;
    }
    
    return index;
}

int size(const hash_table *h) { return h->size; }
int max_size(const hash_table *h) { return h->max_size; }

void insert(hash_table *h, int val, int key)
{
    if (size(h) >= 0.7 * h->max_size)
        rehash(h);
    
    int index = hash_func(h, key);
    if (index != -1)
    {
        h->dict[index].val = val; 
        h->dict[index].empty = false;
        h->size++;
    }
}

void clear(hash_table *h)
{
    for (size_t i = 0; i < h->max_size; i++)
        h->dict[i].empty = true;
    h->size = 0;
}

void print_table(const hash_table *h)
{
    for (size_t i = 0; i < h->max_size; i++)
    {
        if (!h->dict[i].empty)
            printf("%d ", h->dict[i].val);
        else
            printf("_ ");
    }
    printf("\n");
}

int main()
{
    hash_table *h = create_table();

    return 0;
}
