#include <iostream>
using namespace std;

class Node
{
    public:
        int element;
        int key;
        int height;
        Node *left;
        Node *right;

        Node(int Element, int Key)
        {
            key = key;
            element = Element;
            left = right = nullptr;
            height = 0;
        }
};

class BST
{
    private:
        int findhelp(Node *rt, int key)
        {
            if (rt == nullptr)
                return -1;
            if (rt->key > key)
                return findhelp(rt->left, key);
            else if (rt->key == key)
                return rt->element;
            else
                return findhelp(rt->right, key);
        }

        Node *rightRotate(Node *rt)
        {
            Node *l = rt->left;
            Node *lr = l->right;

            l->right = rt;
            rt->left = lr;

            rt->height = 1 + max(h(rt->left), h(rt->right));
            l->height = 1 + max(h(l->left), h(l->right));

            return l;
        }
        Node *leftRotate(Node *rt)
        {
            Node *r = rt->right;
            Node *rl = r->left;

            r->left = rt;
            rt->right = rl;
            rt->height = 1 + max(h(rt->left), h(rt->right));
            r->height = 1 + max(h(r->left), h(r->right));

            return r;
        }

        Node *inserthelp(Node *rt, int element, int key)
        {
            if (rt == nullptr)
                return new Node(element, key);
            
            if (rt->key > key)
                rt->left = inserthelp(rt->left, element, key);
            else
                rt->right = inserthelp(rt->right, element, key);
            
            rt->height = 1 + max(h(rt->left), h(rt->right));
            int balance = getBalance(rt);

            if ((balance < -1) && (key >= rt->right->key))
                return leftRotate(rt);
            if ((balance > 1) && (key < rt->left->key))
                return rightRotate(rt);
            if ((balance > 1) && (key >= rt->left->key))
            {
                rt->left = leftRotate(rt->left);
                return rightRotate(rt);
            }
            if ((balance < -1) && (key < rt->right->key))
            {
                rt->right = rightRotate(rt->right);
                return leftRotate(rt);
            }

            return rt;
        }

        int h(Node *rt)
        {
            if (rt == nullptr)
                return -1;
                
            return max(h(rt->left), h(rt->right)) + 1;
        }
        int getBalance(Node *rt)
        {
            if (rt == nullptr)
                return 0;
            return (h(rt->left) - h(rt->right));
        }
        Node *getmin(Node *rt)
        {
            if (rt->left == nullptr)
                return rt;
            return getmin(rt->left);
        }
        Node *deletemin(Node *rt)
        {
            if (rt->left == nullptr)
                return rt->right;

            rt->left = deletemin(rt->left);
            return rt;
        }

        Node *removehelp(Node *rt, int key)
        {
            if (rt == nullptr)
                return nullptr;

            if (rt->key > key)
                rt->left = removehelp(rt->left, key);
            else if (rt->key < key)
                rt->right = removehelp(rt->right, key);
            else
            {
                if (rt->left == nullptr)
                    return rt->right;
                else if (rt->right == nullptr)
                    return rt->left;
                else
                {
                    Node *temp = getmin(rt->right);
                    rt->element = temp->element;
                    rt->key = temp->key;
                    rt->right = deletemin(rt->right);
                }
            }
            return rt;
        }

    public:
        Node *root;
        int count;
        BST()
        {
            root = nullptr;
            count = 0;
        }

        int find(int element)
        {
            return findhelp(root, element);
        }

        void insert(int element,int key)
        {
            root = inserthelp(root, element, key);
            count++;
        }

        int Remove(int key)
        {
            int temp = findhelp(root, key);
            if (temp != -1)
            {
                root = removehelp(root, key);
                count--;
            }
            
            return temp;
        }

        void preorder(Node *rt)
        {
            if (rt != nullptr)
            {
                cout << ' ' << rt->element;
                preorder(rt->left);
                preorder(rt->right);
            }
        }
        void inorder(Node *rt)
        {
            if (rt != nullptr)
            {
                inorder(rt->left);
                cout << ' ' << rt->element;
                inorder(rt->right);
            }
        }
        void posorder(Node *rt)
        {
            if (rt != nullptr)
            {
                posorder(rt->left);
                posorder(rt->right);
                cout << ' ' << rt->element;
            }
        }
};

int main()
{
    BST bst = BST();
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int num, k;
        cin >> num;
        cin >> k;

        bst.insert(num, k);
    }

    cout << "Pre order : ";
    bst.preorder(bst.root);
    cout << '\n';

    cout << "In order  : ";
    bst.inorder(bst.root);
    cout << '\n';
    
    cout << "Post order: ";
    bst.posorder(bst.root);
    cout << '\n';

    return 0;
}