      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( set_sym_diff_container_comp )  
{
    using namespace flow;

    std::vector<int> vec = {};

    std::vector<int> ex = {};
    auto s = empty<int>() | set_sym_diff(vec, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    vec = { 1, 2, 3 };
    ex = { 3 };
    s = from({ 1, 2 }) | set_sym_diff(vec, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = {};
    s = vec | set_sym_diff(vec, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    vec = { 1, 1, 2 };
    ex = { 1, 2 };
    s = from({ 1, 2, 2 }) | set_sym_diff(vec, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    vec = { 1, 3, 5, 7 };
    ex = { 5, 7 };
    s = from({ 1, 3 }) | set_sym_diff(vec, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    vec = { 1, -2 };
    ex = { 1, -4, 5 };
    s = from({ 2, -4, 5 }) | set_sym_diff(vec, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    vec = { -1, 2, -3 };
    ex = { 1 };
    s = from({ 1, 1, -2, 3 }) | set_sym_diff(vec, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());
}

