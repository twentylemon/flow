      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( set_intersect_list_comp )  
{
    using namespace flow;

    std::vector<int> v1 = { 1, 3, 5, 7 };
    std::vector<int> v2 = { 1, 2, 3, 4 };

    std::vector<int> ex = { 1, 3 };
    auto s = v1 | set_intersect({ 1, 2, 3, 4 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 2 };
    s = from({ 1, 1, 2 }) | set_intersect({ 1, 2, 2 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 3, 5, 7 };
    s = v1 | set_intersect({ 1, 3, 5, 7 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 3 };
    s = v1 | set_intersect({ 1, 3 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = {};
    s = empty<int>() | set_intersect({ 1, 3, 5, 7 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = range(1, 3) | to_vector();
    s = range(1, 3) | set_intersect({ 1, 2, 3 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    s = closed_range(1, 3) | set_intersect({ 1, 2 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 0, -1, 1, -2 };
    s = range(-2, 2) | stable_sort(square_less) | set_intersect({ 0, -1, 1, -2, 2 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    s = closed_range(-2, 2) | stable_sort(square_less) | set_intersect({ 0, -1, 1, -2 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());
}

