
#include "../test.h"

BOOST_AUTO_TEST_SUITE(flow_generator)

BOOST_AUTO_TEST_CASE(generate_t) {
    std::vector<int> vec = { 1, 2, 3 };
    std::vector<int> ex = { 1, 2, 3 };
    std::size_t i = 0;

    auto s = generate([&i,&vec]() { return vec[i++]; }) | limit(3) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 4, 4, 4, 4 };
    s = generate([]() { return 4; }) | limit(4) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

BOOST_AUTO_TEST_CASE(generate_n_t) {
    std::vector<int> vec = { 1, 2, 3 };
    std::vector<int> ex = vec;
    std::size_t i = 0;

    auto s = generate([&i, &vec]() { return vec[i++]; }, vec.size()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 4, 4, 4, 4 };
    s = generate([]() { return 4; }, 4) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

BOOST_AUTO_TEST_SUITE_END()
