
#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <functional>

#include <flow.h>
using namespace flow;

#include <boost/test/unit_test.hpp>

#define DO_OP(cls) \
    namespace std { \
        template <typename T> \
        std::ostream& operator<<(std::ostream& out, const cls<T>& container) { \
            return container | dump(); \
        } \
    }

DO_OP(std::deque);
DO_OP(std::vector);
DO_OP(std::list);
DO_OP(std::forward_list);
DO_OP(std::set);
DO_OP(std::multiset);
DO_OP(std::unordered_set);
DO_OP(std::unordered_multiset);
namespace std {
    template <typename T, typename U>
    std::ostream& operator<<(std::ostream& out, const std::pair<T, U>& pair) {
        return out << '(' << pair.first << ", " << pair.second << ')';
    }
}

inline bool is_even(int val) {
    return val % 2 == 0;
}

inline int negate(int val) {
    return -val;
}

inline bool square_less(int lhs, int rhs) {
    return lhs*lhs < rhs*rhs;
}

struct Widget {
    Widget(int i) : _value(i), _other(0) { }
    void set_value(int value) { _value = value; }
    void clear() { _value = 0; }
    bool is_even() const { return _value % 2 == 0; }
    bool operator==(const Widget& rhs) const { return _value == rhs._value; }
    bool operator!=(const Widget& rhs) const { return _value != rhs._value; }
    bool operator<(const Widget& rhs) const { return _value < rhs._value; }
    bool operator<=(const Widget& rhs) const { return _value <= rhs._value; }
    bool operator>(const Widget& rhs) const { return _value > rhs._value; }
    bool operator>=(const Widget& rhs) const { return _value >= rhs._value; }

    void process() const { _other = _value; }
    int _value;
    mutable int _other;
};

inline std::ostream& operator<<(std::ostream& out, const Widget& widget) {
    return out << widget._value;
}

extern std::initializer_list<int> init_list;

#endif
