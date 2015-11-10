      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( set_sym_diff_list_less )  
{
    using namespace flow;

    std::vector<int> ex = { 3 };
    auto s = from({ 1, 2 }) | set_sym_diff({ 1, 2, 3 }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = {};
    s = from({ 1, 2, 3 }) | set_sym_diff({ 1, 2, 3 }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 2 };
    s = from({ 1, 2, 2 }) | set_sym_diff({ 1, 1, 2 }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 5, 7 };
    s = from({ 1, 3 }) | set_sym_diff({ 1, 3, 5, 7 }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());
}

