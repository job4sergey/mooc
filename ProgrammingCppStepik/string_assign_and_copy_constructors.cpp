#include <cstddef> // size_t
#include <iostream>

using namespace std;

struct String {
	String(const char *str = "");
	String(size_t n, char c);
	~String();

	String(const String &other) {
        char* t = new char[other.size+1];
        for (int i = 0; i < other.size; i++) {
            t[i] = other.str[i];
        }
        t[other.size] = '\0';
        this->str = t;
        this->size = other.size;
    }

    String &operator=(const String &other) {
        if (this != &other) {
            char* t = new char[other.size+1];
            for (int i = 0; i < other.size; i++) {
            t[i] = other.str[i];
            }
            t[other.size] = '\0';
            delete[] this->str;
            this->str = t;
            this->size = other.size;
        }
        return *this;
    }

	void append(const String &other);

	size_t size;
	char *str;
};

int main() {
    int a = 10;
    int& la = a;
    cout << &la << endl;
    return 0;
}