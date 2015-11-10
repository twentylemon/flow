      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( fold_id_init )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | fold_id(std::plus<int>(), [](int i) { return 2 * i; }, 1), 8);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | fold_id([](std::pair<int, int> p, int i) {
        p.first = std::min(p.first, i); // p is the min/max
        p.second = std::max(p.second, i);
        return p;
    }, [](int i) { return std::make_pair(i, i); }, 0), std::make_pair(0, 3));   // 0 from init value, 3 is max

    BOOST_CHECK_EQUAL(empty<int>() | fold_id(std::plus<int>(), [](int i) { return 4; }, 0), 4);
}

