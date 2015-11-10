      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( zip_stream_func )  
{
    using namespace flow;

    std::vector<int> left = { 1, 2, 3 };
    std::vector<int> right = { 4, 5, 6 };

    std::vector<int> ex = { 5, 7, 9 };
    auto s = left | zip(from(right), std::plus<int>()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 4, 10, 18 };
    s = left | zip(from(right), std::multiplies<int>()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<bool> ex2 = { true, true, true };
    auto s2 = left | zip(from({ 4, 5, 6 }), std::less<int>()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s2.begin(), s2.end(), ex2.begin(), ex2.end());

    ex = {};
    s = empty<int>() | zip(empty<int>(), std::plus<int>()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    s = empty<int>() | zip(from({ 1, 2, 3 }), std::plus<int>()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    s = left | zip(empty<int>(), std::plus<int>()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 2, 4, 6 };
    s = range(1, 1000) | zip(closed_range(1, 3), std::plus<int>()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

