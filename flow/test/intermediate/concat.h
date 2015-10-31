
#include "../test.h"

BOOST_AUTO_TEST_CASE(concat_t) {
    std::vector<int> vec3 = { 1, 2, 3 };

    std::vector<int> vec1 = { 1, 2, 3, 4, 5, 6 };
    auto vec2 = from({ 1, 2, 3 }) | concat({ 4, 5, 6 }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { 1, 2, 3, 1, 2, 3 };
    vec2 = from({ 1, 2, 3 }) | concat(vec3.begin(), vec3.end()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { 1, 2, 3 };
    vec2 = from({ 1, 2, 3 }) | concat(empty<int>()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { 4, 5, 6 };
    vec2 = empty<const int>() | concat({ 4, 5, 6 }) | to_vector();  // init_list are const
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = {};
    vec2 = empty<int>() | concat(empty<int>()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    vec1 = { 1, 2, 3, 4 };
    vec2 = from({ 1, 2 }) | concat(from({ 4, 3 }) | reverse()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
}
