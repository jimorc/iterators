#ifndef VALUES_H
#define VALUES_H

#include <iterator>
#include <vector>

template <typename T>
class Value
{
    public:
        Value(const T& value) : m_value(value) {}
        const T& getValue() const noexcept { return m_value; }
        virtual ~Value() {}
    private:
        T m_value;
};

template<typename T>
class Values
{
    public:
        struct const_iterator;      // forward declaration

        struct iterator
        {
            using iterator_category = std::random_access_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = T;
            using pointer           = T*;  // or also value_type*
            using reference         = T&;  // or also value_type& 

            explicit iterator(pointer ptr) : m_ptr(ptr) {}
            reference operator*() const { return *m_ptr; }
            pointer operator->() const { return m_ptr; }

            // Prefix increment
            iterator& operator++() { ++m_ptr; return *this; }  

            // Postfix increment
            iterator operator++(int) { iterator tmp = *this; ++m_ptr; return tmp; }

            // Prefix decrement
            iterator& operator--() { --m_ptr; return *this; }  

            // Postfix decrement
            iterator operator--(int) { iterator tmp = *this; --m_ptr; return tmp; }

            friend bool operator== (const iterator& a, const iterator& b) { return a.m_ptr == b.m_ptr; };
            friend bool operator!= (const iterator& a, const iterator& b) { return a.m_ptr != b.m_ptr; };
            friend size_t operator- (const iterator& a, const iterator& b) { return a.m_ptr - b.m_ptr; };
            friend bool operator< (const iterator& a, const iterator& b) { return a.m_ptr < b.m_ptr; };
            friend const_iterator;

            private:
                pointer m_ptr;
        };

        struct const_iterator
        {
            using iterator_category = std::random_access_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = const T;
            using pointer           = const T*;  // or also value_type*
            using reference         = const T&;  // or also value_type& 

            explicit const_iterator(pointer ptr) : m_ptr(ptr) {}
            const_iterator(const iterator& it) : m_ptr(it.m_ptr) {}
            reference operator*() const { return *m_ptr; }
            pointer operator->() const { return m_ptr; }

            // Prefix increment
            const_iterator& operator++() { m_ptr++; return *this; }  

            // Postfix increment
            const_iterator operator++(int) { const_iterator tmp = *this; ++m_ptr; return tmp; }

            // Prefix decrement
            const_iterator& operator--() { m_ptr--; return *this; }  

            // Postfix decrement
            const_iterator operator--(int) { const_iterator tmp = *this; --m_ptr; return tmp; }

            friend bool operator== (const const_iterator& a, const const_iterator& b) { return a.m_ptr == b.m_ptr; };
            friend bool operator!= (const const_iterator& a, const const_iterator& b) { return a.m_ptr != b.m_ptr; };
            friend size_t operator- (const const_iterator& a, const const_iterator& b) { return a.m_ptr - b.m_ptr; };

            private:
                pointer m_ptr;
        };

        struct reverse_iterator
        {
            using iterator_category = std::random_access_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = T;
            using pointer           = T*;  // or also value_type*
            using reference         = T&;  // or also value_type& 

            explicit reverse_iterator(pointer ptr) : m_ptr(ptr) {}
            reference operator*() const { return *m_ptr; }
            pointer operator->() const { return m_ptr; }

            // Prefix increment
            reverse_iterator& operator++() { --m_ptr; return *this; }  

            // Postfix increment
            reverse_iterator operator++(int) { reverse_iterator tmp = *this; --m_ptr; return tmp; }

            // Prefix decrement
            reverse_iterator& operator--() { ++m_ptr; return *this; }  

            // Postfix decrement
            reverse_iterator operator--(int) { reverse_iterator tmp = *this; ++m_ptr; return tmp; }

