// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#ifndef STDAFX_H
#define STDAFX_H

#ifdef _WIN32
#include "targetver.h"
#endif

#include <stdio.h>

// TODO: reference additional headers your program requires here
#include <sstream>
#include <flow.h>

#define DO_OP1(cls) \
    namespace std { \
        template <typename T> \
        std::ostream& operator<<(std::ostream& out, const cls<T>& container) { \
            return container | flow::dump(); \
        } \
    }

#define DO_OP2(cls) \
    namespace std { \
        template <typename T, typename C> \
        std::ostream& operator<<(std::ostream& out, const cls<T,C>& container) { \
            return container | flow::dump(); \
        } \
    }

#define DO_OP3(cls) \
    namespace std { \
        template <typename T, typename C, typename P> \
        std::ostream& operator<<(std::ostream& out, const cls<T,C,P>& container) { \
            return container | flow::dump(); \
        } \
    }

#define DO_OP4(cls) \
    namespace std { \
        template <typename T, typename C, typename P, typename A> \
        std::ostream& operator<<(std::ostream& out, const cls<T,C,P,A>& container) { \
            return container | flow::dump(); \
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

const int DEFAULT_OTHER = 0;

struct Widget {
    Widget(int i) : _value(i), _other(DEFAULT_OTHER) { }
    Widget(int i, int j) : _value(i), _other(j) { }
    void set_value(int value) { _value = value; }
    void clear() { _value = 0; }
    bool is_even() const { return _value % 2 == 0; }
    int& get_other_ref() { return _other; }
    bool operator==(const Widget& rhs) const { return _value == rhs._value; }
    bool operator!=(const Widget& rhs) const { return _value != rhs._value; }
    bool operator<(const Widget& rhs) const { return _value < rhs._value; }
    bool operator<=(const Widget& rhs) const { return _value <= rhs._value; }
    bool operator>(const Widget& rhs) const { return _value > rhs._value; }
    bool operator>=(const Widget& rhs) const { return _value >= rhs._value; }
    Widget& operator++() { ++_value; return *this; }

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

//Adding required boost header
#ifdef _WIN32
#include <boost/test/unit_test.hpp>
#else
#include <boost/test/included/unit_test.hpp>
#endif
#endif
