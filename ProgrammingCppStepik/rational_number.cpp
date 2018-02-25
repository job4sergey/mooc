#include <iostream>

using namespace std;

struct Rational
{
    Rational(int numerator = 0, int denominator = 1) : numerator_(numerator), denominator_(denominator) {};

    void add(Rational rational) {
        this->numerator_ = this->numerator_ * rational.denominator_ + rational.numerator_ * this->denominator_;
        this->denominator_ *= rational.denominator_;
    }
    void sub(Rational rational) {
        this->numerator_ = this->numerator_ * rational.denominator_ - rational.numerator_ * this->denominator_;
        this->denominator_ *= rational.denominator_;
    }
    // multiplication
    void mul(Rational rational) {
        this->numerator_ *= rational.numerator_;
        this->denominator_ *= rational.denominator_;
    }
    // division
    void div(Rational rational) {
        this->numerator_ *= rational.denominator_;
        this->denominator_ *= rational.numerator_;
    }

    void neg(){ 
        this->numerator_ = -(this->numerator_);
    }
    void inv() {};
    double to_double() const {
        return this->numerator_ / (double)this->denominator_;
    }

    // Operators override
    Rational& operator+=(Rational const& rational) {
        this->add(rational);
        return *this;
    }
    Rational& operator-=(Rational const& rational) {
        this->sub(rational);
        return *this;
    }
    Rational& operator*=(Rational const& rational) {
        this->mul(rational);
        return *this;
    }
    Rational& operator/=(Rational const& rational) {
        this->div(rational);
        return *this;
    }
    Rational operator+() const {return Rational(this->numerator_, this->denominator_);}
    Rational operator-() const {return Rational(-1*this->numerator_, this->denominator_);}

    friend bool operator==(Rational const& left, Rational const &right);
    friend bool operator<(Rational const& left, Rational const &right);
    
    operator double() const {
        return to_double();
    }

private:
    int numerator_;
    int denominator_;
};

// Cover with with integers instead of only rational.
// (a construct is OK with implicit casting int->Rational)
Rational operator+(Rational r1, Rational const& r2) {
    return r1 += r2;
}
Rational operator-(Rational r1, Rational const& r2) {
    return r1 -= r2;
}
Rational operator*(Rational r1, Rational const& r2) {
    return r1 *= r2;
}
Rational operator/(Rational r1, Rational const& r2) {
    return r1 /= r2;
}
bool operator==(Rational const& r1, Rational const& r2) {
    Rational r1m(r1.numerator_*r2.denominator_, r1.denominator_*r2.denominator_);
    Rational r2m(r2.numerator_*r1.denominator_, r2.denominator_*r1.denominator_);
    return (r1m.numerator_ == r2m.numerator_) && (r1m.denominator_ == r2m.denominator_);
}
bool operator<(Rational const& r1, Rational const& r2) {
    return r1.numerator_*r2.denominator_ < r2.numerator_*r1.denominator_;
}
bool operator!=(Rational const& r1, Rational const& r2) {
    return !(r1==r2);
}
bool operator>(Rational const& r1, Rational const& r2) {
    return r2<r1;
}
bool operator<=(Rational const& r1, Rational const& r2) {
    return !(r2<r1);
}
bool operator>=(Rational const& r1, Rational const& r2) {
    return !(r1<r2);
}


int main() {
    Rational r1(1, 2);
    Rational r2(2, 4);
    return 0;
}