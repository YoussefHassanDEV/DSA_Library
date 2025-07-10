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
        // 🔹 Insert at front if position is <= 0
        if (position <= 0)
        {
            push_front(value);
            return;
        }

        // 🔹 Insert at back if position is out of bounds
        if (position >= length)
        {
            push_back(value);
            return;
        }

        // 🔹 Traverse to position - 1
        Node *current = head.get();
        for (int i = 0; i < position - 1; ++i)
        {
            current = current->next.get(); // Move one step forward
        }

        // 🔹 Insert new node after 'current'
        auto newNode = std::make_unique<Node>(value);
        newNode->next = std::move(current->next); // Link to the rest of the list
        current->next = std::move(newNode);       // Current now points to new node
        length++;
    }
    void erase(int position)
    {
        // Case 1: Invalid position or empty list
        if (!head || position < 0 || position >= length)
            return;
        // Case 2: Erase the head node
        if (position == 0)
        {
            pop_front();
            return;
        }
        // Step 1: Traverse to the node just before the one to erase
        Node *current = head.get();
        for (int i = 0; i < position - 1; ++i)
            current = current->next.get();
        //Step 2: Check if the next node exists
        if (!current || !current->next)
            return; // This should never happen due to length check above

        //Step 3: If deleting the tail, update tail pointer
        if (current->next.get() == tail)
            tail = current;
        //Step 4: Delete the target node by skipping it
        current->next = std::move(current->next->next);
        //Step 5: Decrease length
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
    void is_same(const LinkedList<T> &other) const
    {
        if (length != other.length)
        {
            std::cout << "Lists are not the same, different lengths\n";
            return;
        }
        Node *current1 = head.get();
        Node *current2 = other.head.get();
        while (current1 && current2)
        {
            if (current1->value != current2->value)
            {
                std::cout << "Lists are not the same, found different values\n";
                return;
            }
            current1 = current1->next.get();
            current2 = current2->next.get();
        }
        std::cout << "Lists are the same\n";

    }
};

// #include "LinkedList.hpp"
int main()
{
    LinkedList<int> list,list1;

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
    list.is_same(list1); // Output: Lists are the same
    std::cout << "Is empty: " << list.is_empty() << std::endl;
}
