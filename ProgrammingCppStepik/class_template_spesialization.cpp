#include <cstddef>
#include <iostream>

template <typename T, typename U>
struct SameType
{ static const bool value = false; };

template <typename T> 
struct SameType<T, T>
{ static const bool value = true; };

int main() {
    std::cout << SameType<int, int>::value << std::endl; 
    std::cout << SameType<int, int&>::value << std::endl;
    std::cout << SameType<int, const int>::value << std::endl;
}