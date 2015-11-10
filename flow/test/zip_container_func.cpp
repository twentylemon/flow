      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( zip_container_func )  
{
    using namespace flow;

    std::vector<int> left = { 1, 2, 3 };
    std::vector<int> right = { 4, 5, 6 };

    std::vector<int> ex = { 5, 7, 9 };
    auto s = left | zip(right, std::plus<int>()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 4, 10, 18 };
    s = left | zip(right, std::multiplies<int>()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = {};
    s = empty<int>() | zip(left, std::plus<int>()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    s = left | zip(empty<int>(), std::plus<int>()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

