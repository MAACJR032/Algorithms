#include <iostream>
#include <memory>
using namespace std;

class Node
{
    public:
        int item;
        shared_ptr<Node> next;

        Node(int Item, shared_ptr<Node> Next)
        {
            item = Item;
            next = nullptr;
        }
};

class List
{
    private:
        int size;
        shared_ptr<Node> head;
        shared_ptr<Node> tail;
        shared_ptr<Node> cursor;

    public:
        List();

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
            shared_ptr<Node> tmp = make_shared<Node>(0, nullptr);
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
        void Append(int item)
        {
            shared_ptr<Node> New_Node = make_shared<Node>(item, nullptr);
            
            if (head == nullptr)
                head = New_Node;
            else
                tail->next = New_Node;
                
            tail = New_Node;
            size++;
        }
        void push_front(int item)
        {
            shared_ptr<Node> New_Node = make_shared<Node>(item, nullptr);
            
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
        int pop_back()
        {
            if (head == nullptr || tail == nullptr)
                return -1;

            cursor = head;
            if (cursor->next != tail)
            {
                cursor = tail;
                prev();
            }

            int r_item = cursor->item;
            cursor->next = nullptr;
            cursor = head;
            size--;

            return r_item;
        }
        int pop_front()
        {
            if (head == nullptr)
                return -1;
            
            cursor = head;
            int r_item = cursor->item;

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

List::List()
{
    size = 0;
    head = nullptr;
    tail = head;
    cursor = head;
}

int main()
{
    List l;
    l.Append(1);
    l.Append(2);
    l.Append(3);
    l.pop_front();
    l.print();   
    return 0;
}
