#include <iostream>
#include <memory>
#include <utility>
template <typename T>
class DoubleLinkedList
{
private:
    struct Node
    {
        T / data{};
        std::unique_ptr<Node> next;
        Node *prev{};
        Node *next{};
        Node(T val) : data(val) {}
        void set(Node *prev, Node *next)
        {
            this->prev = prev;
            this->next = next;
        }
    };
    std::unique_ptr<Node> head;
    Node *tail = nullptr;
    int length = 0;

public:
    DoubleLinkedList(/* args */);
    ~DoubleLinkedList();
};

DoubleLinkedList::DoubleLinkedList(/* args */)
{
}

DoubleLinkedList::~DoubleLinkedList()
{
}
