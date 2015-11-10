      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( to_group_t )  
{
    using namespace flow;

    std::vector<Widget> w = { Widget(1), Widget(2), Widget(3), Widget(4) };

    std::map<bool, std::vector<Widget>> ex = { { false,{ Widget(1), Widget(3) } },{ true,{ Widget(2), Widget(4) } } };
    auto s = w | to_group([](Widget& w) { return w.is_even(); });
    for (auto& p : s) {
        BOOST_CHECK_EQUAL_COLLECTIONS(p.second.begin(), p.second.end(), ex[p.first].begin(), ex[p.first].end());
    }

    auto s2 = empty<int>() | to_group(is_even);
    BOOST_CHECK(s2.empty());

    std::map<int, std::vector<Widget>> ex3 = { { 1,{ Widget(1) } },{ 2,{ Widget(2) } },{ 3,{ Widget(3) } },{ 4,{ Widget(4) } } };
    auto s3 = w | to_group([](Widget& w) { return w._value; });
    for (auto& p : s3) {
        BOOST_CHECK_EQUAL_COLLECTIONS(p.second.begin(), p.second.end(), ex3[p.first].begin(), ex3[p.first].end());
    }

    std::map<int, std::vector<int>> ex4 = { { true,{ 2,4,6,8 } },{ false,{ 1,3,5,7 } } };
    auto s4 = closed_range(1, 8) | to_group(is_even);
    for (auto& p : s4) {
        BOOST_CHECK_EQUAL_COLLECTIONS(p.second.begin(), p.second.end(), ex4[p.first].begin(), ex4[p.first].end());
    }
}

