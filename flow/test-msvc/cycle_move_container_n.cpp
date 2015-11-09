      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( cycle_move_container_n )  
{
    using namespace flow;

    std::vector<int> vec = { 1, 2, 3 };

    std::vector<int> ex = { 1, 2, 3, 1, 2, 3 };
    auto s = cycle_move(std::move(vec), 2) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<int> vec2 = { 1 };
    ex = { 1, 1, 1 };
    s = cycle_move(std::move(vec2), 3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

