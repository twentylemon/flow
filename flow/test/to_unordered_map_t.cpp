      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( to_unordered_map_t )  
{
    using namespace flow;

    std::unordered_map<int, std::size_t> em;
    auto tem = empty<int>() | to_unordered_map();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());

    std::initializer_list<std::pair<const int, std::size_t>> list = { { 1, 1 },{ 2, 2 },{ 3, 1 },{ 4, 3 } };
    std::vector<int> f = { 1, 2, 2, 3, 4, 4, 4 };

    std::unordered_map<int, std::size_t> con = list;
    auto res = from(f) | to_unordered_map();
    for (auto& p : con) {
        BOOST_CHECK_EQUAL(p, *res.find(p.first));
    }

    std::unordered_map<int, std::size_t, std::hash<int>> de(16, std::hash<int>());
    de = list;
    auto de2 = from(f) | to_unordered_map(std::hash<int>());
    for (auto& p : de) {
        BOOST_CHECK_EQUAL(p, *de2.find(p.first));
    }

    std::unordered_map<int, std::size_t, std::hash<int>, std::equal_to<int>> de3(16, std::hash<int>(), std::equal_to<int>());
    de3 = list;
    auto de4 = from(f) | to_unordered_map(std::hash<int>(), std::equal_to<int>());
    for (auto& p : de3) {
        BOOST_CHECK_EQUAL(p, *de4.find(p.first));
    }

    std::unordered_map<int, std::size_t, std::hash<int>, std::equal_to<int>, std::allocator<std::pair<const int, std::size_t>>> de5(16, std::hash<int>(), std::equal_to<int>(), std::allocator<std::pair<const int, std::size_t>>());
    de5 = list;
    auto de6 = from(f) | to_unordered_map(std::hash<int>(), std::equal_to<int>(), std::allocator<std::pair<const int, std::size_t>>());
    for (auto& p : de5) {
        BOOST_CHECK_EQUAL(p, *de6.find(p.first));
    }
}

