/*
Implementation of a doubly linked list

iterating the list

for (node<type> *n = l.begin(); n != l.end(); n = n->next())
{
    ...
}

*/

#include <iostream>
#include <memory>
#include <stdexcept>

template <typename type>
class list;

template <typename type>
class node
{
    private:
        node<type> *next_node;
        node<type> *prev_node;
        list<type> *origin;
    
        friend class list<type>;

    public:
        type elem;

        node(type elem, node *next, node *prev, list<type> *origin) : elem(elem), next_node(next), prev_node(prev), origin(origin) {}

        // Returns the next node of n
        node<type>* next() const
        {
            if (this == origin->tail)
                throw std::out_of_range("the node is out of the list range");

            return next_node;
        }

        // Returns the previous node of n
        node<type>* prev() const
        {
            if (this == origin->head)
                throw std::out_of_range("the node is out of the list range");

            return prev_node;
        }
};

template <typename type>
class list
{
    private:
        size_t size;
        node<type> *head;
        node<type> *tail;

        friend class node<type>;

    public:
        list()
        {
            size = 0;

            head = new node<type>({}, nullptr, nullptr, this);
            tail = new node<type>({}, nullptr, nullptr, this);

            head->next_node = tail;
            head->prev_node = nullptr;

            tail->next_node = nullptr;
            tail->prev_node = head;
        }
        list(const list<type> &other)
        {
            size = 0;

            head = new node<type>({}, nullptr, nullptr, this);
            tail = new node<type>({}, nullptr, nullptr, this);

            head->next_node = tail;
            head->prev_node = nullptr;

            tail->next_node = nullptr;
            tail->prev_node = head;

            push_back_list(other);
        }
        ~list()
        {
            clear();
            delete head;
            delete tail;
        }

        // Returns the size of the list
        int get_size() const { return size; }

        // Returns true if the list is empty, and returns false if not
        bool empty() const { return size == 0; }

        // Returns true if the node is part of the list, and returns false if not
        bool in_list(const node<type> *n) const { return n->origin == this; }

        // Returns the first element of the list
        node<type> *begin() const { return head->next_node; }

        // Returns the tail (after the last element) of the list
        node<type> *end() const { return tail; }

        // Insert elem to the end of the list
        void push_back(type elem)
        {
            node<type> *new_node = new node<type>(elem, tail, tail->prev_node, this);

            tail->prev_node->next_node = new_node;
            tail->prev_node = new_node;

            size++;
        }

        // Insert elem to the begining of the list
        void push_front(type elem)
        {
            node<type> *new_node = new node<type>(elem, head->next_node, head, this);

            head->next_node = new_node;
            new_node->next_node->prev_node = new_node;

            size++;
        }

        // inserts the node to the end of the list
        // the node must not be part of any list, including this
        void push_back_node(node<type> *n)
        {
            if (n == nullptr || n == head || n == tail || n->origin != nullptr)
                throw std::invalid_argument("invalid node passed as argument to push_back_node()");
            
            n->origin = this;

            tail->prev_node->next_node = n;
            tail->prev_node = n;

            size++;
        }

        // inserts the node to the begining of the list
        // the node must not be part of any list, including this
        void push_front_node(node<type> *n)
        {
            if (n == nullptr || n == head || n == tail || n->origin != nullptr)
                throw std::invalid_argument("invalid node passed as argument to push_back_node()");
            
            n->origin = this;

            head->next_node = n;
            n->next_node->prev_node = n;

            size++;
        }
        
        // Insert copies of the other list elements to the end of this list
        void push_back_list(const list<type> &other)
        {
            if (other.empty())
                return;

            node<type> *n = other.begin();
            while (n != other.end())
            {
                push_back(n->elem);
                n = n->next();
            }
        }

        // Insert copies of the other list elements to the begining of this list
        void push_front_list(const list &other)
        {
            if (other.empty())
                return;
            
            node<type> *n = other.end()->prev_node;
            while (n != other.begin()->prev_node)
            {
                push_front(n->elem);
                n = n->prev();
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
                n->origin = this;
                n = n->next_node;
            }

            tail->prev_node->next_node = other.head->next_node;
            other.head->next_node->prev_node = tail->prev_node;

            tail->prev_node = other.tail->prev_node;
            other.tail->prev_node->next_node = tail;

            size += other.size;
            
            // Clear other list
            other.head->next_node = other.tail;
            other.tail->prev_node = other.head;
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
                n->origin = this;
                n = n->next_node;
            }

            head->next_node->prev_node = other.tail->prev_node;
            other.tail->prev_node->next_node = head->next_node;

            head->next_node = other.head->next_node;
            other.head->next_node->prev_node = head;

            size += other.size;
            
            // Clear other list
            other.head->next_node = other.tail;
            other.tail->prev_node = other.head;
            other.size = 0;        
        }


        // Removes the last element
        type pop_back()
        {
            if (size == 0)
                throw std::runtime_error("Cannot pop from an empty list.");
            
            node<type> *temp = tail->prev_node;
            type elem = temp->elem;

            tail->prev_node = tail->prev_node->prev_node;
            tail->prev_node->next_node = tail;
            size--;
            
            delete temp;
            return elem;
        }

        // Removes the first element
        type pop_front()
        {
            if (size == 0)
                throw std::runtime_error("Cannot pop from an empty list.");
            
            node<type> *temp = head->next_node;
            type elem = temp->elem;

            head->next_node = head->next_node->next_node;
            head->next_node->prev_node = head;
            size--;
            
            delete temp;
            return elem;
        }

        // Removes the node n if it belongs to this list 
        node<type> pop_node(node<type> *n)
        {
            if (n == nullptr)
                throw std::invalid_argument("nullptr passed as argument to pop_node()");
            else if (n == head || n == tail)
                throw std::out_of_range("The node is out of range");
            else if (!in_list(n))
                throw std::invalid_argument("The node does not belong to this list");
            
            n->prev_node->next_node = n->next_node;
            n->next_node->prev_node = n->prev_node;
            n->origin = nullptr;
            size--;
            
            return n;
        }

        // Removes all the occurences of elem
        void remove(type elem)
        {
            for (node<type> *i = begin(); i != end();)
            {
                if (i->elem == elem)
                {
                    node<type> *temp = i;
                    
                    i->prev_node->next_node = i->next_node;
                    i->next_node->prev_node = i->prev_node;

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
            {
                pop_front();
            }
        }


        void print_list() const
        {
            node<type> *curr = begin();
            
            while (curr != end())
            {
                std::cout << curr->elem << ' ';
                curr = curr->next_node;
            }
            std::cout << '\n';
        }
};
