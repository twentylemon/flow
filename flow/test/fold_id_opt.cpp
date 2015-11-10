      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( fold_id_opt )  
{
    using namespace flow;

    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | fold_id(std::plus<int>(), [](int i) { return 2 * i; }).value(), 7);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | fold_id([](std::pair<int, int> p, int i) {
        p.first = std::min(p.first, i); // p is the min/max
        p.second = std::max(p.second, i);
        return p;
    }, [](int i) { return std::make_pair(i, i); }).value(), std::make_pair(1, 3));

    auto i = empty<int>() | fold_id(std::plus<int>(), [](int i) { return 4; });
    BOOST_CHECK(!i);
    BOOST_CHECK_EQUAL(i.value_or(3), 3);
}

