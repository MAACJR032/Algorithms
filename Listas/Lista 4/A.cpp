#include <iostream>
using namespace std;

class Node 
{
    public:
        int element, height, size;
        Node *left, *right;

        Node(int Element)
        {
            element = Element;
            left = right = nullptr;
            height = 0;
            size = 1;
        }
};

class BST 
{
    private:
        Node *rightRotate(Node *rt)
        {
            Node *l = rt->left;
            Node *lr = l->right;

            l->right = rt;
            rt->left = lr;
           
            rt->height = 1 + max(((rt->left != nullptr) ? rt->left->height : -1), ((rt->right != nullptr) ? rt->right->height : -1));
            l->height = 1 + max(((l->left != nullptr) ? l->left->height : -1), ((l->right != nullptr) ? l->right->height : -1));
            
            update_size(rt);
            update_size(l);

            return l;
        }

        Node *leftRotate(Node *rt)
        {
            Node *r = rt->right;
            Node *rl = r->left;

            r->left = rt;
            rt->right = rl;

            rt->height = 1 + max(((rt->left != nullptr)? rt->left->height : -1), ((rt->right != nullptr) ?rt->right->height : -1));
            r->height = 1 + max(((r->left != nullptr)? r->left->height : -1), ((r->right != nullptr)? r->right->height : -1));

            update_size(rt);
            update_size(r);

            return r;
        }

        Node *inserthelp(Node *rt, int element)
        {
            if (rt == nullptr)
                return new Node(element);
            if (rt->element > element)
                rt->left = inserthelp(rt->left, element);
            else
                rt->right = inserthelp(rt->right, element);
            
            rt->height = 1 + max(((rt->left != nullptr) ? rt->left->height : -1), ((rt->right != nullptr) ? rt->right->height : -1));

            update_size(rt);

            int balance = ((rt->left != nullptr) ? rt->left->height : -1) - ((rt->right != nullptr) ? rt->right->height : -1);

            if (balance < -1 && element >= rt->right->element)
                return leftRotate(rt);
            else if (balance > 1 && element < rt->left->element)
                return rightRotate(rt);
            else if (balance > 1 && element >= rt->left->element)
            {
                rt->left = leftRotate(rt->left);
                return rightRotate(rt);
            }
            else if (balance < -1 && element < rt->right->element)
            {
                rt->right = rightRotate(rt->right);
                return leftRotate(rt);
            }

            return rt;
        }

        void update_size(Node *rt)
        {
            if (rt != nullptr)
            {
                rt->size = 1;
                if (rt->left != nullptr)
                    rt->size += rt->left->size;
                if (rt->right != nullptr)
                    rt->size += rt->right->size;
            }
        }

    public:
        Node *root;
        
        BST()
        {
            root = nullptr;
        }

        void insert(int element)
        {
            root = inserthelp(root, element);
        }

        int Find(Node *rt, int index, int element, int *found)
        {
            while ((rt != nullptr) && ((*found) == 0))
            {
                if (element == rt->element)
                {
                    (*found) = 1;
                    if (rt->left != nullptr)
                        index += (rt->left->size + 1);
                    else
                        index++;
                    
                    return index;
                }
                else if (element > rt->element)
                {
                    if (rt->left != nullptr)
                        index += (rt->left->size + 1);
                    else
                        index++;

                    rt = rt->right;
                }
                else
                    rt = rt->left;
            }
            return -1;
        }
};

int main() 
{
    BST bst = BST();
    int Q;
    cin >> Q;

    for (int i = 0; i < Q; i++)
    {
        int op, x;
        cin >> op;
        cin >> x;

        if (op == 1)
            bst.insert(x);
        else if (op == 2)
        {
            int index = 0, found = 0;
            index = bst.Find(bst.root, index, x, &found);
            if (found == 0)
                cout << "Data tidak ada\n";
            else
                cout << index << '\n';
        }
    }
    
    return 0;
}