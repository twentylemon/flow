
#ifndef LARGE_CLASS_H
#define LARGE_CLASS_H

#include <array>
#include <iostream>

class LargeClass
{
public:
    LargeClass() : value(0) { }
    LargeClass(int v) : value(v) { }
    int get_value() const {
        return value;
    }
    void set_value(int v) { value = v; }
    bool operator<(const LargeClass& rhs) const { return value < rhs.value; }
    LargeClass operator*(const LargeClass& rhs) const { return LargeClass(value * rhs.value); }
    bool operator==(const LargeClass& rhs) const { return value == rhs.value; }
    LargeClass operator++() { return LargeClass(value + 1); }
    std::string& get_name() { return name; }
    LargeClass operator/(int i) const { return LargeClass(value / i); }
    LargeClass operator%(int i) const { return LargeClass(value % i); }
    int value;
    std::string name;
    std::array<int, 500> arry;
};

std::ostream& operator<<(std::ostream& o, const LargeClass& w) {
    return o << w.value;
}
#endif
