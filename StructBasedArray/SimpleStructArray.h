#pragma once
#include <cstddef>
#include <stdexcept>

template<typename T, size_t Size> struct SimpleStructArray {
    T& operator[](size_t index) {
        if (index == 0) return value;
        else            return rest[index - 1];
    }
private:
    T value;
    Array<T, Size - 1> rest;
};

template<typename T> struct SimpleStructArray<T, 0> {
    T& operator[](size_t index) {
        throw std::out_of_range("index out of range");
    }
};