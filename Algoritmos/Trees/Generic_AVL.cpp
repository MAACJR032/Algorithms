#include <iostream>
using namespace std;

template <typename T>
class Node
{
    public:
        T element;
        int height;
        Node<T> *left;
        Node<T> *right;

        Node(T elem)
        {
            element = elem;
            height = 0;
            left = right = nullptr;
        }
};

template <typename T>
class BST
{
    private:
        bool findhelp(const Node<T> *rt, T element) const
        {
            if (rt == nullptr)
                return false;
            if (rt->element > element)
                return findhelp(rt->left, element);
            else if (rt->element == element)
                return true;
            else
                return findhelp(rt->right, element);
        }

        Node<T> *rightRotate(Node<T> *rt)
        {
            Node<T> *l = rt->left;
            Node<T> *lr = l->right;

            l->right = rt;
            rt->left = lr;

            rt->height = 1 + max(h(rt->left), h(rt->right));
            l->height = 1 + max(h(l->left), h(l->right));

            return l;
        }
        Node<T> *leftRotate(Node<T> *rt)
        {
            Node<T> *r = rt->right;
            Node<T> *rl = r->left;

            r->left = rt;
            rt->right = rl;
            rt->height = 1 + max(h(rt->left), h(rt->right));
            r->height = 1 + max(h(r->left), h(r->right));

            return r;
        }

        Node<T> *inserthelp(Node<T> *rt, T element)
        {
            if (rt == nullptr)
                return new Node<T>(element);
            
            if (rt->element > element)
                rt->left = inserthelp(rt->left, element);
            else
                rt->right = inserthelp(rt->right, element);
            
            rt->height = 1 + max(h(rt->left), h(rt->right));
            int balance = getBalance(rt);

            if ((balance < -1) && (element >= rt->right->element))
                return leftRotate(rt);
            if ((balance > 1) && (element < rt->left->element))
                return rightRotate(rt);
            if ((balance > 1) && (element >= rt->left->element))
            {
                rt->left = leftRotate(rt->left);
                return rightRotate(rt);
            }
            if ((balance < -1) && (element < rt->right->element))
            {
                rt->right = leftRotate(rt->right);
                return leftRotate(rt);
            }

            return rt;
        }

        int h(const Node<T> *rt) const
        {
            if (rt == nullptr)
                return -1;
                
            return 1 + max(h(rt->left), h(rt->right));
        }
        int getBalance(const Node<T> *rt) const
        {
            if (rt == nullptr)
                return 0;
            return (h(rt->left) - h(rt->right));
        }
        Node<T> *getmin(Node<T> *rt)
        {
            if (rt->left == nullptr)
                return rt;
            return getmin(rt->left);
        }
        Node<T> *deletemin(Node<T> *rt)
        {
            if (rt->left == nullptr)
                return rt->right;

            rt->left = deletemin(rt->left);
            return rt;
        }

        Node<T> *removehelp(Node<T> *rt, int element)
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
                    return rt->right;
                else if (rt->right == nullptr)
                    return rt->left;
                else
                {
                    Node<T> *temp = getmin(rt->right);
                    rt->element = temp->element;
                    rt->right = deletemin(rt->right);
                }
            }
            return rt;
        }

    public:
        Node<T> *root;
        int count;

        BST()
        {
            root = nullptr;
            count = 0;
        }

        bool find(T element) const
        {
            return findhelp(root, element);
        }

        void insert(T element)
        {
            root = inserthelp(root, element);
            count++;
        }

        T Remove(T element)
        {
            if (findhelp(root, element))
            {
                root = removehelp(root, element);
                count--;
            }
            
            return temp;
        }

        void preorder(const Node<T> *rt) const
        {
            if (rt != nullptr)
            {
                cout << ' ' << rt->element;
                preorder(rt->left);
                preorder(rt->right);
            }
        }
        void inorder(const Node<T> *rt) const
        {
            if (rt != nullptr)
            {
                inorder(rt->left);
                cout << ' ' << rt->element;
                inorder(rt->right);
            }
        }
        void posorder(const Node<T> *rt) const
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
    BST<int> bst;
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int num;
        cin >> num;

        bst.insert(num);
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
