#pragma once

template <typename T>
SmartVector<T>::SmartVector()
    : capacity(1), length(0), data(std::make_unique<T[]>(1)) {}

template <typename T>
void SmartVector<T>::resize(size_t new_capacity) {
    std::unique_ptr<T[]> new_data = std::make_unique<T[]>(new_capacity);
    for (size_t i = 0; i < length; ++i) {
        new_data[i] = std::move(data[i]);
    }
    capacity = new_capacity;
    data = std::move(new_data);
}

template <typename T>
void SmartVector<T>::push_back(const T &value) {
    if (length == capacity) {
        resize(capacity * 2);
    }
    data[length++] = value;
}

template <typename T>
void SmartVector<T>::pop_back() {
    if (length == 0)
        throw std::out_of_range("Vector is empty");
    --length;
}

template <typename T>
T &SmartVector<T>::operator[](size_t index) {
    if (index >= length)
        throw std::out_of_range("Index out of range");
    return data[index];
}

template <typename T>
const T &SmartVector<T>::operator[](size_t index) const {
    if (index >= length)
        throw std::out_of_range("Index out of range");
    return data[index];
}

template <typename T>
size_t SmartVector<T>::size() const {
    return length;
}

template <typename T>
size_t SmartVector<T>::get_capacity() const {
    return capacity;
}

template <typename T>
bool SmartVector<T>::empty() const {
    return length == 0;
}

template <typename T>
void SmartVector<T>::clear() {
    length = 0;
}

template <typename T>
void SmartVector<T>::reserve(size_t new_capacity) {
    if (new_capacity > capacity) {
        resize(new_capacity);
    }
}

template <typename T>
void SmartVector<T>::insert(size_t index, const T &value) {
    if (index > length)
        throw std::out_of_range("Index out of range");

    if (length == capacity) {
        resize(capacity * 2);
    }

    for (size_t i = length; i > index; --i) {
        data[i] = std::move(data[i - 1]);
    }

    data[index] = value;
    ++length;
}
