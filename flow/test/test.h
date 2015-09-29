
#ifndef TEST_H
#define TEST_H

#include <iostream>

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

inline bool is_even(int val) {
    return val % 2 == 0;
}

struct Member {
    Member(int i) : _value(i) { }
    bool is_even() const { return _value % 2 == 0; }
    int _value;
};

extern std::initializer_list<int> init_list;

#endif
