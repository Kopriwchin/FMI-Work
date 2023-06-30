#pragma once

#include <iostream>

template <typename T>

class DynamicArray {
private:
    T* elements;
    size_t size;
    size_t capacity;

    void resize(size_t newCapacity) {
        T* newElements = new T[newCapacity];
        for (size_t i = 0; i < size; ++i) {
            newElements[i] = elements[i];
        }
        delete[] elements;
        elements = newElements;
        capacity = newCapacity;
    }

public:
    DynamicArray() : elements(nullptr), size(0), capacity(0) {}

    ~DynamicArray() {
        delete[] elements;
    }

    void push_back(const T& value) {
        if (size == capacity) {
            size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
            resize(newCapacity);
        }
        elements[size++] = value;
    }

    void pop_back() {
        if (size > 0) {
            --size;
        }
    }

    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return elements[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return elements[index];
    }

    size_t getSize() const {
        return size;
    }

    size_t getCapacity() const {
        return capacity;
    }
};