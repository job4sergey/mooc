#include <cstddef>

template <typename T>
struct Array
{
    explicit Array(size_t size, const T& value = T()) {
        size_ = size;
        data_ = (T*) new char[size_ * sizeof(T)];
        for (size_t i = 0; i < size_; i++) {
            new (data_ + i) T(value); 
        }
    }

    Array() {
        size_ = 0;
        data_ = 0;
    }
    
    Array(const Array& other) {
        size_ = other.size();
        data_ = (T*) new char[size_ * sizeof(T)];
        for (size_t i = 0; i < size_; i++) {
            new (data_ + i) T(other[i]); 
        }
    }
    
    ~Array() {
        this->free();
    }
    
    Array& operator=(const Array& other) {
        if (this != &other) {
            this->free();
            size_ = other.size();
            data_ = static_cast<T*>(operator new[] (size_ * sizeof(T)));
            for (size_t i = 0; i < size_; i++) {
                new (data_ + i) T(other[i]); 
            }
        }
        return *this;
    }

    size_t size() const { return size_; }
    T& operator[](size_t i) { return data_[i]; }
    const T& operator[](size_t i) const { return data_[i]; }

    void free() {
        for (size_t i = 0; i != size_; ++i) {
            data_[i].~T();
        }
        delete[] (char*) data_;
    }

private:
    size_t size_;
    T* data_;
};

int main() {
    return 0;
}