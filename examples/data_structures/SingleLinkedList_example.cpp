#include <iostream>
#include <memory>
#include <stdexcept>

template <typename T>
class SmartSinglyLinkedList {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        Node(const T& val) : data(val), next(nullptr) {}
    };
    std::unique_ptr<Node> head;
    Node* tail;
    size_t length;

public:
    SmartSinglyLinkedList() : head(nullptr), tail(nullptr), length(0) {}

    void push_front(const T& value) {
        auto new_node = std::make_unique<Node>(value);
        if (!head) {
            tail = new_node.get();
        }
        new_node->next = std::move(head);
        head = std::move(new_node);
        ++length;
    }
    void push_back(const T& value) {
        auto new_node = std::make_unique<Node>(value);
        Node* new_tail = new_node.get();

        if (!head) {
            head = std::move(new_node);
            tail = new_tail;
        } else {
            tail->next = std::move(new_node);
            tail = new_tail;
        }
        ++length;
    }
    void pop_front() {
        if (!head) throw std::out_of_range("List is empty");
        head = std::move(head->next);
        if (!head) tail = nullptr;
        --length;
    }  
    void pop_back() {
        if (!head) throw std::out_of_range("List is empty");
        if (head->next == nullptr) {
            head.reset();
            tail = nullptr;
        } else {
            Node* curr = head.get();
            while (curr->next && curr->next->next) {
                curr = curr->next.get();
            }
            curr->next.reset();
            tail = curr;
        }
        --length;
    }
    void print() const {
        Node* curr = head.get();
        while (curr) {
            std::cout << curr->data << " -> ";
            curr = curr->next.get();
        }
        std::cout << "null\n";
    }
    void clear() {
        head.reset();
        tail = nullptr;
        length = 0;
    }
    void insert(size_t index, const T& value) {
        if (index > length) throw std::out_of_range("Index out of range");
        if (index == 0) {
            push_front(value);
            return;
        }
        auto new_node = std::make_unique<Node>(value);
        Node* curr = head.get();
        for (size_t i = 0; i < index - 1; ++i) {
            curr = curr->next.get();
        }
        new_node->next = std::move(curr->next);
        curr->next = std::move(new_node);
        if (!curr->next->next) tail = curr->next.get();
        ++length;
    }
    void remove(size_t index) {
        if (index >= length) throw std::out_of_range("Index out of range");
        if (index == 0) {
            pop_front();
            return;
        }
        Node* curr = head.get();
        for (size_t i = 0; i < index - 1; ++i) {
            curr = curr->next.get();
        }
        curr->next = std::move(curr->next->next);
        if (!curr->next) tail = curr;
        --length;
    }
    size_t size() const { return length; }
    bool empty() const { return length == 0; }
    const T& front() const {
        if (!head) throw std::out_of_range("List is empty");
        return head->data;
    }
    const T& back() const {
        if (!tail) throw std::out_of_range("List is empty");
        return tail->data;
    }
    // Disable copy
    SmartSinglyLinkedList(const SmartSinglyLinkedList&) = delete;
    SmartSinglyLinkedList& operator=(const SmartSinglyLinkedList&) = delete;
    // Allow move
    SmartSinglyLinkedList(SmartSinglyLinkedList&&) noexcept = default;
    SmartSinglyLinkedList& operator=(SmartSinglyLinkedList&&) noexcept = default;
    ~SmartSinglyLinkedList() = default;
};

int main() {
    SmartSinglyLinkedList<int> list;

    list.push_back(10);
    list.push_back(20);
    list.push_front(5);
    list.print(); // 5 -> 10 -> 20 -> null

    list.pop_front();
    list.print(); // 10 -> 20 -> null

    std::cout << "Front: " << list.front() << "\n";
    std::cout << "Back: " << list.back() << "\n";

    return 0;
}
