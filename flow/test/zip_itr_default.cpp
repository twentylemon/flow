      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( zip_itr_default )  
{
    using namespace flow;

    std::vector<int> left = { 1, 2, 3 };
    std::vector<int> right = { 4, 5, 6 };

    std::vector<std::tuple<int, int>> ex = { std::make_tuple(1,4), std::make_tuple(2,5), std::make_tuple(3,6) };
    auto s = left | zip(right.begin(), right.end()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { std::make_tuple(1,4), std::make_tuple(2,5) };
    s = left | zip(right.begin(), right.begin() + 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

