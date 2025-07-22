#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        Node* prev;

        Node(const T& val) : data(val), next(nullptr), prev(nullptr) {}
    };

    std::unique_ptr<Node> head;
    Node* tail;
    size_t length;
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), length(0) {}
    // Deleted copy operations (unique_ptr makes copying unsafe)
    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;
    // Move operations
    DoublyLinkedList(DoublyLinkedList&& other) noexcept
        : head(std::move(other.head)), tail(other.tail), length(other.length) {
        other.tail = nullptr;
        other.length = 0;
    }
    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head = std::move(other.head);
            tail = other.tail;
            length = other.length;

            other.tail = nullptr;
            other.length = 0;
        }
        return *this;
    }
    void push_front(const T& value) {
        auto new_node = std::make_unique<Node>(value);
        new_node->next = std::move(head);
        new_node->prev = nullptr;

        if (new_node->next) {
            new_node->next->prev = new_node.get();
        } else {
            tail = new_node.get();  // First node
        }

        head = std::move(new_node);
        ++length;
    }
    void push_back(const T& value) {
        auto new_node = std::make_unique<Node>(value);
        new_node->prev = tail;
        new_node->next = nullptr;

        if (tail) {
            tail->next = std::move(new_node);
            tail = tail->next.get();
        } else {
            head = std::move(new_node);
            tail = head.get();
        }

        ++length;
    }
    void pop_front() {
        if (!head) throw std::out_of_range("List is empty");
        head = std::move(head->next);
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        --length;
    }
    void pop_back() {
        if (!tail) throw std::out_of_range("List is empty");

        if (tail == head.get()) {
            head.reset();
            tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next.reset();
        }

        --length;
    }
    T& front() {
        if (!head) throw std::out_of_range("List is empty");
        return head->data;
    }
    T& back() {
        if (!tail) throw std::out_of_range("List is empty");
        return tail->data;
    }
    bool empty() const {
        return head == nullptr;
    }
    size_t size() const {
        return length;
    }
    void clear() {
        while (head) {
            pop_front();
        }
    }
    void insert(size_t index, const T& value) {
        if (index > length) throw std::out_of_range("Index out of range");
        if (index == 0) {
            push_front(value);
            return;
        }
        if (index == length) {
            push_back(value);
            return;
        }

        auto new_node = std::make_unique<Node>(value);
        Node* curr = head.get();
        for (size_t i = 0; i < index - 1; ++i) {
            curr = curr->next.get();
        }

        new_node->next = std::move(curr->next);
        new_node->prev = curr;

        if (new_node->next) {
            new_node->next->prev = new_node.get();
        } else {
            tail = new_node.get();
        }

        curr->next = std::move(new_node);
        ++length;
    }
    void remove(size_t index) {
        if (index >= length) throw std::out_of_range("Index out of range");
        if (index == 0) {
            pop_front();
            return;
        }
        if (index == length - 1) {
            pop_back();
            return;
        }

        Node* curr = head.get();
        for (size_t i = 0; i < index; ++i) {
            curr = curr->next.get();
        }

        if (curr->prev) {
            curr->prev->next = std::move(curr->next);
        }
        if (curr->next) {
            curr->next->prev = curr->prev;
        }

        --length;
    }
    ~DoublyLinkedList() {
        clear();
    }
};

int main() {
    DoublyLinkedList<int> dll;

    dll.push_back(10);
    dll.push_front(5);
    dll.push_back(20);

    std::cout << "Front: " << dll.front() << "\n"; // 5
    std::cout << "Back: " << dll.back() << "\n";   // 20

    dll.pop_front(); // remove 5
    std::cout << "New Front: " << dll.front() << "\n"; // 10

    dll.pop_back();  // remove 20
    std::cout << "New Back: " << dll.back() << "\n";   // 10

    std::cout << "Size: " << dll.size() << "\n";   // 1
    std::cout << "Empty? " << std::boolalpha << dll.empty() << "\n"; // false

    dll.clear();
    std::cout << "Cleared. Empty? " << dll.empty() << "\n"; // true

    return 0;
}
