
#include "../test.h"

BOOST_AUTO_TEST_CASE(filter_func) {
    std::vector<int> vec1 = { 2, 4, 6 };
    auto vec2 = from({ 1, 2, 3, 4, 5, 6 }) | filter(is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = empty<int>() | filter(is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = from({ 1, 3, 1, 5 }) | filter(is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { 2, 2, 2 };
    vec2 = from({ 2, 2, 2 }) | filter(is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
    
    std::vector<Widget> w = { Widget(1), Widget(2), Widget(3) };
    std::vector<Widget> ex = { Widget(1), Widget(3) };
    auto s = w | filter([](Widget& w){ return !w.is_even(); }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());
}

BOOST_AUTO_TEST_CASE(filter_bool) {
    std::vector<bool> vec1 = { true, true };
    auto vec2 = from({ true, true, false, false }) | filter() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = empty<bool>() | filter() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { true, true };
    vec2 = from({ true, true }) | filter() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { };
    vec2 = from({ false, false, false }) | filter() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { true, true };
    vec2 = from({ true, false, true }) | filter() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
}

BOOST_AUTO_TEST_CASE(filter_member) {
    std::vector<Widget> f1 = { Widget(2), Widget(1), Widget(3) };
    std::vector<Widget> vec1 = { Widget(2) };
    auto vec2 = f1 | filter(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = empty<Widget>() | filter(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    f1 = { Widget(2), Widget(2) };
    vec1 = { Widget(2), Widget(2) };
    vec2 = f1 | filter(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    f1 = { Widget(1), Widget(1) };
    vec1 = {};
    vec2 = f1 | filter(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
}

BOOST_AUTO_TEST_CASE(filter_member_const) {
    std::vector<Widget> vec1 = { Widget(2) };
    auto vec2 = from({ Widget(2), Widget(1), Widget(3) }) | filter(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = empty<const Widget>() | filter(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { Widget(2), Widget(2) };
    vec2 = from({ Widget(2), Widget(2) }) | filter(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = from({ Widget(1), Widget(1) }) | filter(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
}
