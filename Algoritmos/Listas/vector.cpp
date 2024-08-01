#include <iostream>

template <typename type>
class vector
{
    private:
        type *m_arr;
        size_t m_size, m_max_size;

        void reallocate()
        {
            type *new_arr = new type[m_max_size];
                
            for (size_t i = 0; i < m_size; i++)
                new_arr[i] = m_arr[i];
            
            type *tmp = m_arr;
            m_arr = new_arr;
            delete[] tmp;
        }

    public:
        vector()
        {
            m_size = 0;
            m_max_size = 10;
            m_arr = new type[m_max_size];
        }
        vector(size_t size)
        {
            m_size = 0;
            m_max_size = size;
            m_arr = new type[m_max_size];
        }
        vector(size_t size, type elem)
        {
            m_size = 0;
            m_max_size = size;
            m_arr = new type[m_max_size];

            for (size_t i = 0; i < m_max_size; i++)
                m_arr[i] = elem;
        }
        vector(vector &v)
        {
            m_size = v.m_size;
            m_max_size = v.m_max_size;
            m_arr = new type[m_max_size];

            for (size_t i = 0; i < m_size; i++)
                m_arr[i] = v.m_arr[i];
        }
        ~vector()
        {
            delete[] m_arr;
        }


        // Operators:
        /* access to the data contained in the vector and allows modification */
        type& operator[] (const size_t index)
        {
            if (index >= m_size)
                throw std::out_of_range("Index out of range");
            return m_arr[index];
        }
        
        /* Access the data contained in the vector but is read only */
        const type& operator[] (const size_t index) const
        {
            if (index >= m_size)
                throw std::out_of_range("Index out of range");
            return m_arr[index];
        }

        /* Copies the other to this vector */
        vector& operator= (const vector &other)
        {
            if (this == &other)
                return *this;
            
            delete[] m_arr;

            m_size = other.m_size;
            m_max_size = other.m_max_size;
            
            m_arr = new type[m_max_size];
            for (size_t i = 0; i < m_size; i++)
                m_arr[i] = other.m_arr[i];
            
            return *this;
        }


        // Insertion operations:
        /* Creates an element at the end of the vector and assigns the given data to it. This operation can be done in constant time if the vector has preallocated space available. */
        void push_back(type elem)
        {
            if (m_size == m_max_size)
            {
                m_max_size *= 2;
                reallocate();
            }

            m_arr[m_size] = elem;
            m_size++;
        }

        /* inserts all the elements of the parameter vector to the end of this vector */
        void push_back(const vector<type> &v)
        {
            size_t dif = m_size + v.size();
            if (dif > m_max_size)
            {
                m_max_size = dif * 1.5;
                reallocate(); 
            }
            
            for (size_t i = m_size, j = 0; i < dif; i++, j++)
                m_arr[i] = v.m_arr[j];

            m_size += v.m_size;
        }

        /* Creates an element at the begining of the vector and assigns the given data to it. This operation is done in linear time, according to the vector's size */
        void push_front(type elem)
        {
            if (m_size == m_max_size)
            {
                m_max_size *= 2;
                reallocate();
            }

            if (m_size > 0)
            {
                for (size_t i = m_size; i > 0; i--)
                    m_arr[i] = m_arr[i-1];
            }
            
            m_arr[0] = elem;
            m_size++;
        }

        /* inserts all the elements of the parameter vector in order in the begining of this vector */
        void push_front(const vector<type> &v)
        {
            int dif = m_size + v.m_size;

            vector<type> temp = *this;
            
            delete[] m_arr;
            m_arr = new int[dif];
            
            for (size_t i = 0; i < v.m_size; i++)
                m_arr[i] = v.m_arr[i];
            
            for (size_t i = v.m_size, j = 0; i < dif; i++, j++)
                m_arr[i] = temp.m_arr[j];
            
            m_size += v.m_size;
        }

        /* Inserts element before specified index */
        void insert(type elem, size_t index)
        {
            if (index > m_size)
                throw std::out_of_range("index out of range");
            
            if (m_size == m_max_size)
            {
                m_max_size *= 2;
                reallocate();
            }

            for (int i = m_size; i > index; i--)
                m_arr[i] = m_arr[i-1];

            m_arr[index] = elem;
            m_size++;
        }


        // Remove operations:
        /* Removes the last element */
        type pop_back()
        {
            if (m_size == 0)
                throw std::out_of_range("Vector is empty");

            type tmp = m_arr[m_size-1];
            m_size--;
            
            return tmp;
        }

        /* Removes the first element */
        type pop_front()
        {
            if (m_size == 0)
                throw std::out_of_range("Vector is empty");
            
            type tmp = m_arr[0];
            for (size_t i = 0; i < m_size - 1; i++)
                m_arr[i] = m_arr[i+1];

            m_size--;
            return tmp;
        }

        /* Erases all elements from start (inclusive) until end (exclusive) */
        void erase(size_t start, size_t end)
        {
            if (start > m_size || end > m_size || start > end)
                throw std::out_of_range("index out of range");
            
            if (end == m_size)
            {
                m_size = start;
                return;
            }
            
            for (size_t i = start, j = end; i < m_size; i++, j++)
                m_arr[i] = m_arr[j];

            m_size -= end - start;
        }


        // Non-return function:
        /* Prints all the vector elements */
        void print_vector() const
        {
            for (size_t i = 0; i < m_size; i++)
                std::cout << m_arr[i] << ' ';
            std::cout << '\n';
        }

        /* Erases all the elements. Note that if the elements themselves are pointers, the
           pointed-to memory is not touched in any way. Managing the pointer is
           the user's responsibility */
        void clear()
        {
            delete[] m_arr;
            m_size = 0;
            m_max_size = 10;
            m_arr = new type[m_max_size];
        }

        /* Resizes the vector to the specified number of elements. If the number is smaller than the vector's current size the vector is truncated, otherwise default constructed elements are appended. */
        void resize(size_t size)
        {
            if (size <= m_size)
                m_size = size;
            else
            {
                m_max_size = size;
                reallocate();
                m_size = m_max_size;
            }
        }

        /* Resizes the vector to the size specified and assigns every index to the element specified */
        void resize(size_t size, type elem)
        {
            delete[] m_arr;
            
            m_size = size;
            m_max_size = size;
            m_arr = new type[m_max_size];

            for (size_t i = 0; i < m_max_size; i++)
                m_arr[i] = elem;
        }

        /* Swap the vectors */
        void swap(vector<type> &v)
        {
            size_t tmp2 = m_size;
            m_size = v.m_size;
            v.m_size = tmp2;

            tmp2 = m_max_size;
            m_max_size = v.m_max_size;
            v.m_max_size = tmp2;

            type *tmp1 = m_arr;
            m_arr = v.m_arr;
            v.m_arr = tmp1;
        }

        // Returns funtions:
        /* Returns the maximum capacity the vector can have before allocating more */
        int capacity() const
        {
            return m_max_size;
        }

        /* Returns how many elements the vector has */
        int size() const
        {
            return m_size;
        }

        /* Returns true if the vector is empty */
        bool empty() const
        {
            return (m_size == 0);
        }
};
