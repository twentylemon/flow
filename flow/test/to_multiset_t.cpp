      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( to_multiset_t )  
{
    using namespace flow;

    auto init_list = { 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, -1, -2, -3, -4, -5, -6 };

    std::multiset<int> em;
    auto tem = empty<int>() | to_multiset();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());

    std::multiset<int> con = init_list;
    auto res = from(init_list) | to_multiset();
    BOOST_CHECK_EQUAL_COLLECTIONS(con.begin(), con.end(), res.begin(), res.end());

    std::multiset<int, bool(*)(int, int)> de(square_less);   // ctor by init_list changes order
    std::copy(init_list.begin(), init_list.end(), std::inserter(de, de.end()));
    auto de2 = from(init_list) | to_multiset(square_less);
    BOOST_CHECK_EQUAL_COLLECTIONS(de.begin(), de.end(), de2.begin(), de2.end());

    std::multiset<int, bool(*)(int, int), std::allocator<int>> de3(square_less, std::allocator<int>());
    std::copy(init_list.begin(), init_list.end(), std::inserter(de3, de3.end()));
    auto de4 = from(init_list) | to_multiset(square_less, std::allocator<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(de3.begin(), de3.end(), de4.begin(), de4.end());
}

