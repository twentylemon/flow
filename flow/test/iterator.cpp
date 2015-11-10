      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( iterator )  
{
    using namespace flow;

    std::vector<int> vec;
    std::vector<int> ex = { 1, 2, 3, 4 };
    auto s = from({ 1, 2, 3, 4 });
    std::copy(s.begin(), s.end(), std::back_inserter(vec));
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), vec.begin(), vec.end());

    auto s2 = iota(1) | filter(is_even) | limit(10);
    ex = { 2, 4, 6, 8, 10, 12, 14, 16, 18, 20 };
    BOOST_CHECK_EQUAL_COLLECTIONS(s2.begin(), s2.end(), ex.begin(), ex.end());

    auto s3 = empty<int>();
    ex = {};
    BOOST_CHECK_EQUAL_COLLECTIONS(s3.begin(), s3.end(), ex.begin(), ex.end());

    vec = { 1, 2, 3, 4 };
    ex = { 1, 2, 3, 4 };
    auto s4 = from(vec);
    BOOST_CHECK_EQUAL_COLLECTIONS(s4.begin(), s4.end(), ex.begin(), ex.end());

    vec = {};
    auto s5 = from({ 1, 2, 3, 4 });
    for (auto it = s5.begin(), end = s5.end(); it != end; it++) {
        vec.push_back(*it);
    }
    BOOST_CHECK_EQUAL_COLLECTIONS(vec.begin(), vec.end(), ex.begin(), ex.end());

    vec = {};
    auto s6 = from({ 1, 2, 3, 4 });
    for (auto it = s6.begin(), end = s6.end(); it != end; ++it) {
        vec.push_back(*it);
    }
    BOOST_CHECK_EQUAL_COLLECTIONS(vec.begin(), vec.end(), ex.begin(), ex.end());

    auto s7 = iota(0);
    int lim = 10000;
    int su = 0;
    for (auto& i : s7) {
        su += i;
        if (--lim == 0) {
            break;
        }
    }
    BOOST_CHECK_EQUAL(iota(0) | limit(10000) | sum().value(), su);

    auto s8 = iota(0);
    BOOST_CHECK_EQUAL(*std::find(s8.begin(), s8.end(), 1000), 1000);
    BOOST_CHECK_EQUAL(*s8.begin(), 1001);

    auto s9 = range(0, 100);
    BOOST_CHECK(std::find(s9.begin(), s9.end(), -1) == s9.end());
}

