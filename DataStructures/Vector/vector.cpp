#include <iostream>
#include <string>

template<typename T> class Vector
{
        public:
                Vector()
                {
                        reAlloc(2);
                }

                ~Vector()
                {
                        clear();
                        ::operator delete[](m_data, m_capacity*sizeof(T));
                }

                void pushBack(T&& value)
                {
                        if (m_capacity <= m_size) reAlloc(2*m_capacity);

                        m_data[m_size++] = value;
                }

                void pushBack(const T& value)
                {
                        if (m_capacity <= m_size) reAlloc(2*m_capacity);

                        m_data[m_size++] = std::move(value);
                }

                template<typename... Args> T& emplaceBack(Args&&... args)
                {
                        if (m_capacity <= m_size) reAlloc(2*m_capacity);

                        new(&m_data[m_size]) T(std::forward(args)...);

                        return m_data[m_size++];
                }

                void popBack()
                {
                        if (m_size > 0)
                        {
                                m_size--;
                                m_data[m_size].~T();
                        }
                }

                void clear()
                {
                        for (size_t i = 0; i < m_size; i++) m_data[i].~T();

                        m_size = 0;
                }

                T& operator[](size_t index) {return m_data[index];}
                const T& operator[](size_t index) const {return m_data[index];}

                size_t size() const {return m_size;}

        private:
                T* m_data = nullptr;
                size_t m_size = 0;
                size_t m_capacity = 0;

                void reAlloc(size_t newCapacity)
                {
                        T* newBlock = (T*)::operator new(newCapacity*sizeof(T));

                        if (newCapacity < m_size) m_size = newCapacity; // check for downsizing

                        for (size_t i = 0; i < m_size; i++) newBlock[i] = std::move(m_data[i]); // move data

                        for (size_t i = 0; i < m_size; i++) m_data[i].~T();

                        ::operator delete[](m_data, m_capacity*sizeof(T));
                        m_data = newBlock;
                        m_capacity = newCapacity;
                }
};

int main()
{
        Vector<std::string> vector;

        for (int i = 0; i < 25; i++) vector.pushBack("Roiqk\n");

        for (int i = 0; i < 25; i++) std::cout << vector[i];

        vector.clear();

        return 0;
}
