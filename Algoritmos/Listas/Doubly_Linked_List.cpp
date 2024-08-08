#include <iostream>
#include <stdexcept>

template <typename type>
class node
{
    public:
        type elem;
    
    private:
        node *next;
        node *prev;

    node(type elem, node *next, node *prev) : elem(elem), next(next), prev(prev) {}
};

template <typename type>
class list
{
    private:
        size_t size;
        node<type> *head;
        node<type> *tail;

        node<type> next(const node<type> n)
        {
            if (n != tail || n != nullptr)
                return n.next
        }

    public:
        list()
        {
            size = 0;

            head = new node<type>({}, nullptr, nullptr);
            tail = new node<type>({}, nullptr, nullptr);

            head->next = tail;
            head->prev = nullptr;

            tail->next = nullptr;
            tail->prev = head;
        }
        ~list()
        {
            clear();
            delete head;
            delete tail;
        }

        int get_size() const { return size; }
        bool empty() const { return size == 0; }
        
        void push_back(type elem)
        {
            node<type> *new_node = new node<type>(elem, tail, tail.prev);

            tail->prev->next = new_node;
            tail->prev = new_node;

            size++;
        }
        void push_front(type elem)
        {
            node<type> *new_node = new node<type>(elem, head->next, head);

            head->next = new_node;
            new_node->next->prev = new_node;

            size++;
        }
        void push_back_list(list *other)
        {
            while (!other->empty())
            {
                type elem = pop_node(other->begin());
                other->size--;
                push_back(elem)
            }
        }

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
        type pop_node(node<type> n)
        {
            if (n == head || n == tail)
                throw std::out_of_range("The node is out of range");

            n.prev->next = n.next;
            n.next->prev = n.prev;
        
            return n.elem
        }
        void remove(type value)
        {
            for (node<type> *i = begin(); i != end();)
            {
                if (i->elem == value)
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
        void clear()
        {
            while (size > 0)
                pop_front();
        }

        void print_list()
        {
            node<type> *curr = head->next;

            while (curr != tail)
            {
                std::cout << curr->elem << ' ';
                curr = curr->next;
            }
            std::cout << '\n';
        }

        node<type> *begin() { return head->next; }
        node<type> *end() { return tail; }
};
