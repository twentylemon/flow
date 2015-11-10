      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( set_diff_itr_comp )  
{
    using namespace flow;

    std::vector<int> vec = {};

    std::vector<int> ex = {};
    auto s = empty<int>() | set_diff(vec.begin(), vec.end(), square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    vec = { 1, 2, 3 };
    ex = {};
    s = from({ 1, 2 }) | set_diff(vec.begin(), vec.end(), square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = {};
    s = from({ 1, 2 }) | set_diff(vec.begin(), vec.begin() + 2, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    vec = { 1, 1, 2 };
    ex = { 2 };
    s = from({ 1, 2, 2 }) | set_diff(vec.begin(), vec.end(), square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    vec = { 1, 3, 5, 7 };
    ex = { 5, 7 };
    s = vec | set_diff(vec.begin(), vec.begin() + 2, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    vec = { 1, -2, 5 };
    ex = { -4, 5 };
    s = from({ 2, -4, 5 }) | set_diff(vec.begin(), vec.begin() + 2, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    vec = { -1, 2, -3 };
    ex = { 1 };
    s = from({ 1, 1, -2, 3 }) | set_diff(vec.begin(), vec.end(), square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1 };
    s = from({ 1, -2, 3 }) | set_diff(vec.begin() + 1, vec.end(), square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    vec = {};
    ex = { 1, 2 };
    s = from({ 1, 2 }) | set_diff(vec.begin(), vec.end(), square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());
}

