      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( to_unordered_multiset_t )  
{
    using namespace flow;

    auto init_list = { 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, -1, -2, -3, -4, -5, -6 };

    std::unordered_multiset<int> em;
    auto tem = empty<int>() | to_unordered_multiset();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());

    std::unordered_multiset<int> con;
    std::copy(init_list.begin(), init_list.end(), std::inserter(con, con.end()));
    auto res = from(init_list) | to_unordered_multiset();
    BOOST_CHECK_EQUAL_COLLECTIONS(con.begin(), con.end(), res.begin(), res.end());

    std::unordered_multiset<int, std::hash<int>> de(16, std::hash<int>());
    std::copy(init_list.begin(), init_list.end(), std::inserter(de, de.end()));
    auto de2 = from(init_list) | to_unordered_multiset(std::hash<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(de.begin(), de.end(), de2.begin(), de2.end());

    std::unordered_multiset<int, std::hash<int>, std::equal_to<int>> de3(16, std::hash<int>(), std::equal_to<int>());
    std::copy(init_list.begin(), init_list.end(), std::inserter(de3, de3.end()));
    auto de4 = from(init_list) | to_unordered_multiset(std::hash<int>(), std::equal_to<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(de3.begin(), de3.end(), de4.begin(), de4.end());

    std::unordered_multiset<int, std::hash<int>, std::equal_to<int>, std::allocator<int>> de5(16, std::hash<int>(), std::equal_to<int>(), std::allocator<int>());
    std::copy(init_list.begin(), init_list.end(), std::inserter(de5, de5.end()));
    auto de6 = from(init_list) | to_unordered_multiset(std::hash<int>(), std::equal_to<int>(), std::allocator<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(de5.begin(), de5.end(), de6.begin(), de6.end());
}

