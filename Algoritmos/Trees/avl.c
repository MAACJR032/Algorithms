#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

struct node
{
    int val;
    int height;
    struct node *left;
    struct node *right;
};
typedef struct node node;

struct avl
{
    node *root;
    int size;
};
typedef struct avl avl;

// Return functions
int max(int n1, int n2)
{
    return n1 > n2 ? n1 : n2;
}

node *get_min(node *rt)
{
    if (rt->left == NULL)
        return rt;
    return get_min(rt->left);
}

node *delete_min(node *rt)
{
    if (rt->left == NULL)
        return rt->right;

    rt->left = delete_min(rt->left);
    return rt;
}

// Constructors
node* new_node(int val, node *left, node *right)
{
    node *n = (node *) malloc(sizeof(node));
    assert(n != NULL);

    n->val = val;
    n->left = left;
    n->right = right;
    n->height = -1;

    return n;
}

avl* create_tree()
{
    avl *t = (avl *) malloc(sizeof(avl));
    assert(t != NULL);

    t->root = NULL;
    t->size = 0;

    return t;
}

// Rotations
void update_height(node *rt)
{
    if (rt)
    {
        rt->height = 1;
        if (rt->left)
            rt->height += rt->left->height;
        if (rt->right)
            rt->height += rt->right->height;
    }
}

node *rightRotate(node *rt)
{
    node *l = rt->left;
    node *lr = l->right;

    l->right = rt;
    rt->left = lr;

    rt->height = 1 + max(rt->left ? rt->left->height : -1, rt->right ? rt->right->height : -1);

    l->height = 1 + max(l->left ? l->left->height : -1, l->right ? l->right->height : -1);
    
    update_height(rt);
    update_height(l);

    return l;
}

node *leftRotate(node *rt)
{
    node *r = rt->right;
    node *rl = r->left;

    r->left = rt;
    rt->right = rl;

    rt->height = 1 + max(rt->left ? rt->left->height : -1, rt->right ? rt->right->height : -1);

    r->height = 1 + max(r->left ? r->left->height : -1, r->right ? r->right->height : -1);

    update_height(rt);
    update_height(r);

    return r;
}

// Insertion
node* insert_help(node *rt, int val)
{
    if (rt == NULL)
        return new_node(val, NULL, NULL);
    
    if (rt->val > val)
        rt->left = insert_help(rt->left, val);
    else
        rt->right = insert_help(rt->right, val);
    
    rt->height = 1 + max(rt->left ? rt->left->height : -1, rt->right ? rt->right->height : -1);

    update_height(rt);

    int balance = (rt->left ? rt->left->height : -1) - (rt->right ? rt->right->height : -1);

    if ((balance < -1) && (val >= rt->right->val))
        return leftRotate(rt);
    if ((balance > 1) && (val < rt->left->val))
        return rightRotate(rt);
    if ((balance > 1) && (val >= rt->left->val))
    {
        rt->left = leftRotate(rt->left);
        return rightRotate(rt);
    }
    if ((balance < -1) && (val < rt->right->val))
    {
        rt->right = rightRotate(rt->right);
        return leftRotate(rt);
    }

    return rt;
}

void insert(avl *t, int val)
{
    t->root = insert_help(t->root, val);
    t->size++;
}

// Find
bool find_help(const node *rt, int val)
{
    if (rt == NULL)
        return false;
    if (rt->val > val)
        return find_help(rt->left, val);
    else if (rt->val == val)
        return true;
    
    return find_help(rt->right, val);
}

bool find(const avl *t, int val)
{
    return find_help(t->root, val);
}

// Remove
node *remove_help(node *rt, int val)
{
    if (rt == NULL)
        return NULL;

    if (rt->val > val)
        rt->left = remove_help(rt->left, val);
    else if (rt->val < val)
        rt->right = remove_help(rt->right, val);
    else
    {
        if (rt->left == NULL)
            return rt->right;
        else if (rt->right == NULL)
            return rt->left;
        else
        {
            node *temp = get_min(rt->right);
            rt->val = temp->val;
            rt->right = delete_min(rt->right);
        }
    }

    return rt;
}

void Remove(avl *t, int val)
{
    if (find_help(t->root, val))
    {
        t->root = remove_help(t->root, val);
        t->size--;
    }
}

// Traversies
void preorder(const node *rt)
{
    if (rt != NULL)
    {
        printf("%d ", rt->val);
        preorder(rt->left);
        preorder(rt->right);
    }
}
void inorder(const node *rt)
{
    if (rt != NULL)
    {
        inorder(rt->left);
        printf("%d ", rt->val);
        inorder(rt->right);
    }
}
void posorder(const node *rt)
{
    if (rt != NULL)
    {
        posorder(rt->left);
        posorder(rt->right);
        printf("%d ", rt->val);
    }
}

// Destructor
void posorder_destroy(node *rt)
{
    if (rt)
    {
        posorder_destroy(rt->left);
        posorder_destroy(rt->right);
        free(rt);
    }   
}

void destroy_avl(avl *t)
{
    posorder_destroy(t->root);
    free(t);
}

int main()
{
    avl *tree = create_tree();
    insert(tree, 10);
    insert(tree, 20);
    insert(tree, 30);
    insert(tree, 40);
    insert(tree, 50);
    insert(tree, 25);

    printf("Preorder traversal: ");
    preorder(tree->root);
    printf("\n");

    printf("Inorder traversal: ");
    inorder(tree->root);
    printf("\n");

    printf("Posorder traversal: ");
    posorder(tree->root);
    printf("\n");

    Remove(tree, 30);
    printf("After removing 30, inorder traversal: ");
    inorder(tree->root);
    printf("\n");

    destroy_avl(tree);
    return 0;
}