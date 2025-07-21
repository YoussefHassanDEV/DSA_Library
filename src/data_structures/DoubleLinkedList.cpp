#include <iostream>
#include <memory>
#include <utility>
template <typename T>
class DoubleLinkedList
{
private:
    struct Node
    {
        T data{};
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
    DoubleLinkedList() = default;
    ~DoubleLinkedList() = default;

    void link(Node *prev, Node *next)
    {
        if (prev)
            prev->next = next;
        if (next)
            next->prev = prev;
    }
    void delete_and_link(Node *node)
    {
        if (!node)
            return;
        if (node->prev)
            node->prev->next = std::move(node->next);
        if (node->next)
            node->next->prev = node->prev;
        if (node == head.get())
            head.reset(node->next.release());
        if (node == tail)
            tail = node->prev;
        length--;
    }
    void insert(const T &value, int position)
    {
        if (position <= 0)
        {
            auto newNode = std::make_unique<Node>(value);
            newNode->next = std::move(head);
            if (head)
                head->prev = newNode.get();
            head = std::move(newNode);
            if (!tail)
                tail = head.get();
            length++;
            return;
        }

        if (position >= length)
        {
            auto newNode = std::make_unique<Node>(value);
            if (tail)
            {
                tail->next = std::move(newNode);
                tail->next->prev = tail;
                tail = tail->next.get();
            }
            else
            {
                head = std::move(newNode);
                tail = head.get();
            }
            length++;
            return;
        }

        Node *current = head.get();
        for (int i = 0; i < position - 1 && current; ++i)
        {
            current = current->next.get();
        }

        auto newNode = std::make_unique<Node>(value);
        newNode->set(current->prev, current);
        link(current->prev, newNode.get());
        link(newNode.get(), current);
        length++;
    }
    void print() const
    {
        Node *current = head.get();
        while (current)
        {
            std::cout << current->data << " ";
            current = current->next.get();
        }
        std::cout << "\n";
    }
    void reverse()
    {
        Node *current = head.release();
        tail = current;
        Node *prev = nullptr;
        while (current)
        {
            Node *next = current->next.release();
            current->next.reset(prev);
            current->prev = next; // Set the previous pointer
            prev = current;
            current = next;
        }
        head.reset(prev);
    }
    void pop_front()
    {
        if (!head)
            return;
        if (head->next)
        {
            head = std::move(head->next);
            head->prev = nullptr;
        }
        else
        {
            head.reset();
            tail = nullptr;
        }
        length--;
    }
    void pop_back()
    {
        if (!tail)
            return;
        if (tail->prev)
        {
            tail = tail->prev;
            tail->next.reset();
        }
        else
        {
            head.reset();
            tail = nullptr;
        }
        length--;
    }
    void delete_at(int position)
    {
        if (position < 0 || position >= length)
        {
            std::cout << "Index out of bounds\n";
            return;
        }
        if (position == 0)
        {
            pop_front();
            return;
        }
        if (position == length - 1)
        {
            pop_back();
            return;
        }
        Node *current = head.get();
        for (int i = 0; i < position; ++i)
        {
            current = current->next.get();
        }
        delete_and_link(current);
    }
    void clear()
    {
        head.reset();
        tail = nullptr;
        length = 0;
    }
    int size() const
    {
        return length;
    }
    bool is_empty() const
    {
        return length == 0;
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
        std::cout << "Value at index " << n << ": " << current->data << "\n";
    }
    void search(const T &value) const
    {
        Node *current = head.get();
        int index = 0;
        while (current)
        {
            if (current->data == value)
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
            if (cur->data == value)
            {
                if (prv)
                {
                    std::swap(prv->data, cur->data); // move-to-front optimization
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
    void is_same(const DoubleLinkedList<T> &other) const
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
            if (current1->data != current2->data)
            {
                std::cout << "Lists are not the same, found different values\n";
                return;
            }
            current1 = current1->next.get();
            current2 = current2->next.get();
        }
        std::cout << "Lists are the same\n";
    }
    void print_reverse() const
    {
        Node *current = tail;
        while (current)
        {
            std::cout << current->data << " ";
            current = current->prev;
        }
        std::cout << "\n";
    }
    void print_recursive(const Node *node) const
    {
        if (!node)
            return;
        std::cout << node->data << " ";
        print_recursive(node->next.get());
    }
    void print_recursive_reverse(const Node *node) const
    {
        if (!node)
            return;
        print_recursive_reverse(node->next.get());
        std::cout << node->data << " ";
    }
    void print_recursive_reverse() const
    {
        print_recursive_reverse(head.get());
        std::cout << "\n";
    }
    void print_recursive() const
    {
        print_recursive(head.get());
        std::cout << "\n";
    }
    void delete_even()
    {
        Node *current = head.get();
        while (current)
        {
            Node *next = current->next.get();
            if (current->data % 2 == 0)
            {
                delete_and_link(current);
            }
            current = next;
        }
    }
    void delete_odd()
    {
        Node *current = head.get();
        while (current)
        {
            Node *next = current->next.get();
            if (current->data % 2 != 0)
            {
                delete_and_link(current);
            }
            current = next;
        }
    }
    void delete_even_positions()
    {
        Node *current = head.get();
        int index = 0;
        while (current)
        {
            Node *next = current->next.get();
            if (index % 2 == 0)
            {
                delete_and_link(current);
            }
            current = next;
            index++;
        }
    }
    void delete_odd_positions()
    {
        insert_front(-1); // Dummy node to handle edge cases
        delete_even_positions();
        pop_front(); // Remove the dummy node
    }
    bool isPalindrome() const
    {
        Node *left = head.get();
        Node *right = tail;
        while (left && right && left != right && left->prev != right)
        {
            if (left->data != right->data)
                return false;
            left = left->next.get();
            right = right->prev;
        }
        return true;
    }
};

// DoubleLinkedList::DoubleLinkedList(/* args */)
// {
// }

// DoubleLinkedList::~DoubleLinkedList()
// {
// }
