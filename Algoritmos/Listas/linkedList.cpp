#include <iostream>
#include <string>
#include <memory>
using namespace std;

template <typename T>
class Node
{
    public:
        T item;
        shared_ptr<Node<T>> next;

        Node(T Item, shared_ptr<Node<T>> Next)
        {
            item = Item;
            next = nullptr;
        }
        Node(shared_ptr<Node<T>> Next)
        {
            next = nullptr;
        }
};

template <typename T>
class List
{
    private:
        int size;
        shared_ptr<Node<T>> head;
        shared_ptr<Node<T>> tail;
        shared_ptr<Node<T>> cursor;

    public:
        List()
        {
            size = 0;
            head = nullptr;
            tail = head;
            cursor = head;
        }

        // Returns
        int Size()
        {
            return size;
        }

        // Move
        void next()
        {
            if (cursor->next == nullptr)
                return;
            else
                cursor = cursor->next;
        }
        void prev()
        {
            shared_ptr<Node<T>> tmp = make_shared<Node<T>>(nullptr);
            tmp = cursor;

            cursor = head;
            while (cursor->next != tmp)
                next();
        }

        // Print
        void print()
        {
            cursor = head;
            for (int i = 0; i < size; i++)
            {
                cout << cursor->item << " ";
                next();
            }
            cout << '\n';
            cursor = head;
        }
        void print_at()
        {
            if (cursor != nullptr)
                cout << cursor->item;
        }

        // Insert
        void push_back(T item)
        {
            shared_ptr<Node<T>> New_Node = make_shared<Node<T>>(item, nullptr);
            
            if (head == nullptr)
                head = New_Node;
            else
                tail->next = New_Node;
                
            tail = New_Node;
            size++;
        }
        void push_front(T item)
        {
            shared_ptr<Node<T>> New_Node = make_shared<Node<T>>(item, nullptr);
            
            if (head == nullptr)
            {
                head = New_Node;
                tail = New_Node;
            }
            else
            {
                New_Node->next = head;
                head = New_Node;
            }

            size++;
        }

        // Remove
        T pop_back()
        {
            if (head == nullptr || tail == nullptr)
            {
                // Creates temporary Node pointer to return an error
                unique_ptr<Node<T>> temp = make_unique<Node<T>>(nullptr);
                return temp->item;
            }

            cursor = head;
            if (cursor->next != tail)
            {
                cursor = tail;
                prev();
            }

            T r_item = cursor->item;
            cursor->next = nullptr;
            cursor = head;
            size--;

            return r_item;
        }
        T pop_front()
        {
            if (head == nullptr)
            {
                // Creates temporary Node pointer to return an error
                unique_ptr<Node<T>> temp = make_unique<Node<T>>(nullptr);
                return temp->item;
            }
            
            cursor = head;
            T r_item = cursor->item;

            head = head->next;
            cursor = head;
            size--;

            if (head == nullptr)
                tail = head;

            return r_item;
        }

        void clear()
        {
            while (size > 0)
                pop_front();
        }
};

int main()
{
    List<int> l1;

    l1.push_back(1);
    l1.push_back(2);
    l1.push_back(3);
    
    l1.pop_front();
    l1.print();

    List<string> l2;

    l2.push_back("Ola");
    l2.push_back("Tudo");
    l2.push_back("Bem");
    
    l2.pop_front();
    l2.print();

    List<float> l3;

    l3.pop_back();
    l3.push_back(9.7);
    l3.push_back(2.1);
    
    l3.print();
    
    return 0;
}
