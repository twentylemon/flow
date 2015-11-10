      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( rcycle_move_container )  
{
    using namespace flow;

    std::vector<int> vec = { 1, 2, 3 };

    std::vector<int> ex = { 3, 2, 1, 3, 2 };
    auto s = rcycle_move(std::move(vec)) | limit(5) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<int> vec2 = { 1 };
    ex = { 1, 1, 1 };
    s = rcycle_move(std::move(vec2)) | limit(3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

