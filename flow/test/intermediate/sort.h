
#include "../test.h"

BOOST_AUTO_TEST_CASE(sort_less) {
    std::vector<int> ex = { 1, 2, 3 };
    auto s = from({ 2, 3, 1 }) | sort() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = empty<int>() | sort() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1, 1, 2, 2, 3, 3 };
    s = from({ 2, 1, 2, 1, 3, 3 }) | sort() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

BOOST_AUTO_TEST_CASE(sort_comp) {
    std::vector<int> ex = { 1, 2, 3 };
    auto s = from({ 2, 3, 1 }) | sort(square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = empty<int>() | sort(square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

BOOST_AUTO_TEST_CASE(stable_sort_less) {
    std::vector<Widget> ex = { Widget(1), Widget(2), Widget(3) };
    auto s = from({ Widget(2), Widget(3), Widget(1) }) | stable_sort() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = empty<Widget>() | stable_sort() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { Widget(1, 0), Widget(1, 1), Widget(2, 0), Widget(2, 1) };
    s = from({ Widget(2, 0), Widget(1, 0), Widget(1, 1), Widget(2, 1) }) | stable_sort() | to_vector();
    BOOST_CHECK_EQUAL(ex.size(), s.size());
    for (std::size_t i = 0; i < s.size(); ++i) {
        BOOST_CHECK_EQUAL(s[i], ex[i]);
        BOOST_CHECK_EQUAL(s[i]._other, ex[i]._other);
    }
}

BOOST_AUTO_TEST_CASE(stable_sort_comp) {
    std::vector<Widget> ex = { Widget(1), Widget(2), Widget(3) };
    auto s = from({ Widget(2), Widget(3), Widget(1) }) | stable_sort(square_less_widget) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = empty<Widget>() | stable_sort(square_less_widget) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { Widget(1, 0), Widget(-1, 1), Widget(-2, 0), Widget(2, 1) };
    s = from({ Widget(-2, 0), Widget(1, 0), Widget(-1, 1), Widget(2, 1) }) | stable_sort(square_less_widget) | to_vector();
    BOOST_CHECK_EQUAL(ex.size(), s.size());
    for (std::size_t i = 0; i < s.size(); ++i) {
        BOOST_CHECK_EQUAL(s[i], ex[i]);
        BOOST_CHECK_EQUAL(s[i]._other, ex[i]._other);
    }
}
