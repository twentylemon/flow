      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( merge_list_comp )  
{
    using namespace flow;

    std::vector<int> ex = { -1, 2, 2, -3, -4, 5 };
    auto s = from({ 2, -4, 5 }) | merge({ -1, 2, -3 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, -1, 1, -2, 2, 3, -3 };
    s = from({ 1, -1, -2, 3 }) | merge({ 1, 2, -3 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 2, 3, 4, 5, 6, 7, 8 };
    s = from({ 1, 3, 5, 7 }) | merge({ 2, 4, 6, 8 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());
}

