      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( general )  
{
    using namespace flow;

    auto square = [](auto& i) { return i*i; };
    // sum the first 5 even squares
    int result = 2 * 2 + 4 * 4 + 6 * 6 + 8 * 8 + 10 * 10;
    BOOST_CHECK_EQUAL(closed_range(1, 10) | filter(is_even) | map(square) | sum().value(), result);
    auto square_sum = map(square) | sum().value();
    BOOST_CHECK_EQUAL(closed_range(1, 10) | filter(is_even) | square_sum, result);
    auto a = closed_range(1, 10) | filter(is_even) | to_vector();
    BOOST_CHECK_EQUAL(a | square_sum, result);

    auto add2_evens = filter(is_even) | map([](int i) { return i + 2; });
    BOOST_CHECK_EQUAL(a | add2_evens | square_sum, 4 * 4 + 6 * 6 + 8 * 8 + 10 * 10 + 12 * 12);
    BOOST_CHECK_EQUAL(a | add2_evens | square_sum, 4 * 4 + 6 * 6 + 8 * 8 + 10 * 10 + 12 * 12);

    std::vector<int> v;
    range(1, 5) | filter(is_even) | map(square) | copy(std::back_inserter(v));
    range(1, 5) | replace(3, 4) | copy(std::back_inserter(v));
    std::vector<int> ex = { 2 * 2, 4 * 4, 1, 2, 4, 4 };
    BOOST_CHECK_EQUAL_COLLECTIONS(v.begin(), v.end(), ex.begin(), ex.end());

    BOOST_CHECK_EQUAL(iota(1) | filter([](int i) { return i > 10000; }) | first().value(), 10001);
}

