
#include "../test.h"

BOOST_AUTO_TEST_CASE(iota_noinc) {
    std::vector<int> ex = { 1, 2, 3 };
    auto s = iota(1) | limit(3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { -1, 0, 1, 2, 3 };
    s = iota(-1) | limit(5) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<Widget> ex2 = { Widget(1), Widget(2), Widget(3) };
    auto s2 = iota(Widget(1)) | limit(3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s2.begin(), s2.end(), ex2.begin(), ex2.end());
}

BOOST_AUTO_TEST_CASE(iota_inc) {
    std::vector<int> ex = { 1, 3, 5 };
    auto s = iota(1, 2) | limit(3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { -1, 1, 3 };
    s = iota(-1, 2) | limit(3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 8, 7, 6, 5, 4, 3 };
    s = iota(8, -1) | limit(6) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}
