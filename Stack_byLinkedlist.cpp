#include <iostream>
#include <memory>
#include <utility>
template <typename T>
class Stack
{
private:
    struct Node
    {
        T data;
        std::unique_ptr<Node> next;
        Node(T val) : data(val), next(nullptr) {}
    };

    std::unique_ptr<Node> head;
    int length = 0;
    Node *tail = nullptr;
    Node *head= nullptr;
    public:
    Stack() = default;
    ~Stack() = default;
    void push(const T &value)
    {
        auto newNode = std::make_unique<Node>(value);
        if (!head)
        {
            head = std::move(newNode);
            tail = head.get();
        }
        else
        {
            newNode->next = std::move(head);
            head = std::move(newNode);
        }
        length++;
    }
    void pop()
    {
        if (!head)
        {
            std::cerr << "Stack is empty\n";
            return;
        }
        head = std::move(head->next);
        length--;
        if (length == 0)
            tail = nullptr;
    }
    T peek() const
    {
        if (!head)
        {
            throw std::underflow_error("Stack is empty");
        }
        return head->data;
    }
    bool is_empty() const
    {
        return length == 0;
    }
    int get_size() const
    {
        return length;
    }
    void clear()
    {
        head.reset();
        tail = nullptr;
        length = 0;
    }
    void display() const
    {
        Node *current = head.get();
        while (current)
        {
            std::cout << current->data << " ";
            current = current->next.get();
        }
        std::cout << "\n";
    }
    
};