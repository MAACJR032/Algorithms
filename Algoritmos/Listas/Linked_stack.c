#include "DoublyLinked.h"

struct stack
{
    list *l;
};
typedef struct stack stack;

void push(stack *s, int val)
{
    push_back(s->l, val);   
}

int pop(stack *s)
{
    pop_back(s->l);
}

int stack_size(const stack *s)
{
    return size(s->l);
}

void destroy_stack(stack *s)
{
    destroy_list(s->l);
    free(s);
}
