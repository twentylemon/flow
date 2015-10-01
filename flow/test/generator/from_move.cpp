
#include "../test.h"

BOOST_AUTO_TEST_SUITE(flow_generator)

BOOST_AUTO_TEST_CASE(from_move_t) {
    std::vector<int> vec = { 1, 2, 3 };

    std::vector<int> ex = { 1, 2, 3 };
    auto s = from_move(std::move(vec)) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<int> vec2 = { 1 };
    ex = { 1 };
    s = from_move(std::move(vec2)) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<int> vec3 = {};
    ex = {};
    s = from_move(std::move(vec3)) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

BOOST_AUTO_TEST_CASE(rfrom_move_t) {
    std::vector<int> vec = { 1, 2, 3 };

    std::vector<int> ex = { 3, 2, 1 };
    auto s = rfrom_move(std::move(vec)) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<int> vec2 = { 1 };
    ex = { 1 };
    s = rfrom_move(std::move(vec2)) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    std::vector<int> vec3 = {};
    ex = {};
    s = rfrom_move(std::move(vec3)) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

BOOST_AUTO_TEST_SUITE_END()
