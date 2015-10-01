
#include "../test.h"

BOOST_AUTO_TEST_CASE(none_func) {
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | none(is_even), false);
    BOOST_CHECK_EQUAL(from({ 1, 3, 1 }) | none(is_even), true);
    BOOST_CHECK_EQUAL(empty<int>() | none(is_even), true);
}

BOOST_AUTO_TEST_CASE(none_bool) {
    BOOST_CHECK_EQUAL(from({ true, false }) | none(), false);
    BOOST_CHECK_EQUAL(from({ false, false, false }) | none(), true);
    BOOST_CHECK_EQUAL(empty<bool>() | none(), true);
}

BOOST_AUTO_TEST_CASE(none_member) {
    BOOST_CHECK_EQUAL(from({ Widget(1), Widget(2) }) | none(&Widget::is_even), false);
    BOOST_CHECK_EQUAL(from({ Widget(1), Widget(3) }) | none(&Widget::is_even), true);
}

BOOST_AUTO_TEST_CASE(none_member_const) {
    const std::vector<Widget> vec1 = { Widget(1), Widget(2) };
    const std::vector<Widget> vec2 = { Widget(1), Widget(3) };
    BOOST_CHECK_EQUAL(vec1 | none(&Widget::is_even), false);
    BOOST_CHECK_EQUAL(vec2 | none(&Widget::is_even), true);
}
