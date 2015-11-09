      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( merge_list_less )  
{
    using namespace flow;

    std::vector<int> ex = { 1, 2 };
    auto s = empty<const int>() | merge({ 1, 2 }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 2, 3, 4, 5, 6, 7, 8 };
    s = from({ 1, 3, 5, 7 }) | merge({ 2, 4, 6, 8 }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());
}

