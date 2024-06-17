#include <iostream>
#include <stdexcept>

template <typename type>
struct Node
{
    type elem;
    Node *next;
    Node *prev;
};

template <typename type>
class Doubly_List
{
    private:
        size_t size;
        Node<type> *head;
        Node<type> *tail;

        void next(Node<type> *&n)
        {
            if (n != tail)
                n = n->next;
        }

    public:
        Doubly_List()
        {
            size = 0;

            head = new Node<type>;
            tail = new Node<type>;

            head->next = tail;
            head->prev = nullptr;

            tail->next = nullptr;
            tail->prev = head;
        }
        ~Doubly_List()
        {
            clear();
            delete head;
            delete tail;
        }

        int get_size() const { return size; }
        bool empty() const { return size == 0; }
        
        void push_back(type elem)
        {
            Node<type> *new_node = new Node<type>;

            new_node->elem = elem;

            new_node->next = tail;
            new_node->prev = tail->prev;
            tail->prev->next = new_node;
            tail->prev = new_node;

            size++;
        }
        void push_front(type elem)
        {
            Node<type> *new_node = new Node<type>;

            new_node->elem = elem;

            new_node->prev = head;
            new_node->next = head->next;
            head->next = new_node;
            new_node->next->prev = new_node;

            size++;
        }

        type pop_back()
        {
            if (size == 0)
                throw std::runtime_error("Cannot pop from an empty list.");
            
            Node<type> *temp = tail->prev;
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
            
            Node<type> *temp = head->next;
            type elem = temp->elem;

            head->next = head->next->next;
            head->next->prev = head;
            
            delete temp;
            size--;

            return elem;
        }
        void remove(type value)
        {
            for (Node<type> *i = begin(); i != end();)
            {
                if (i->elem == value)
                {
                    Node<type> *temp = i;
                    
                    i->prev->next = i->next;
                    i->next->prev = i->prev;

                    next(i);
                    delete temp;
                    size--;
                }
                else
                    next(i);
            }
        }
        void clear()
        {
            while (size > 0)
                pop_front();
        }

        void print_list()
        {
            Node<type> *curr = head->next;

            while (curr != tail)
            {
                std::cout << curr->elem << ' ';
                curr = curr->next;
            }
            std::cout << '\n';
        }

        Node<type> *begin() { return head->next; }
        Node<type> *end() { return tail; }
};

int main()
{   
    Doubly_List<int> l;

    l.push_front(10);
    l.push_front(11);
    l.push_front(12);
    l.push_back(13);

    l.print_list();

    std::cout << l.pop_back() << '\n';
    std::cout << l.pop_front() << '\n';
    
    l.print_list();
    l.clear();

    if (l.empty())
        std::cout << "empty\n";

    l.push_back(21);
    l.push_back(21);
    l.push_back(15);
    l.push_back(10);
    l.push_back(21);

    l.remove(21);
    l.print_list();

    return 0;
}