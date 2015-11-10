      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( to_deque_t )  
{
    using namespace flow;

    auto init_list = { 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, -1, -2, -3, -4, -5, -6 };

    std::deque<int> em;
    auto tem = empty<int>() | to_deque();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());

    std::deque<int> con = init_list;
    auto res = from(init_list) | to_deque();
    BOOST_CHECK_EQUAL_COLLECTIONS(con.begin(), con.end(), res.begin(), res.end());

    auto tem2 = empty<int>() | to_deque(std::allocator<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem2.begin(), tem2.end());

    std::deque<int, std::allocator<int>> de = init_list;
    auto de2 = from(init_list) | to_deque(std::allocator<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(de.begin(), de.end(), de2.begin(), de2.end());
}

