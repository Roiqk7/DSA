#include <iostream>

template <typename T, size_t S> class Array {
        public:
                constexpr int Size() const {return S;}

                T& operator[](size_t index) {return data[index];}
                const T& operator[](size_t index) const {return data[index];}

                T* Data() {return data;}

        private:
                T data[S]; // Our array.
};

int main()
{
        Array<int, 10> arr;

        for (size_t i = 0; i < 10; i++) arr[i] = i;

        for (size_t i = 0; i < 10; i++) std::cout << arr[i];

        return 0;
}