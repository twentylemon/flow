      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( to_vector_t )  
{
    using namespace flow;

    auto init_list = { 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, -1, -2, -3, -4, -5, -6 };

    std::vector<int> em;
    auto tem = empty<int>() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());

    std::vector<int> con = init_list;
    auto res = from(init_list) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(con.begin(), con.end(), res.begin(), res.end());

    auto tem2 = empty<int>() | to_vector(std::allocator<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem2.begin(), tem2.end());

    std::vector<int, std::allocator<int>> de = init_list;
    auto de2 = from(init_list) | to_vector(std::allocator<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(con.begin(), con.end(), res.begin(), res.end());
}

