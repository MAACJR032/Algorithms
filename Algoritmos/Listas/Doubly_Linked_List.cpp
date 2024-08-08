/*
Implementation of a doubly linked list

iterating the list

for (node<type> *n = l.begin(); l != l.end(); n = n.next)
{
    // do something with n->elem
}

*/

#include <iostream>
#include <stdexcept>

struct node_list
{
    node_list *origin; 
};

template <typename type>
class node
{
    public:
        type elem;
        node_list *origin;
        node *next;
        node *prev;

        node(type elem, node *next, node *prev, node_list *origin) : elem(elem), next(next), prev(prev), origin(origin) {}      
};

template <typename type>
class list
{
    private:
        size_t size;
        node<type> *head;
        node<type> *tail;
        node_list *origin;

        // Returns the next node of n
        node<type>* next(const node<type> *n) const
        {
            if (n != tail || n != nullptr)
                return n->next;
            return nullptr;
        }

        // Returns the previous node of n
        node<type>* prev(const node<type> *n) const
        {
            if (n != head || n != nullptr)
                return n->prev;
            return nullptr;
        }

    public:
        list()
        {
            size = 0;

            origin = new node_list;
            head = new node<type>({}, nullptr, nullptr, origin);
            tail = new node<type>({}, nullptr, nullptr, origin);

            head->next = tail;
            head->prev = nullptr;

            tail->next = nullptr;
            tail->prev = head;
        }
        ~list()
        {
            clear();
            delete origin;
            delete head;
            delete tail;
        }

        // Returns the size of the list
        int get_size() const { return size; }

        // Returns true if the list is empty, and returns false if not
        bool empty() const { return size == 0; }

        // Returns true if the node is part of the list, and returns false if not
        bool in_list(const node<type> *n) const { return n->origin == origin; }

        // Returns the first element of the list
        node<type> *begin() { return head->next; }

        // Returns the tail (after the last element) of the list
        node<type> *end() { return tail; }

        // Insert elem to the end of the list
        void push_back(type elem)
        {
            node<type> *new_node = new node<type>(elem, tail, tail->prev, origin);

            tail->prev->next = new_node;
            tail->prev = new_node;

            size++;
        }

        // Insert elem to the begining of the list
        void push_front(type elem)
        {
            node<type> *new_node = new node<type>(elem, head->next, head, origin);

            head->next = new_node;
            new_node->next->prev = new_node;

            size++;
        }
        
        // Insert copies of the other list elements to the end of this list
        void push_back_list(list<type> &other)
        {
            if (other.empty())
                return;

            node<type> *n = other.begin();
            while (n != other.end())
            {
                push_back(n->elem);
                n = next(n);
            }
        }

        // Insert copies of the other list elements to the begining of this list
        void push_front_list(list &other)
        {
            node<type> *n = other.end()->prev;
            while (n != other.begin()->prev)
            {
                push_front(n->elem);
                n = prev(n);
            }
        }

        // Insert the elements of the other list elements to the end of this list
        // and empties the other list
        void push_back_transfer_list(list<type> &other)
        {
            if (other.empty())
                return;

            // Update the origin of the nodes being transferred
            node<type> *n = other.begin();
            while (n != other.end())
            {
                n->origin = origin;
                n = n->next;
            }

            tail->prev->next = other.head->next;
            other.head->next->prev = tail->prev;

            tail->prev = other.tail->prev;
            other.tail->prev->next = tail;

            size += other.size;
            
            // Clear other list
            other.head->next = other.tail;
            other.tail->prev = other.head;
            other.size = 0;        
        }

        // Insert the elements of the other list elements to the begining of this list
        // and empties the other list
        void push_front_transfer_list(list<type> &other)
        {
            if (other.empty())
                return;
            
            // Update the origin of the nodes being transferred
            node<type> *n = other.begin();
            while (n != other.end())
            {
                n->origin = origin;
                n = n->next;
            }

            head->next->prev = other.tail->prev;
            other.tail->prev->next = head->next;

            head->next = other.head->next;
            other.head->next->prev = head;

            size += other.size;
            
            // Clear other list
            other.head->next = other.tail;
            other.tail->prev = other.head;
            other.size = 0;        
        }


        // Removes the last element
        type pop_back()
        {
            if (size == 0)
                throw std::runtime_error("Cannot pop from an empty list.");
            
            node<type> *temp = tail->prev;
            type elem = temp->elem;

            tail->prev = tail->prev->prev;
            tail->prev->next = tail;
            
            delete temp;
            size--;

            return elem;
        }

        // Removes the first element
        type pop_front()
        {
            if (size == 0)
                throw std::runtime_error("Cannot pop from an empty list.");
            
            node<type> *temp = head->next;
            type elem = temp->elem;

            head->next = head->next->next;
            head->next->prev = head;
            
            delete temp;
            size--;

            return elem;
        }

        // Removes the node n if it belongs to this list 
        type pop_node(node<type> *n)
        {
            if (n == head || n == tail)
                throw std::out_of_range("The node is out of range");
            else if (!in_list(n))
                throw std::out_of_range("The node does not belong to this list");
            
            n->prev->next = n->next;
            n->next->prev = n->prev;
        
            return n->elem;
        }

        // Removes all the occurences of elem
        void remove(type elem)
        {
            for (node<type> *i = begin(); i != end();)
            {
                if (i->elem == elem)
                {
                    node<type> *temp = i;
                    
                    i->prev->next = i->next;
                    i->next->prev = i->prev;

                    i = next(i);
                    delete temp;
                    size--;
                }
                else
                    i = next(i);
            }
        }

        // Removes all the elements
        void clear()
        {
            while (size > 0)
                pop_front();
        }


        void print_list()
        {
            node<type> *curr = begin();
            
            while (curr != end())
            {
                std::cout << curr->elem << ' ';
                curr = curr->next;
            }
            std::cout << '\n';
        }
};
