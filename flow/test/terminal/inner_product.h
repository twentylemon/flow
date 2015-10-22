
#include "../test.h"

BOOST_AUTO_TEST_CASE(inner_product_t) {
    std::vector<int> vec3 = { 1, 2, 3 };

    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | inner_product({ 4, 5, 6 }, 0), 0 + 1 * 4 + 2 * 5 + 3 * 6);

    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | inner_product(vec3.begin(), vec3.end(), 2), 2 + 1 * 1 + 2 * 2 + 3 * 3);

    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | inner_product(empty<int>(), 2), 2);
    BOOST_CHECK_EQUAL(empty<int>() | inner_product({ 1, 2, 3 }, 2), 2);
    BOOST_CHECK_EQUAL(empty<int>() | inner_product(empty<int>(), 2), 2);

    BOOST_CHECK_EQUAL(from({ 1, 1, 1 }) | inner_product(vec3, 0), 6);

    BOOST_CHECK_EQUAL(vec3 | inner_product(vec3, 0, std::divides<int>(), std::plus<int>()), 3);
    BOOST_CHECK_EQUAL(vec3 | inner_product(vec3, 0, std::divides<int>(), std::minus<int>()), -3);
    BOOST_CHECK_EQUAL(vec3 | inner_product({ 1, 2, 3 }, 0, std::divides<int>(), std::minus<int>()), -3);
    BOOST_CHECK_EQUAL(vec3 | inner_product(vec3.begin(), vec3.end(), 0, std::divides<int>(), std::minus<int>()), -3);
}
