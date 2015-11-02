
#ifndef DYNINT_H
#define DYNINT_H

#include <iostream>

class DynInt
{
public:
    DynInt() : _val(new int) { *_val = 0; }
    DynInt(int v) : _val(new int) { *_val = v; }
    DynInt(const DynInt& rhs) : _val(new int) { *_val = *rhs; }
    DynInt(DynInt&& rhs) : _val(new int) { *_val = *rhs; }
    DynInt& operator=(const DynInt& rhs) { *_val = *rhs; return *this; }
    DynInt& operator=(DynInt&& rhs) { *_val = std::move(*rhs); return *this; }
    bool operator<(const DynInt& rhs) const { return *_val < *rhs._val; }
    bool operator<=(const DynInt& rhs) const { return *_val <= *rhs._val; }
    bool operator>(const DynInt& rhs) const { return *_val > *rhs._val; }
    bool operator>=(const DynInt& rhs) const { return *_val >= *rhs._val; }
    bool operator==(const DynInt& rhs) const { return *_val == *rhs._val; }
    bool operator!=(const DynInt& rhs) const { return *_val != *rhs._val; }
    DynInt& operator++() { ++*_val; return *this; }
    const int& operator*() const { return *_val; }
    int& operator*() { return *_val; }
    DynInt operator*(const DynInt& rhs) const { return DynInt(**this * *rhs); }
    DynInt operator+(const DynInt& rhs) const { return DynInt(**this + *rhs); }
    DynInt operator/(int i) const { return DynInt(**this / i); }
    DynInt operator%(int i) const { return DynInt(**this % i); }
    ~DynInt() { delete _val; }
    int* _val;
};

std::ostream& operator<<(std::ostream& out, const DynInt& i) {
    return out << *i;
}
#endif
