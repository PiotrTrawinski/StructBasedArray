#include "StructArray.h"
#include <iostream>
#include <algorithm>

int sum(const StructArray<int, 10>& arr) {
    int value = 0;
    for (int i = 0; i < arr.size(); ++i) {
        value += arr[i];
    }
    return value;
}

template<typename T, int Size> std::ostream& operator<<(std::ostream& out, const StructArray<T, Size>& arr) {
    for (const auto& value : arr) {
        out << value << ' ';
    }
    return out;
}

int main() {
    StructArray<int, 10> arr = { 0, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    std::cout << arr << '\n';

    for (int i = arr.size()-1; i >= 0; --i) {
        arr[i] = i;
    }
    std::cout << arr << '\n';

    for (auto& value : arr) {
        value += 1;
    }
    std::cout << arr << '\n';
    std::cout << sum(arr) << '\n';

    std::cin.get();
    return 0;
}