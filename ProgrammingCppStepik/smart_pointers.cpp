#include <iostream>
#include <string>

struct Expression;
struct Number;
struct BinaryOperation;

struct ScopedPtr
{
    explicit ScopedPtr(Expression *ptr = 0) {
        ptr_ = ptr;
    }
    ~ScopedPtr() {
        delete ptr_;
    }

    Expression* get() const { return ptr_; }
    Expression* release() {
        Expression* result = ptr_;
        ptr_ = NULL;
        return result;
    }
    void reset(Expression *ptr = 0) {
        delete ptr_;
        ptr_ = ptr;
    }

    Expression& operator*() const { return *ptr_; }
    Expression* operator->() const { return ptr_; }

private:
    // deny copy of ScopedPtr
    ScopedPtr(const ScopedPtr&);
    ScopedPtr& operator=(const ScopedPtr&);

    Expression *ptr_;
};

struct SharedPtr
{
    explicit SharedPtr(Expression *ptr = 0) {
		ptr_ = ptr;
        counter_ = ptr_ ? new int(1) : 0;
	}
	SharedPtr(const SharedPtr & obj) {
            ptr_ = obj.ptr_;
            counter_ = obj.counter_;
            if (ptr_){
                ++(*counter_);
            }
	}
    void decrement_counter(){
        if (counter_ && ptr_ && !--(*counter_)) {
            delete ptr_;
            delete counter_;
            counter_ = 0;
        }
    }
	void reset(Expression *ptr = 0) {
        if (ptr_ != ptr) {
            decrement_counter();
            ptr_ = ptr;
            if (ptr) {
                counter_ = new int(0);
                if (ptr_) {
                    ++(*counter_);
                }
            }
        }
	}
	SharedPtr& operator=(const SharedPtr & obj) {
        if (this != &obj){
            decrement_counter();
            ptr_ = obj.ptr_;
            counter_ = obj.counter_;
            if (obj.ptr_) {
                ++(*counter_);
            }
        }
		return *this;
	}
	Expression& operator*() const { return *ptr_; }
	Expression* operator->() const {return ptr_; }
    Expression* get() const { return ptr_;}
	int count() const {
        if (counter_) return *counter_;
        return 0;
	}
	~SharedPtr(){
        decrement_counter();
	}

private:
    Expression *ptr_;
    int *counter_;
};

int main() {
    return 0;
}