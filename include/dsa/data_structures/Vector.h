#ifndef SMARTVECTOR_H
#define SMARTVECTOR_H

#include <memory>
#include <cstddef>
#include <stdexcept>

template <typename T>
class SmartVector {
private:
    std::unique_ptr<T[]> data;
    size_t capacity;
    size_t length;

    void resize(size_t new_capacity);

public:
    SmartVector();
    void push_back(const T &value);
    void pop_back();
    T &operator[](size_t index);
    const T &operator[](size_t index) const;
    size_t size() const;
    size_t get_capacity() const;
    bool empty() const;
    void clear();
    void reserve(size_t new_capacity);
    void insert(size_t index, const T &value);

    // Disallow copy
    SmartVector(const SmartVector &) = delete;
    SmartVector &operator=(const SmartVector &) = delete;

    // Allow move
    SmartVector(SmartVector &&other) noexcept = default;
    SmartVector &operator=(SmartVector &&other) noexcept = default;

    ~SmartVector() = default;
};

// Template implementation
#include "SmartVector.tpp" // Ensure SmartVector.tpp is in the same directory as Vector.h

#endif // SMARTVECTOR_H