            friend bool operator== (const reverse_iterator& a, const reverse_iterator& b) 
                { return a.m_ptr == b.m_ptr; };
            friend bool operator!= (const reverse_iterator& a, const reverse_iterator& b) 
                { return a.m_ptr != b.m_ptr; };
            friend size_t operator- (const reverse_iterator& a, const reverse_iterator& b) 
                { return a.m_ptr - b.m_ptr; };

            private:
                pointer m_ptr;
        };

        struct const_reverse_iterator
        {
            using iterator_category = std::random_access_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = const T;
            using pointer           = const T*;  // or also value_type*
            using reference         = const T&;  // or also value_type& 

            explicit const_reverse_iterator(pointer ptr) : m_ptr(ptr) {}
            reference operator*() const { return *m_ptr; }
            pointer operator->() const { return m_ptr; }

            // Prefix increment
            const_reverse_iterator& operator++() { m_ptr--; return *this; }  

            // Postfix increment
            const_reverse_iterator operator++(int) { const_reverse_iterator tmp = *this; --m_ptr; return tmp; }

            // Prefix decrement
            const_reverse_iterator& operator--() { m_ptr++; return *this; }  

            // Postfix decrement
            const_reverse_iterator operator--(int) { const_reverse_iterator tmp = *this; ++m_ptr; return tmp; }

            friend bool operator== (const const_reverse_iterator& a, const const_reverse_iterator& b) { return a.m_ptr == b.m_ptr; };
            friend bool operator!= (const const_reverse_iterator& a, const const_reverse_iterator& b) { return a.m_ptr != b.m_ptr; };
            friend size_t operator- (const const_reverse_iterator& a, const const_reverse_iterator& b) { return a.m_ptr - b.m_ptr; };

            private:
                pointer m_ptr;
        };

        Values() {}
        virtual ~Values() {}
        void push_back(const T& value) { m_values.push_back(value); }
        // Depending on the underlying storage type, this method could be very inefficient.
        void push_front(const T& value) { m_values.insert(m_values.cbegin(), value); }
        const std::vector<T>& get_values() const { return m_values; }
        size_t size() const { return m_values.size(); }
        void clear() { m_values.clear(); }
        T& operator[](size_t pos) { return m_values[pos]; }
        const T& operator[](size_t pos) const { return m_values[pos]; }
        T& at(size_t pos)
        {
            if(pos >= m_values.size()) throw std::out_of_range("Out of range");
            return m_values[pos];
        }
        const T& at(size_t pos) const
        {
            if(pos >= m_values.size()) throw std::out_of_range("Out of range");
            return m_values[pos];
        }
        // This is needed for actions performed by the various inserters.
        // Depending on the underlying storage type and where the insertion is performed,
        // this could be a very inefficient method.
        iterator insert(const_iterator pos, const T& val)
        {
            auto distance = std::distance(this->cbegin(), pos);
            std::vector<T> vec { val };
            auto valIter = m_values.cbegin();
            for (auto dist = 0; dist < distance; ++dist)
            {
                ++valIter;
            }
            m_values.insert(valIter, val);
            auto iter = this->begin();
            for (auto dist = 0; dist != distance; ++dist)
            {
                ++iter;
            }
            return iter;
        }
        iterator begin() noexcept { return iterator(m_values.data()); }
        iterator end() noexcept { return iterator(m_values.data() + m_values.size()); }
        const_iterator cbegin() const noexcept { return const_iterator(m_values.data()); }
        const_iterator cend() const noexcept { return const_iterator(m_values.data() + m_values.size()); }
        reverse_iterator rbegin() noexcept { return reverse_iterator(m_values.data() + m_values.size() - 1); }
        reverse_iterator rend() noexcept { return reverse_iterator(m_values.data() - 1); }
        const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(m_values.data() + m_values.size() - 1); }
        const_reverse_iterator crend() const noexcept { return const_reverse_iterator(m_values.data() - 1); }
    private:
        std::vector<T> m_values;
};

#endif      // VALUES_H