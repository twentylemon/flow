      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( zip_stream_default )  
{
    using namespace flow;

    std::vector<int> left = { 1, 2, 3 };
    std::vector<int> right = { 4, 5, 6 };

    std::vector<std::tuple<int, int>> ex = { std::make_tuple(1,4), std::make_tuple(2,5), std::make_tuple(3,6) };
    auto s = left | zip(from(right)) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<std::tuple<int, int, int>> ex2 = { std::make_tuple(1, 4, 1), std::make_tuple(2, 5, 2), std::make_tuple(3, 6, 3) };
    auto s2 = left | zip(from(right)) | zip(from(left)) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s2.begin(), s2.end(), ex2.begin(), ex2.end());

    s2 = left | zip(right | zip(left)) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s2.begin(), s2.end(), ex2.begin(), ex2.end());

    std::vector<std::tuple<int, int, int, int>> ex3 = { std::make_tuple(1,1,4,4), std::make_tuple(2,2,5,5), std::make_tuple(3,3,6,6) };
    auto s3 = left | zip(from(left)) | zip(right | zip(from(right))) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s3.begin(), s3.end(), ex3.begin(), ex3.end());

    s3 = left | zip(from(left)) | zip(from(right)) | zip(from(right)) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s3.begin(), s3.end(), ex3.begin(), ex3.end());

    s3 = left | zip(left | zip(right)) | zip(from(right)) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s3.begin(), s3.end(), ex3.begin(), ex3.end());

    s3 = left | zip(left | zip(right | zip(from(right)))) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s3.begin(), s3.end(), ex3.begin(), ex3.end());

    s3 = left | zip(left) | zip(right | zip(from(right))) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s3.begin(), s3.end(), ex3.begin(), ex3.end());

    std::vector<Widget> w = { Widget(0), Widget(0), Widget(0) };
    std::vector<Widget> orig = w;
    std::vector<Widget> wex = { Widget(1), Widget(2), Widget(3) };
    w | zip(iota(1), [](Widget& w, int i) { w.set_value(i); return i; }) | execute();
    BOOST_CHECK_EQUAL_COLLECTIONS(wex.begin(), wex.end(), w.begin(), w.end());

    w = orig;
    w | zip(iota(1)) | each(uncurry([](Widget& w, int i) { w.set_value(i); }));
    BOOST_CHECK_EQUAL_COLLECTIONS(wex.begin(), wex.end(), w.begin(), w.end());

    w = orig;
    w | zip(iota(1)) | zip(repeat(0)) | each(uncurry([](Widget& w, int l, int r) { w.set_value(l + r); }));
    BOOST_CHECK_EQUAL_COLLECTIONS(wex.begin(), wex.end(), w.begin(), w.end());
}

