      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( set_diff_container_less )  
{
    using namespace flow;

    std::vector<int> vec = {};

    std::vector<int> ex = {};
    auto s = empty<int>() | set_diff(vec) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    vec = { 1, 2, 3 };
    ex = {};
    s = from({ 1, 2 }) | set_diff(vec) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = {};
    s = vec | set_diff(vec) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    vec = { 1, 1, 2 };
    ex = { 2 };
    s = from({ 1, 2, 2 }) | set_diff(vec) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    vec = { 1, 3, 5, 7 };
    ex = {};
    s = from({ 1, 3 }) | set_diff(vec) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    vec = {};
    ex = { 1, 2 };
    s = from({ 1, 2 }) | set_diff(vec) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());
}

