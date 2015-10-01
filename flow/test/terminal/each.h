
#include "../test.h"

BOOST_AUTO_TEST_CASE(each_func) {
    std::vector<int> vec = { 1, 2, 3 };
    std::vector<int> v;
    from({ 1, 2, 3 }) | each([&v](int i) { v.push_back(i); });
    BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(), v.end(), vec.begin(), vec.end());
}

BOOST_AUTO_TEST_CASE(each_member) {
    std::vector<Widget> zero = { Widget(0), Widget(0) };
    std::vector<Widget> vec = { Widget(1), Widget(2) };
    vec | each(&Widget::clear);
    BOOST_CHECK_EQUAL_COLLECTIONS(vec.begin(), vec.end(), zero.begin(), zero.end());
}

BOOST_AUTO_TEST_CASE(each_member_const) {
    const std::vector<Widget> vec = { Widget(1), Widget(2) };
    vec | each(&Widget::process);
    for (const Widget& w : vec) {
        BOOST_CHECK_EQUAL(w._other, w._value);
    }
}
