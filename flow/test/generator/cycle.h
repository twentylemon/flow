
#include "../test.h"

BOOST_AUTO_TEST_CASE(cycle_itr) {
    std::vector<int> vec = { 1, 2, 3 };

    std::vector<int> ex = { 1, 2, 3, 1, 2 };
    auto s = cycle(vec.begin(), vec.end()) | limit(5) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1, 1, 1 };
    s = cycle(vec.begin(), vec.begin() + 1) | limit(3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<Widget> w = { Widget(1), Widget(2) };
    std::vector<Widget> wex = { Widget(1), Widget(2), Widget(1) };
    auto sw = cycle(w.begin(), w.end()) | limit(3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(sw.begin(), sw.end(), wex.begin(), wex.end());
}

BOOST_AUTO_TEST_CASE(cycle_itr_n) {
    std::vector<int> vec = { 1, 2, 3 };

    std::vector<int> ex = { 1, 2, 3, 1, 2, 3 };
    auto s = cycle(vec.begin(), vec.end(), 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1, 1, 1 };
    s = cycle(vec.begin(), vec.begin() + 1, 3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

BOOST_AUTO_TEST_CASE(cycle_container) {
    std::vector<int> vec = { 1, 2, 3 };

    std::vector<int> ex = { 1, 2, 3, 1, 2 };
    auto s = cycle(vec) | limit(5) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    vec = { 1 };
    ex = { 1, 1, 1 };
    s = cycle(vec) | limit(3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<Widget> w = { Widget(1), Widget(2) };
    std::vector<Widget> wex = { Widget(1), Widget(2), Widget(1) };
    auto sw = cycle(w) | limit(3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(sw.begin(), sw.end(), wex.begin(), wex.end());
}

BOOST_AUTO_TEST_CASE(cycle_container_n) {
    std::vector<int> vec = { 1, 2, 3 };

    std::vector<int> ex = { 1, 2, 3, 1, 2, 3 };
    auto s = cycle(vec, 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    vec = { 1 };
    ex = { 1, 1, 1 };
    s = cycle(vec, 3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<Widget> w = { Widget(1), Widget(2) };
    std::vector<Widget> wex = { Widget(1), Widget(2), Widget(1), Widget(2) };
    auto sw = cycle(w, 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(sw.begin(), sw.end(), wex.begin(), wex.end());
}

BOOST_AUTO_TEST_CASE(cycle_list) {
    std::vector<int> ex = { 1, 2, 3, 1, 2 };
    auto s = cycle({ 1, 2, 3 }) | limit(5) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1, 1, 1 };
    s = cycle({ 1 }) | limit(3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<Widget> wex = { Widget(1), Widget(1), Widget(1), Widget(1) };
    auto sw = cycle({ Widget(1) }) | limit(4) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(sw.begin(), sw.end(), wex.begin(), wex.end());
}

BOOST_AUTO_TEST_CASE(cycle_list_n) {
    std::vector<int> ex = { 1, 2, 3, 1, 2, 3 };
    auto s = cycle({ 1, 2, 3 }, 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 1, 2, 1, 2, 1, 2 };
    s = cycle({ 1, 2 }, 3) | to_vector();

    std::vector<Widget> wex = { Widget(1), Widget(1), Widget(1), Widget(1) };
    auto sw = cycle({ Widget(1) }, 4) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(sw.begin(), sw.end(), wex.begin(), wex.end());
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

BOOST_AUTO_TEST_CASE(rcycle_container) {
    std::vector<int> vec = { 1, 2, 3 };

    std::vector<int> ex = { 3, 2, 1, 3, 2 };
    auto s = rcycle(vec) | limit(5) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    vec = { 1 };
    ex = { 1, 1, 1 };
    s = rcycle(vec) | limit(3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<Widget> w = { Widget(1), Widget(2) };
    std::vector<Widget> wex = { Widget(2), Widget(1), Widget(2) };
    auto sw = rcycle(w) | limit(3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(sw.begin(), sw.end(), wex.begin(), wex.end());
}

BOOST_AUTO_TEST_CASE(rcycle_container_n) {
    std::vector<int> vec = { 1, 2, 3 };

    std::vector<int> ex = { 3, 2, 1, 3, 2, 1 };
    auto s = rcycle(vec, 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    vec = { 1 };
    ex = { 1, 1, 1 };
    s = rcycle(vec, 3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<Widget> w = { Widget(1), Widget(2) };
    std::vector<Widget> wex = { Widget(2), Widget(1), Widget(2), Widget(1) };
    auto sw = rcycle(w, 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(sw.begin(), sw.end(), wex.begin(), wex.end());
}
