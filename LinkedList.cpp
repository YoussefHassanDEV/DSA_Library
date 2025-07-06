#include <iostream>
#include <memory>
#include <utility>
template <typename T>
class LinkedList
{
private:
    struct Node
    {
        T value;
        std::unique_ptr<Node> next;
        Node(T val) : value(val), next(nullptr) {}
    };
    std::unique_ptr<Node> head;
    Node *tail = nullptr;
    int length = 0;

public:
    LinkedList() = default;
    ~LinkedList() = default;
    void print() const
    {
        Node *current = head.get();
        while (current)
        {
            std::cout << current->value << " ";
            current = current->next.get();
        }
        std::cout << std::endl;
    }
    void print_reverse(const Node *node) const
    {
        if (!node)
            return;
        print_reverse(node->next.get());
        std::cout << node->value << " ";
    }
    void print_recursive(const Node *node) const
    {
        if (!node)
            return;
        std::cout << node->value << " ";
        print_recursive(node->next.get());
    }
    void push_back(const T &value)
    {
        auto newNode = std::make_unique<Node>(value);
        if (!tail)
        {
            head = std::move(newNode);
            tail = head.get();
        }
        else
        {
            tail->next = std::move(newNode);
            tail = tail->next.get();
        }
        length++;
    }
    void push_front(const T &value)
    {
        auto newNode = std::make_unique<Node>(value);
        if (!head)
        {
            tail = newNode.get();
        }
        newNode->next = std::move(head);
        head = std::move(newNode);
        length++;
    }
    void pop_back()
    {
        if (!head)
            return;
        if (head.get() == tail)
        {
            head.reset();
            tail = nullptr;
        }
        else
        {
            Node *current = head.get();
            while (current->next.get() != tail)
                current = current->next.get();
            current->next.reset();
            tail = current;
        }
        length--;
    }
    void pop_front()
    {
        if (!head)
            return;
        head = std::move(head->next);
        if (!head)
            tail = nullptr;
        length--;
    }
    void insert(const T &value, int position)
    {
        if (position <= 0)
        {
            push_front(value);
            return;
        }
        Node *current = head.get();
        for (int i = 0; i < position - 1 && current; ++i)
            current = current->next.get();
        if (!current)
        {
            push_back(value);
        }
        else
        {
            auto newNode = std::make_unique<Node>(value);
            newNode->next = std::move(current->next);
            current->next = std::move(newNode);
            if (!current->next->next)
                tail = current->next.get();
            length++;
        }
    }
    void erase(int position)
    {
        if (!head || position < 0)
            return;
        if (position == 0)
        {
            pop_front();
            return;
        }
        Node *current = head.get();
        for (int i = 0; i < position - 1 && current && current->next; ++i)
            current = current->next.get();
        if (!current || !current->next)
            return;
        if (current->next.get() == tail)
            tail = current;
        current->next = std::move(current->next->next);
        length--;
    }
    void clear()
    {
        head.reset();
        tail = nullptr;
        length = 0;
    }
    bool is_empty() const
    {
        return head == nullptr;
    }
    int size() const
    {
        return length;
    }
    void reverse()
    {
        Node *prev = nullptr;
        Node *current = head.release();
        tail = current;
        while (current)
        {
            Node *next = current->next.release();
            current->next.reset(prev);
            prev = current;
            current = next;
        }
        head.reset(prev);
    }
    void get_nth(int n) const
    {
        if (n < 0 || n >= length)
        {
            std::cout << "Index out of bounds\n";
            return;
        }
        Node *current = head.get();
        for (int i = 0; i < n; ++i)
            current = current->next.get();
        std::cout << "Value at index " << n << ": " << current->value << "\n";
    }
    void search(const T &value) const
    {
        Node *current = head.get();
        int index = 0;
        while (current)
        {
            if (current->value == value)
            {
                std::cout << "Value " << value << " found at index " << index << "\n";
                return;
            }
            current = current->next.get();
            index++;
        }
        std::cout << "Value " << value << " not found\n";
    }
    int improved_search(const T &value)
    {
        Node *prv = nullptr;
        Node *cur = head.get();
        int index = 0;
        while (cur)
        {
            if (cur->value == value)
            {
                if (prv)
                {
                    std::swap(prv->value, cur->value); // move-to-front optimization
                }
                return index;
            }
            prv = cur;
            cur = cur->next.get();
            index++;
        }
        return -1; // not found
    }

    void check_integrity() const
    {
        if (length == 0 && head)
        {
            std::cout << "Error: List is empty but head is not null\n";
        }
        if (length > 0 && !head)
        {
            std::cout << "Error: List has elements but head is null\n";
        }
        Node *current = head.get();
        int count = 0;
        while (current)
        {
            count++;
            current = current->next.get();
        }
        if (count != length)
        {
            std::cout << "Error: Length mismatch, expected " << length << " but found " << count << "\n";
        }
    }
};
// #include "LinkedList.hpp"
int main()
{
    LinkedList<int> list;

    list.push_back(10);
    list.push_back(20);
    list.push_front(5);

    list.print(); // Output: 5 10 20

    list.insert(15, 2);
    list.print(); // Output: 5 10 15 20

    list.erase(1);
    list.print(); // Output: 5 15 20

    list.reverse();
    list.print(); // Output: 20 15 5

    list.search(15); // Output: found at index 1
    list.check_integrity();
    list.clear();
    std::cout << "Is empty: " << list.is_empty() << std::endl;
}
