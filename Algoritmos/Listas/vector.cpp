#include <iostream>

template <typename type>
class vector
{
    private:
        type *arr;
        size_t size_, max_size;

        void reallocate()
        {
            type *new_arr = new type[max_size];
                
            for (size_t i = 0; i < size_; i++)
                new_arr[i] = arr[i];
            
            type *tmp = arr;
            arr = new_arr;
            delete[] tmp;
        }

    public:
        vector()
        {
            size_ = 0;
            max_size = 10;
            arr = new type[max_size];
        }
        vector(int size)
        {
            if (size < 0)
                throw std::bad_alloc();
            
            size_ = 0;
            max_size = size;
            arr = new type[max_size];
        }
        vector(int size, type elem)
        {
            if (size < 0)
                throw std::bad_alloc();
            
            size_ = 0;
            max_size = size;
            arr = new type[max_size];

            for (size_t i = 0; i < max_size; i++)
                arr[i] = elem;
        }
        vector(vector &v)
        {
            size_ = v.size_;
            max_size = v.max_size;
            arr = new type[max_size];

            for (size_t i = 0; i < size_; i++)
                arr[i] = v.arr[i];
        }
        ~vector()
        {
            delete[] arr;
        }


        // Operators:
        /* access to the data contained in the vector and allows modification */
        type& operator[] (const int index)
        {
            if (index < 0 || index >= size_)
                throw std::out_of_range("Index out of range");
            return arr[index];
        }
        
        /* Access the data contained in the vector but is read only */
        const type& operator[] (const int index) const
        {
            if (index < 0 || index >= size_)
                throw std::out_of_range("Index out of range");
            return arr[index];
        }

        /* Copies the other to this vector */
        vector& operator= (const vector &other)
        {
            if (this == &other)
                return *this;
            
            delete[] arr;

            size_ = other.size_;
            max_size = other.max_size;
            
            arr = new type[max_size];
            for (size_t i = 0; i < size_; i++)
                arr[i] = other.arr[i];
            
            return *this;
        }


        // Insertion operations:
        /* Creates an element at the end of the vector and assigns the given data to it. This operation can be done in constant time if the vector has preallocated space available. */
        void push_back(type elem)
        {
            if (size_ == max_size)
            {
                max_size *= 2;
                reallocate();
            }

            arr[size_] = elem;
            size_++;
        }

        /* Creates an element at the begining of the vector and assigns the given data to it. This operation is done in linear time, according to the vector's size */
        void push_front(type elem)
        {
            if (size_ == max_size)
            {
                max_size *= 2;
                reallocate();
            }

            if (size_ > 0)
            {
                for (size_t i = size_; i > 0; i--)
                    arr[i] = arr[i-1];
            }
            
            arr[0] = elem;
            size_++;
        }

        /* Inserts element before specified index */
        void insert(type elem, int index)
        {
            if (index > size_ || index < 0)
                throw std::out_of_range("index out of range");
            
            if (size_ == max_size)
            {
                max_size *= 2;
                reallocate();
            }

            for (int i = size_; i > index; i--)
                arr[i] = arr[i-1];

            arr[index] = elem;
            size_++;
        }


        // Remove operations:
        /* Removes the last element */
        type pop_back()
        {
            if (size_ == 0)
                throw std::out_of_range("Vector is empty");

            type tmp = arr[size_-1];
            size_--;
            
            return tmp;
        }

        /* Removes the first element */
        type pop_front()
        {
            if (size_ == 0)
                throw std::out_of_range("Vector is empty");
            
            type tmp = arr[0];
            for (size_t i = 0; i < size_ - 1; i++)
                arr[i] = arr[i+1];

            size_--;
            return tmp;
        }

        /* Erases all elements from start (inclusive) until end (exclusive) */
        void erase(int start, int end)
        {
            if (start < 0 || start > size_ || end < 0 || end > size_ || start > end)
                throw std::out_of_range("index out of range");
            
            if (end == size_)
            {
                size_ = start;
                return;
            }
            
            for (size_t i = start, j = end; i < size_; i++, j++)
                arr[i] = arr[j];

            size_ -= end - start;
        }


        // Non-return function:
        /* Prints all the vector elements */
        void print_vector() const
        {
            for (size_t i = 0; i < size_; i++)
                std::cout << arr[i] << ' ';
            std::cout << '\n';
        }

        /* Erases all the elements. Note that if the elements themselves are pointers, the
           pointed-to memory is not touched in any way. Managing the pointer is
           the user's responsibility */
        void clear()
        {
            delete[] arr;
            size_ = 0;
            max_size = 10;
            arr = new type[max_size];
        }

        /* Resizes the vector to the specified number of elements. If the number is smaller than the vector's current size the vector is truncated, otherwise default constructed elements are appended. */
        void resize(int size)
        {
            if (size < 0)
                throw std::bad_alloc();
                     
            if (size <= size_)
                size_ = size;
            else
            {
                max_size = size;
                reallocate();
                size_ = max_size;
            }
        }

        /* Resizes the vector to the size specified and assigns every index to the element specified */
        void resize(int size, type elem)
        {
            if (size < 0)
                throw std::bad_alloc();
            
            delete[] arr;
            
            size_ = size;
            max_size = size;
            arr = new type[max_size];

            for (size_t i = 0; i < max_size; i++)
                arr[i] = elem;
        }

        /* Swap the vectors */
        void swap(vector<type> &v)
        {
            size_t tmp2 = size_;
            size_ = v.size_;
            v.size_ = tmp2;

            tmp2 = max_size;
            max_size = v.max_size;
            v.max_size = tmp2;

            type *tmp1 = arr;
            arr = v.arr;
            v.arr = tmp1;
        }


        // Returns funtions:
        /* Returns the maximum capacity the vector can have before allocating more */
        int capacity() const
        {
            return max_size;
        }

        /* Returns how many elements the vector has */
        int size() const
        {
            return size_;
        }

        /* Returns true if the vector is empty */
        bool empty() const
        {
            return (size_ == 0);
        }
};

int main()
{
    vector<int> v1;

    for (size_t i = 0; i < 5; i++)
        v1.push_back(i);
    v1.print_vector();

    v1.erase(0, 2);
    v1.print_vector();
    
    v1[0] = 0;
    v1.insert(5, 2);
    v1.print_vector();

    v1.resize(10, 0);
    v1.print_vector();

    vector<int> v2;
    for (size_t i = 0; i < 5; i++)
        v2.push_back(i);

    v1 = v2;
    v1.print_vector();
    v2.print_vector();

    v1.clear();
    v1.push_front(15);
    v1.push_front(16);
    v1.print_vector();

    v1.swap(v2);
    v1.print_vector();
    v2.print_vector();

    v1.pop_back();
    v1.pop_front();
    v1.print_vector();

    return 0;
}