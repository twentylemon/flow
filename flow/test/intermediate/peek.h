
#include "../test.h"

BOOST_AUTO_TEST_CASE(peek_func) {
    std::vector<int> vec;
    std::vector<int> ex = { 1, 2, 3 };
    ex | peek([&vec](int i) { vec.push_back(i); }) | execute();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), vec.begin(), vec.end());

    vec = {};
    std::vector<int> ex2 = {};
    ex | peek([&vec](int i) { vec.push_back(i); }); // lazy; no items should be pushed
    BOOST_CHECK_EQUAL_COLLECTIONS(ex2.begin(), ex2.end(), vec.begin(), vec.end());
}

BOOST_AUTO_TEST_CASE(peek_member) {
    std::vector<Widget> vec = { Widget(1), Widget(2) };
    std::vector<Widget> ex = { Widget(0), Widget(0) };
    vec | peek(&Widget::clear) | execute();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), vec.begin(), vec.end());

    vec = { Widget(1), Widget(2) };
    ex = { Widget(1), Widget(2) };
    vec | peek(&Widget::clear);
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), vec.begin(), vec.end());
}

BOOST_AUTO_TEST_CASE(peek_member_const) {
    std::vector<Widget> vec = { Widget(1), Widget(2) };
    vec | peek(&Widget::process) | execute();
    for (Widget& w : vec) {
        BOOST_CHECK_EQUAL(w._other, w._value);
    }

    vec = { Widget(1), Widget(2) };
    vec | peek(&Widget::process);
    for (Widget& w : vec) {
        BOOST_CHECK_EQUAL(w._other, DEFAULT_OTHER);
    }
}
