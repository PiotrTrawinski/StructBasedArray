#pragma once
#include <cstddef>
#include <stdexcept>

template<typename T, size_t Size> struct StructArray;

namespace details {
    template<typename T, size_t Size> struct Iterator {
        Iterator(StructArray<T, Size>* arrPtr, int index) :
            arrPtr(arrPtr),
            index(index)
        {}
        Iterator& operator++() {
            index += 1;
            return *this;
        }
        Iterator& operator--() {
            index -= 1;
            return *this;
        }
        T& operator*() {
            return (*arrPtr)[index];
        }
        bool operator==(const Iterator& other) {
            return index == other.index && arrPtr == other.arrPtr;
        }
        bool operator!=(const Iterator& other) {
            return !(*this == other);
        }

        StructArray<T, Size>* arrPtr;
        size_t index;
    };

    template<typename T, size_t Size> struct ConstIterator {
        ConstIterator(const StructArray<T, Size>* arrPtr, int index) :
            arrPtr(arrPtr),
            index(index)
        {}
        ConstIterator& operator++() {
            index += 1;
            return *this;
        }
        ConstIterator& operator--() {
            index -= 1;
            return *this;
        }
        const T& operator*() {
            return (*arrPtr)[index];
        }
        bool operator==(const ConstIterator& other) {
            return index == other.index && arrPtr == other.arrPtr;
        }
        bool operator!=(const ConstIterator& other) {
            return !(*this == other);
        }

        const StructArray<T, Size>* arrPtr;
        size_t index;
    };
}


template<typename T, size_t Size> struct StructArray {
    using Iterator = details::Iterator<T, Size>;
    using ConstIterator = details::ConstIterator<T, Size>;

    StructArray() {}
    StructArray(std::initializer_list<T> init) :
        value(*init.begin()),
        rest((init.begin() + 1))
    {}
    StructArray(const T* iter) :
        value(*iter),
        rest((iter + 1))
    {}

    T& operator[](size_t index) {
        if (index == 0) return value;
        else            return rest[index - 1];
    }
    const T& operator[](size_t index) const {
        if (index == 0) return value;
        else            return rest[index - 1];
    }

    Iterator begin() {
        return Iterator(this, 0);
    }
    Iterator end() {
        return Iterator(this, Size);
    }

    ConstIterator begin() const {
        return ConstIterator(this, 0);
    }
    ConstIterator end() const {
        return ConstIterator(this, Size);
    }

    int size() const {
        return Size;
    }

private:
    T value;
    StructArray<T, Size - 1> rest;
};

template<typename T> struct StructArray<T, 1> {
    using Iterator = details::Iterator<T, 1>;
    using ConstIterator = details::ConstIterator<T, 1>;

    StructArray() {}
    StructArray(std::initializer_list<T> init) :
        value(*init.begin())
    {}
    StructArray(const T* iter) :
        value(*iter)
    {}

    T& operator[](size_t index) {
        if (index == 0) return value;
        else throw std::out_of_range("index out of range");
    }
    const T& operator[](size_t index) const {
        if (index == 0) return value;
        else throw std::out_of_range("index out of range");
    }
    
    Iterator begin() {
        return Iterator(this, 0);
    }
    Iterator end() {
        return Iterator(this, 1);
    }

    ConstIterator begin() const {
        return ConstIterator(this, 0);
    }
    ConstIterator end() const {
        return ConstIterator(this, 1);
    }

    int size() const {
        return 1;
    }

private:
    T value;
};

template<typename T> struct StructArray<T, 0> {
    using Iterator = details::Iterator<T, 0>;
    using ConstIterator = details::ConstIterator<T, 0>;

    StructArray() {}
    StructArray(std::initializer_list<T> init) {}
    StructArray(const T* iter) {}

    T& operator[](size_t index) {
        throw std::out_of_range("index out of range");
    }
    const T& operator[](size_t index) const {
        throw std::out_of_range("index out of range");
    }

    Iterator begin() {
        return Iterator(this, 0);
    }
    Iterator end() {
        return Iterator(this, 0);
    }

    ConstIterator begin() const {
        return ConstIterator(this, 0);
    }
    ConstIterator end() const {
        return ConstIterator(this, 0);
    }

    int size() const {
        return 0;
    }
};