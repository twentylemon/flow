
#include "../test.h"

BOOST_AUTO_TEST_SUITE(flow_intermediate)

BOOST_AUTO_TEST_CASE(take_while_func) {
    std::vector<int> vec1 = { 1, 2 };
    auto vec2 = from({ 1, 2, 3, 4, 5, 6 }) | take_while(less_3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = empty<int>() | take_while(less_3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { 1, 2, 1, 2, 1 };
    vec2 = from({ 1, 2, 1, 2, 1 }) | take_while(less_3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = from({ 4, 5, 4, 5, 4 }) | take_while(less_3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { 2 };
    vec2 = from({ 2, 3, 2, 2 }) | take_while(less_3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
}

BOOST_AUTO_TEST_CASE(take_while_bool) {
    std::vector<bool> vec1 = { true, true };
    auto vec2 = from({ true, true, false, false }) | take_while() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = empty<bool>() | take_while() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { true, true };
    vec2 = from({ true, true }) | take_while() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { };
    vec2 = from({ false, false, false }) | take_while() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { true };
    vec2 = from({ true, false, true }) | take_while() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
}

BOOST_AUTO_TEST_CASE(take_while_member) {
    std::vector<Widget> vec1 = { Widget(2) };
    auto vec2 = from({ Widget(2), Widget(1), Widget(3) }) | take_while(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = empty<Widget>() | take_while(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { Widget(2), Widget(2) };
    vec2 = from({ Widget(2), Widget(2) }) | take_while(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = from({ Widget(1), Widget(2) }) | take_while(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
}

BOOST_AUTO_TEST_CASE(take_while_member_const) {
    std::vector<Widget> vec1 = { Widget(2) };
    auto vec2 = from({ Widget(2), Widget(1), Widget(3) }) | take_while(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    const auto vec3 = vec1;
    vec2 = vec3 | take_while(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { Widget(2), Widget(2) };
    vec2 = from({ Widget(2), Widget(2) }) | take_while(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = from({ Widget(1), Widget(2) }) | take_while(&Widget::is_even) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
}

BOOST_AUTO_TEST_SUITE_END()
