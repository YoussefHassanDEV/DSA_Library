#include <iostream>
#include <list>
#include <stdexcept>
template <typename T>
class Stack
{
private:
    std::list<T> container; // aggregated STL doubly linked list
public:
    Stack() = default;

    void push(const T &value)
    {
        container.push_back(value);
    }

    void pop()
    {
        if (empty())
            throw std::out_of_range("Stack is empty");
        container.pop_back();
    }

    T &top()
    {
        if (empty())
            throw std::out_of_range("Stack is empty");
        return container.back();
    }

    const T &top() const
    {
        if (empty())
            throw std::out_of_range("Stack is empty");
        return container.back();
    }

    bool empty() const
    {
        return container.empty();
    }

    size_t size() const
    {
        return container.size();
    }

    void clear()
    {
        container.clear();
    }

    // Disable copy
    Stack(const Stack &) = delete;
    Stack &operator=(const Stack &) = delete;

    // Allow move
    Stack(Stack &&) noexcept = default;
    Stack &operator=(Stack &&) noexcept = default;

    ~Stack() = default;
};

int main()
{
    Stack<int> s;

    s.push(10);
    s.push(20);
    s.push(30);

    std::cout << "Top: " << s.top() << "\n"; // 30
    s.pop();
    std::cout << "Top after pop: " << s.top() << "\n"; // 20
    std::cout << "Size: " << s.size() << "\n";         // 2

    s.clear();
    std::cout << "Empty? " << std::boolalpha << s.empty() << "\n"; // true

    return 0;
}
