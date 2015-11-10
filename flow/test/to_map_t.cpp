      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( to_map_t )  
{
    using namespace flow;

    std::map<int, std::size_t> em;
    auto tem = empty<int>() | to_map();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());

    std::vector<int> vec = { 1, 2, 3 };
    std::map<int, std::size_t> ex = { { 1, 1 },{ 2, 1 },{ 3, 1 } };
    auto s = vec | to_map();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    vec = { 1, 2, 2, 3, 3, 3 };
    ex = { { 1, 1 },{ 2, 2 },{ 3, 3 } };
    s = vec | to_map();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    s = closed_range(1, 3) | flat_map([](int i) { return repeat(i, i); }) | to_map();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::map<int, std::size_t, bool(*)(int, int)> ex2(square_less);
    ex2 = { { 1, 1 },{ -2, 1 } };
    vec = { -2, 1 };
    auto s2 = vec | to_map(square_less);
    BOOST_CHECK_EQUAL_COLLECTIONS(s2.begin(), s2.end(), ex2.begin(), ex2.end());

    std::map<int, std::size_t, bool(*)(int, int), std::allocator<std::pair<const int, std::size_t>>> ex3(square_less, std::allocator<std::pair<const int, std::size_t>>());
    ex3 = { { 1, 1 },{ -2, 1 } };
    auto s3 = vec | to_map(square_less, std::allocator<std::pair<const int, std::size_t>>());
    BOOST_CHECK_EQUAL_COLLECTIONS(s3.begin(), s3.end(), ex3.begin(), ex3.end());
}

