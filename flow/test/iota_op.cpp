      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( iota_op )  
{
    using namespace flow;

    std::vector<int> ex = { 1, 2, 3 };
    auto s = iota(1) | limit(3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { -1, 0, 1, 2, 3 };
    s = iota(-1) | limit(5) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<Widget> ex2 = { Widget(1), Widget(2), Widget(3) };
    auto s2 = iota(Widget(1)) | limit(3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s2.begin(), s2.end(), ex2.begin(), ex2.end());

    BOOST_CHECK_EQUAL(iota(0) | nth(10).value(), 10);
}

