      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( uncurry_t )  
{
    using namespace flow;

    std::vector<int> left = { 1, 2, 3 };
    std::vector<int> right = { 4, 5, 6 };

    std::vector<std::tuple<int, int>> ex = { std::make_tuple(1,4), std::make_tuple(2,5), std::make_tuple(3,6) };
    auto s = left | zip(right) | filter(uncurry([](int l, int r) { return true; })) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<std::tuple<int, int, int>> ex2 = { std::make_tuple(1, 4, 1), std::make_tuple(2, 5, 2), std::make_tuple(3, 6, 3) };
    auto s2 = left | zip(right) | zip(left) | filter(uncurry([](int l, int r, int i) { return true; })) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s2.begin(), s2.end(), ex2.begin(), ex2.end());

    std::vector<int> ex3 = { 3, 6, 9 };
    auto s3 = left | zip(left) | zip(left) | map(uncurry([](int i, int j, int k) { return i + j + k; })) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s3.begin(), s3.end(), ex3.begin(), ex3.end());

    auto f1 = uncurry(std::plus<int>());
    BOOST_CHECK_EQUAL(f1(std::make_tuple(1, 1)), 1 + 1);
    BOOST_CHECK_EQUAL(f1(std::make_tuple(-42, 323)), -42 + 323);

    auto f2 = uncurry([](int i, int j, int k) { return i * j * k; });
    BOOST_CHECK_EQUAL(f2(std::make_tuple(1, 2, 3)), 1 * 2 * 3);
    BOOST_CHECK_EQUAL(f2(std::make_tuple(4, -2, 5)), 4 * -2 * 5);
}

