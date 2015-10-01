
#include "../test.h"

BOOST_AUTO_TEST_CASE(drop_while_func) {
    std::vector<int> vec1 = { 3, 4, 5, 6 };
    auto vec2 = from({ 1, 2, 3, 4, 5, 6 }) | drop_while(less_3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = empty<int>() | drop_while(less_3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = from({ 1, 2, 1, 2, 1 }) | drop_while(less_3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { 4, 5, 4, 5, 4 };
    vec2 = from({ 4, 5, 4, 5, 4 }) | drop_while(less_3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { 3, 2, 2 };
    vec2 = from({ 2, 3, 2, 2 }) | drop_while(less_3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
}

BOOST_AUTO_TEST_CASE(drop_while_bool) {
    std::vector<bool> vec1 = { false, false };
    auto vec2 = from({ true, true, false, false }) | drop_while() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = empty<bool>() | drop_while() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = from({ true, true }) | drop_while() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { false, false, false };
    vec2 = from({ false, false, false }) | drop_while() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { false, true };
    vec2 = from({ true, false, true }) | drop_while() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
}

BOOST_AUTO_TEST_CASE(drop_while_member) {
    std::vector<Widget> vec1 = { Widget(1), Widget(3) };
    auto vec2 = from({ Widget(2), Widget(1), Widget(3) }) | drop_while(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = empty<Widget>() | drop_while(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { };
    vec2 = from({ Widget(2), Widget(2) }) | drop_while(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { Widget(1), Widget(2) };
    vec2 = from({ Widget(1), Widget(2) }) | drop_while(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
}

BOOST_AUTO_TEST_CASE(drop_while_member_const) {
    std::vector<Widget> vec1 = { Widget(1), Widget(3) };
    auto vec2 = from({ Widget(2), Widget(1), Widget(3) }) | drop_while(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    const auto vec3 = vec1;
    vec2 = vec3 | drop_while(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = from({ Widget(2), Widget(2) }) | drop_while(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { Widget(1), Widget(2) };
    vec2 = from({ Widget(1), Widget(2) }) | drop_while(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
}
