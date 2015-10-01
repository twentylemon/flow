
#include "../test.h"

BOOST_AUTO_TEST_CASE(any_func) {
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | any(is_even), true);
    BOOST_CHECK_EQUAL(from({ 1, 3, 5 }) | any(is_even), false);
    BOOST_CHECK_EQUAL(empty<int>() | any(is_even), false);
}

BOOST_AUTO_TEST_CASE(any_bool) {
    BOOST_CHECK_EQUAL(from({ true, false }) | any(), true);
    BOOST_CHECK_EQUAL(from({ false, false, false }) | any(), false);
    BOOST_CHECK_EQUAL(empty<bool>() | any(), false);
}

BOOST_AUTO_TEST_CASE(any_member) {
    BOOST_CHECK_EQUAL(from({ Widget(1), Widget(2) }) | any(&Widget::is_even), true);
    BOOST_CHECK_EQUAL(from({ Widget(1), Widget(3) }) | any(&Widget::is_even), false);
}

BOOST_AUTO_TEST_CASE(any_member_const) {
    const std::vector<Widget> vec1 = { Widget(1), Widget(2) };
    const std::vector<Widget> vec2 = { Widget(1), Widget(1) };
    BOOST_CHECK_EQUAL(vec1 | any(&Widget::is_even), true);
    BOOST_CHECK_EQUAL(vec2 | any(&Widget::is_even), false);
}
