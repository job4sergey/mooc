struct ICloneable
{
	virtual ICloneable* clone() const = 0;
	virtual ~ICloneable() { }
};

template <typename T>
struct ValueHolder : ICloneable {
    ValueHolder(const T& value) : data_(value) {}
    
    ValueHolder* clone() const {
        ValueHolder* v = new ValueHolder(data_);
        return v;
    }

    T data_;
};

int main() {
    ValueHolder<int> h(1);
    return 0;
}