
#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <functional>

#include <flow.h>
using namespace flow;

#define BOOST_TEST_MODULE flow_test
#include <boost/test/unit_test.hpp>

#define DO_OP1(cls) \
    namespace std { \
        template <typename T> \
        std::ostream& operator<<(std::ostream& out, const cls<T>& container) { \
            return container | dump(); \
        } \
    }

#define DO_OP2(cls) \
    namespace std { \
        template <typename T, typename C> \
        std::ostream& operator<<(std::ostream& out, const cls<T,C>& container) { \
            return container | dump(); \
        } \
    }

#define DO_OP3(cls) \
    namespace std { \
        template <typename T, typename C, typename P> \
        std::ostream& operator<<(std::ostream& out, const cls<T,C,P>& container) { \
            return container | dump(); \
        } \
    }

#define DO_OP4(cls) \
    namespace std { \
        template <typename T, typename C, typename P, typename A> \
        std::ostream& operator<<(std::ostream& out, const cls<T,C,P,A>& container) { \
            return container | dump(); \
        } \
    }

DO_OP1(std::deque);
DO_OP1(std::vector);
DO_OP1(std::list);
DO_OP1(std::forward_list);
DO_OP1(std::set);
DO_OP1(std::multiset);
DO_OP1(std::unordered_set);
DO_OP1(std::unordered_multiset);
DO_OP2(std::deque);
DO_OP2(std::vector);
DO_OP2(std::list);
DO_OP2(std::forward_list);
DO_OP2(std::set);
DO_OP2(std::multiset);
DO_OP2(std::unordered_set);
DO_OP2(std::unordered_multiset);
DO_OP3(std::set);
DO_OP3(std::multiset);
DO_OP3(std::unordered_set);
DO_OP3(std::unordered_multiset);
DO_OP4(std::unordered_set);
DO_OP4(std::unordered_multiset);
namespace std {
    template <typename T, typename U>
    std::ostream& operator<<(std::ostream& out, const std::pair<T, U>& pair) {
        return out << '(' << pair.first << ", " << pair.second << ')';
    }
}

inline bool is_even(int val) {
    return val % 2 == 0;
}

inline bool less_3(int val) {
    return val < 3;
}

inline int negate(int val) {
    return -val;
}

inline bool square_less(int lhs, int rhs) {
    return lhs*lhs < rhs*rhs;
}

struct Widget {
    static const int DEFAULT_OTHER = 0;
    Widget(int i) : _value(i), _other(DEFAULT_OTHER) { }
    Widget(int i, int j) : _value(i), _other(j) { }
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

inline bool square_less_widget(const Widget& lhs, const Widget& rhs) {
    return std::pow(lhs._value, 2) < std::pow(rhs._value, 2);
}

std::initializer_list<int> init_list = { 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, -1, -2, -3, -4, -5, -6 };

#endif
