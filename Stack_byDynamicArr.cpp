#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T>
class Stack
{
private:
    int size{0};
    int capacity{0};
    std::unique_ptr<T[]> array;

    void resize(int new_capacity)
    {
        std::unique_ptr<T[]> new_array = std::make_unique<T[]>(new_capacity);
        for (int i = 0; i < size; ++i)
        {
            new_array[i] = std::move(array[i]);
        }
        array = std::move(new_array);
        capacity = new_capacity;
    }

public:
    Stack() : capacity(4), array(std::make_unique<T[]>(capacity)) {}
    void push(const T &value)
    {
        if (size == capacity)
        {
            resize(capacity * 2); // Double capacity when full
        }
        array[size++] = value;
    }
    void pop()
    {
        if (is_empty())
        {
            std::cerr << "Stack is empty\n";
            return;
        }
        --size;
    }
    T peek() const
    {
        if (is_empty())
        {
            throw std::underflow_error("Stack is empty");
        }
        return array[size - 1];
    }
    bool is_empty() const
    {
        return size == 0;
    }
    int get_size() const
    {
        return size;
    }
    void clear()
    {
        size = 0;
    }
    void display() const
    {
        if (is_empty())
        {
            std::cout << "Stack is empty\n";
            return;
        }
        for (int i = size - 1; i >= 0; --i)
        {
            std::cout << array[i] << " ";
        }
        std::cout << "\n";
    }
    void isfull() const
    {
        std::cout << (size == capacity ? "Stack is full\n" : "Stack is not full\n");
    }
    void is_same(const Stack<T> &other) const
    {
        if (size != other.size || capacity != other.capacity)
        {
            std::cout << "Stacks are not the same\n";
            return;
        }
        for (int i = 0; i < size; ++i)
        {
            if (array[i] != other.array[i])
            {
                std::cout << "Stacks are not the same\n";
                return;
            }
        }
        std::cout << "Stacks are the same\n";
    }
};
