      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( zip_list_default )  
{
    using namespace flow;

    std::vector<int> left = { 1, 2, 3 };

    std::vector<std::tuple<int, int>> ex = { std::make_tuple(1,4), std::make_tuple(2,5), std::make_tuple(3,6) };
    auto s = left | zip({ 4, 5, 6 }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<std::tuple<int, int, int>> ex2 = { std::make_tuple(1, 4, 1), std::make_tuple(2, 5, 2), std::make_tuple(3, 6, 3) };
    auto s2 = left | zip({ 4, 5, 6 }) | zip({ 1, 2, 3 }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s2.begin(), s2.end(), ex2.begin(), ex2.end());
}

