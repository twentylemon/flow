      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( set_sym_diff_list_comp )  
{
    using namespace flow;

    std::vector<int> ex = { 3 };
    auto s = from({ 1, 2 }) | set_sym_diff({ 1, 2, 3 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = {};
    s = from({ 1, 2, 3 }) | set_sym_diff({ 1, 2, 3 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 2 };
    s = from({ 1, 2, 2 }) | set_sym_diff({ 1, 1, 2 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 5, 7 };
    s = from({ 1, 3 }) | set_sym_diff({ 1, 3, 5, 7 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, -4, 5 };
    s = from({ 2, -4, 5 }) | set_sym_diff({ 1, -2 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1 };
    s = from({ 1, 1, -2, 3 }) | set_sym_diff({ -1, 2, -3 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 0, 1, 2, -3, 3 };
    s = from({ 1, 2 }) | set_sym_diff({ 0, -1, 1, -2, 2, -3, 3 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());
}

