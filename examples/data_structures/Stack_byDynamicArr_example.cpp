#include <iostream>
#include <stdexcept>
#include <memory> // for std::unique_ptr

template <typename T>
class DynamicArrayStack {
private:
    std::unique_ptr<T[]> data;
    size_t capacity;
    size_t top_index;

    void resize(size_t new_capacity) {
        std::unique_ptr<T[]> new_data = std::make_unique<T[]>(new_capacity);
        for (size_t i = 0; i < top_index; ++i) {
            new_data[i] = std::move(data[i]);
        }
        data = std::move(new_data);
        capacity = new_capacity;
    }

public:
    DynamicArrayStack()
        : capacity(4), top_index(0), data(std::make_unique<T[]>(capacity)) {}
    void push(const T& value) {
        if (top_index == capacity) {
            resize(capacity * 2);
        }
        data[top_index++] = value;
    }
    void pop() {
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        --top_index;
    }
    T& top() {
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return data[top_index - 1];
    }
    const T& top() const {
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return data[top_index - 1];
    }
    bool empty() const {
        return top_index == 0;
    }
    size_t size() const {
        return top_index;
    }
    void clear() {
        top_index = 0;
    }
};

// Example usage
int main() {
    DynamicArrayStack<int> stack;

    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::cout << "Top: " << stack.top() << "\n"; // 30

    stack.pop();
    std::cout << "Top after pop: " << stack.top() << "\n"; // 20

    std::cout << "Stack size: " << stack.size() << "\n"; // 2

    stack.clear();
    std::cout << "Is stack empty? " << std::boolalpha << stack.empty() << "\n"; // true

    return 0;
}
