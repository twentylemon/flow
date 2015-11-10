      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( set_union_list_comp )  
{
    using namespace flow;

    const std::vector<int> v1 = { 1, 3, 5, 7 };

    std::vector<int> ex = { 1, 2, 3, 4, 5, 6, 7, 8 };
    auto s = v1 | set_union({ 2, 4, 6, 8 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 1 };
    s = from({ 1, 1 }) | set_union({ 1 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 1, 2, 2 };
    s = from({ 1, 1, 2 }) | set_union({ 1, 2, 2 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    const std::vector<int> v2 = { 1, 2, 3 };
    ex = { 1, 2, 3, 4, 5, 6 };
    s = v2 | set_union({ 4, 5, 6 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 2, 3 };
    s = v2 | set_union({ 1, 2, 3 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 2, 3, 4, 5 };
    s = from({ 1, 3, 5 }) | set_union({ 1, 2, 3, 4 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 2, 3 };
    s = empty<const int>() | set_union({ 1, 2, 3 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { -1, 2, -3, -4, 5 };
    s = from({ 2, -4, 5 }) | set_union({ -1, -3 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, -2, 3 };
    s = from({ 1, -2, 3 }) | set_union({ -1, 2, -3 }, square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());
}

