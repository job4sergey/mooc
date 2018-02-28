#include <cstddef>

template <typename T>
struct Array
{
    // Constructor
    explicit Array(size_t size = 0, const T& value = T()) : arrSize(size), data_(new T[size]) {
        for (size_t i = 0; i < size; ++i) {
            data_[i] = value;
        }
    }
    // Copy constructor
    Array(const Array& other) : arrSize(other.arrSize), data_(new T[other.arrSize]) {
        for (size_t i = 0; i < arrSize; ++i) {
            data_[i] = other.data_[i];
        }
    }
    ~Array() { delete[] data_; }
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data_;
            arrSize = other.size();
            data_ = new T[arrSize];
            for (size_t i = 0; i < other.size(); ++i) {
                data_[i] = other.data_[i];
            }
        }
        return *this;
    }
    size_t size() const { return arrSize; }
    T& operator[](size_t i) { return data_[i]; }
    const T& operator[](size_t i) const { return data_[i]; }

private:
    size_t arrSize;
    T* data_;
};

int main() {
    return 0;
}