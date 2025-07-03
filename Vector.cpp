#include <iostream>
#include <cassert>
#include <memory>
template <typename T>

class Vector
{
private:
    std::unique_ptr<T[]> arr;
    int size = 0;
    int capacity = 0;

public:
    Vector(int size) : size(size), capacity(size)
    {
        if (size < 0)
            size = 1;
        this->size = size;
        this->capacity = size;
        arr = std::make_unique<T[]>(capacity);
    }
    ~Vector()
    {

    };
    T get(int idx)
    {
        assert(idx >= 0 && idx < size);
        return arr[idx];
    }
    void set(int idx, T value)
    {
        assert(idx >= 0 && idx < size);
        arr[idx] = value;
    }
    void print() const
    {
        for (int i = 0; i < size; i++)
        {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
    int find(const T &value) const
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[i] == value)
                return i;
        }
        return -1; // Not found
    }
    int getSize() const
    {
        return size;
    }
    T getFront() const
    {
        assert(size > 0);
        return arr[0];
    }
    T getBack() const
    {
        assert(size > 0);
        return arr[size - 1];
    }
    void clear()
    {
        arr.reset();
        size = 0;
        capacity = 0;
    }
    bool isEmpty() const
    {
        return size == 0;
    }
    void expandCapacity()
    {
        if (capacity == 0)
            capacity = 1;
        else
            capacity *= 2;
        std::unique_ptr<T[]> newArr = std::make_unique<T[]>(capacity);
        for (int i = 0; i < size; ++i)
            newArr[i] = arr[i];
        arr = std::move(newArr);
    }
    void pushBack(const T &value)
    {
        if (size >= capacity)
            expandCapacity();
        arr[size++] = value;
    }
    void popBack()
    {
        assert(size > 0);
        --size;
    }
    void insert(int idx, const T &value)
    {
        assert(idx >= 0 && idx <= size);
        if (size >= capacity)
            expandCapacity();
        for (int i = size; i > idx; --i)
            arr[i] = arr[i - 1];
        arr[idx] = value;
        ++size;
    }
    void erase(int idx)
    {
        assert(idx >= 0 && idx < size);
        for (int i = idx; i < size - 1; ++i)
            arr[i] = arr[i + 1];
        --size;
    }
    void right_rotate()
    {
        assert(size > 0);
        T last = arr[size - 1];
        for (int i = size - 1; i > 0; --i)
            arr[i] = arr[i - 1];
        arr[0] = last;
    }
    void left_rotate()
    {
        assert(size > 0);
        T first = arr[0];
        for (int i = 0; i < size - 1; ++i)
            arr[i] = arr[i + 1];
        arr[size - 1] = first;
    }
    void right_rotate(int k)
    {
        assert(k >= 0 && size > 0);
        k %= size;
        for (int i = 0; i < k; ++i)
            right_rotate();
    }
    void left_rotate(int k)
    {
        assert(k >= 0 && size > 0);
        k %= size;
        for (int i = 0; i < k; ++i)
            left_rotate();
    }
    void deletePosition(int idx)
    {
        assert(idx >= 0 && idx < size);
        for (int i = idx; i < size - 1; ++i)
            arr[i] = arr[i + 1];
        --size;
    }
    int improvedSearch(const T &value) const
    {
        if (size == 0)
            return -1;
        int idx = 0;
        while (idx < size && arr[idx] < value)
            ++idx;
        if (idx < size && arr[idx] == value)
            return idx;
        return -1;
    }
};
int main()
{
    Vector<int> vec(5);
    for (int i = 0; i < 5; ++i)
        vec.set(i, i * 10);

    vec.print(); // Output: 0 10 20 30 40
    vec.pushBack(50);
    vec.insert(2, 15);
    vec.print(); // Output: 0 10 15 20 30 40 50

    std::cout << vec.getFront() << " " << vec.getBack() << "\n"; // 0 50
    vec.right_rotate(2);
    vec.print(); // Output: 40 50 0 10 15