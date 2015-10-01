
#include "../test.h"

BOOST_AUTO_TEST_CASE(map_func) {
    std::vector<int> vec = { 1, 2, 3, 4, 5, 6 };

    std::vector<int> ex = { 2, 4, 6, 8, 10, 12 };
    auto s = vec | map([](int i) { return 2 * i; }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<double> ex2 = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };
    auto s2 = vec | map([](int i) { return 0.0; }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s2.begin(), s2.end(), ex2.begin(), ex2.end());

    ex2 = {};
    s2 = empty<int>() | map([](int i) { return 0.0; }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s2.begin(), s2.end(), ex2.begin(), ex2.end());
}

BOOST_AUTO_TEST_CASE(map_member) {
    std::vector<Widget> vec = { Widget(1), Widget(2) };
    
    std::vector<bool> ex = { false, true };
    auto s = vec | map(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

BOOST_AUTO_TEST_CASE(map_member_const) {
    std::vector<bool> ex = { false, true };
    auto s = from({ Widget(1), Widget(2) }) | map(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}
