#include <cstddef>
#include <iostream>

template<typename T, typename S>
void copy_n(T* target, S* source, size_t size) {
    for (size_t i = 0; i < size; i++) {
        target[i] = (T)source[i];
    }
}

int main() {
    int ints[] = {1, 2, 3, 4};
    double doubles[4] = {};
    copy_n(doubles, ints, 4);
    
    std::cout << doubles[3] << std::endl;
    return 0;
}