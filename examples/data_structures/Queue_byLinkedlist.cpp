#include <iostream>
#include <list>
#include <memory>
#include <stdexcept>

template <typename T>
class SmartQueue {
private:
    std::list<std::shared_ptr<T>> container;

public:
    SmartQueue() = default;

    void enqueue(const T& value) {
        container.push_back(std::make_shared<T>(value));
    }
    void dequeue() {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        container.pop_front();
    }
    T& front() {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return *container.front();
    }
    const T& front() const {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }
        return *container.front();
    }
    bool empty() const {
        return container.empty();
    }
    size_t size() const {
        return container.size();
    }
    void clear() {
        container.clear();
    }
    SmartQueue(const SmartQueue&) = delete;
    SmartQueue& operator=(const SmartQueue&) = delete;
    SmartQueue(SmartQueue&&) noexcept = default;
    SmartQueue& operator=(SmartQueue&&) noexcept = default;
    ~SmartQueue() = default;
};
int main() {
    SmartQueue<int> q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    std::cout << "Front: " << q.front() << "\n";

    q.dequeue();
    std::cout << "Front after dequeue: " << q.front() << "\n";

    std::cout << "Size: " << q.size() << "\n";

    q.clear();
    std::cout << "Is empty? " << std::boolalpha << q.empty() << "\n";

    return 0;
}
