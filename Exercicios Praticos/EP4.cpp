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

        void preorder(Node *rt)
        {
            if (rt != nullptr)
            {
                cout << rt->element << '\n';
                preorder(rt->left);
                preorder(rt->right);
            } 
        }
};

int main()
{
    int c;
    cin >> c;

    for (int i = 0; i < c; i++)
    {
        int n;
        cin >> n;

        int keys[n];
        BST AVL = BST();
        for (int j = 0; j < n; j++)
        {
            cin >> keys[j];         
            AVL.insert(keys[j]);
        }
        AVL.preorder(AVL.root);
        cout << "END\n";
    }
    
    return 0;
}