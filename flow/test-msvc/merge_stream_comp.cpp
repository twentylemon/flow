      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( merge_stream_comp )  
{
    using namespace flow;

    std::vector<int> ex = {};
    auto s = empty<int>() | merge(empty<int>(), square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 2, 2, 3, 4, 4, 5, 6 };
    s = from({ 1, 2, 3, 4, 5 }) | merge(from({ 2, 3, 4, 5, 6 }) | filter(is_even), square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 2, 3, 4, 5, 6, 7, 8 };
    s = from({ 1, 3, 5, 7 }) | merge(from({ 2, 4, 6, 8 }), square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { -1, 2, -3, -4, 5 };
    s = from({ 2, -4, 5 }) | merge(from({ -1, -3 }), square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, -1, 1, -2, 2, 3, -3 };
    s = from({ 1, -1, -2, 3 }) | merge(from({ 1, 2, -3 }), square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 2, 3 };
    s = from({ 1, 2, 3 }) | merge(empty<int>(), square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 2, 3 };
    s = from({ 1, 2, 3 }) | merge(empty<int>(), square_less) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());
}

