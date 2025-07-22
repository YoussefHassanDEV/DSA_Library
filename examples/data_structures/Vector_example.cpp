#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T>
class SmartVector
{
private:
    std::unique_ptr<T[]> data;
    size_t capacity;
    size_t length;

    void resize(size_t new_capacity)
    {
        std::unique_ptr<T[]> new_data = std::make_unique<T[]>(new_capacity);
        for (size_t i = 0; i < length; ++i)
        {
            new_data[i] = std::move(data[i]);
        }
        capacity = new_capacity;
        data = std::move(new_data);
    }

public:
    SmartVector() : capacity(1), length(0), data(std::make_unique<T[]>(1)) {}   
    void push_back(const T &value)
    {
        if (length == capacity)
        {
            resize(capacity * 2);
        }
        data[length++] = value;
    }
    void pop_back()
    {
        if (length == 0)
            throw std::out_of_range("Vector is empty");
        --length;
    }
    T &operator[](size_t index)
    {
        if (index >= length)
            throw std::out_of_range("Index out of range");
        return data[index];
    }
    const T &operator[](size_t index) const
    {
        if (index >= length)
            throw std::out_of_range("Index out of range");
        return data[index];
    }
    size_t size() const
    {
        return length;
    }
    size_t get_capacity() const
    {
        return capacity;
    }
    bool empty() const
    {
        return length == 0;
    }
    void clear()
    {
        length = 0;
    }
    void reserve(size_t new_capacity)
    {
        if (new_capacity > capacity)
        {
            resize(new_capacity);
        }
    }
    void insert(size_t index, const T &value)
    {
        if (index > length)
            throw std::out_of_range("Index out of range");
        if (length == capacity)
        {
            resize(capacity * 2);
        }
        for (size_t i = length; i > index; --i)
        {
            data[i] = std::move(data[i - 1]);
        }
        data[index] = value;
        ++length;
    }
    // Disallow copying
    SmartVector(const SmartVector &) = delete;
    SmartVector &operator=(const SmartVector &) = delete;

    // Allow move semantics
    SmartVector(SmartVector &&other) noexcept = default;
    SmartVector &operator=(SmartVector &&other) noexcept = default;
};
int main()
{
    SmartVector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    for (size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << "\n";

    vec.pop_back();
    std::cout << "After pop, size = " << vec.size() << "\n";
}
