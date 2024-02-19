#include <iostream>
using namespace std;

class Node
{
    public:
        int element;
        Node *left;
        Node *right;
        Node(int Element)
        {
            element = Element;
            left = right = nullptr;
        }
};

class BST
{
    private:
        int findhelp(Node *rt, int element)
        {
            if (rt == nullptr)
                return -1;
            if (rt->element > element)
                return findhelp(rt->left, element);
            else if (rt->element == element)
                return rt->element;
            else
                return findhelp(rt->right, element);
        }
        Node *inserthelp(Node *rt, int element)
        {
            if (rt == nullptr)
                return new Node(element);
            
            if (rt->element > element)
                rt->left = inserthelp(rt->left, element);
            else
                rt->right = inserthelp(rt->right, element);
            
            return rt;
        }
        Node *removehelp(Node *rt, int element)
        {
            if (rt == nullptr)
                return nullptr;

            if (rt->element > element)
                rt->left = removehelp(rt->left, element);
            else if (rt->element < element)
                rt->right = removehelp(rt->right, element);
            else
            {
                if (rt->left == nullptr)
                    return rt->left;
                else if (rt->right == nullptr)
                    return rt->left;
                else
                {
                    Node *temp = getmin(rt->right);
                    rt->element = temp->element;
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

        void insert(int element)
        {
            root = inserthelp(root, element);
            count++;
        }
        
        Node *getmin(Node *rt)
        {
            if (rt->left == nullptr)
                return getmin(rt->left);
        }
        Node *deletemin(Node *rt)
        {
            if (rt->left == nullptr)
                return rt->right;

            rt->left = deletemin(rt->left);
            return rt;
        }

        int Remove(int element)
        {
            int temp = findhelp(root, element);
            if (temp != -1)
            {
                root = removehelp(root, element);
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
        int p;
        cin >> p;

        bst.insert(p);
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