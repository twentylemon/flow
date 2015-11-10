      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( execute_t )  
{
    using namespace flow;

    std::vector<Widget> vec = { Widget(0), Widget(0) };
    auto orig = vec;

    vec | zip(iota(1), [](Widget& w, int i) { w._other = i; return i; });
    for (std::size_t i = 0; i < vec.size(); ++i) {
        BOOST_CHECK_EQUAL(vec[i]._other, DEFAULT_OTHER);
    }

    std::vector<Widget> ex = { Widget(1), Widget(2) };
    vec | zip(iota(1), [](Widget& w, int i) { w._other = i; return i; }) | execute();
    for (std::size_t i = 0; i < vec.size(); ++i) {
        BOOST_CHECK_EQUAL(vec[i]._other, i + 1);
    }
}

