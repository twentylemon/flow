
#include "../test.h"

BOOST_AUTO_TEST_CASE(execute_t) {
    std::vector<Widget> vec = { Widget(0), Widget(0) };
    auto orig = vec;

    vec | zip(iota(1), [](Widget& w, int i) { w._value = i; return i; });
    BOOST_CHECK_EQUAL_COLLECTIONS(orig.begin(), orig.end(), vec.begin(), vec.end());

    std::vector<Widget> ex = { Widget(1), Widget(2) };
    vec | zip(iota(1), [](Widget& w, int i) { w._value = i; return i; }) | execute();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), vec.begin(), vec.end());
}
