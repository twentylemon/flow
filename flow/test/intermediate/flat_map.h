
#include "../test.h"

BOOST_AUTO_TEST_CASE(flat_map_t) {
    std::vector<int> vec = { 1, 2, 3 };
    std::vector<std::vector<int>> bigvec;
    for (int i = 0; i < 3; ++i) {
        bigvec.push_back(vec);
    }
    
    std::vector<int> ex = { 1, 1, 2, 2, 3, 3 };
    auto s = vec | flat_map([](int i){ return repeat(i, 2); }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());
    
    ex = { 1, 2, 3, 1, 2, 3, 1, 2, 3 };
    s = bigvec | flat_map([](std::vector<int>& v){ return from(v); }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    ex = {};
    s = bigvec | flat_map([](auto& v) { return empty<int>(); }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());

    s = empty<std::vector<int>>() | flat_map([](auto& v) { return from(v); }) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(ex.begin(), ex.end(), s.begin(), s.end());
}
