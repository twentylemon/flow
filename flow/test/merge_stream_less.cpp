      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( merge_stream_less )  
{
    using namespace flow;

    std::vector<int> ex = {};
    auto s = empty<int>() | merge(empty<int>()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 2, 2, 3, 4, 4, 5, 6 };
    s = from({ 1, 2, 3, 4, 5 }) | merge(from({ 2, 3, 4, 5, 6 }) | filter(is_even)) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 2, 3, 4, 5, 6, 7, 8 };
    s = from({ 1, 3, 5, 7 }) | merge(from({ 2, 4, 6, 8 })) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = { 1, 2, 3 };
    s = from({ 1, 2, 3 }) | merge(empty<int>()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());
}

