
#include "../test.h"

BOOST_AUTO_TEST_CASE(fold_init) {
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | fold(std::plus<int>(), 0), 6);
    BOOST_CHECK_EQUAL(from({ 1, -2, 3 }) | fold(std::plus<int>(), 0), 2);
    BOOST_CHECK_EQUAL(from({ 1, 2 }) | fold(std::minus<int>(), 0), -3);
    BOOST_CHECK_EQUAL(from({ 1 }) | fold(std::plus<int>(), 0), 1);
    BOOST_CHECK_EQUAL(empty<int>() | fold(std::plus<int>(), 0), 0);
}

BOOST_AUTO_TEST_CASE(fold_noinit) {
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | fold(std::plus<int>()), 6);
    BOOST_CHECK_EQUAL(from({ 1, -2, 3 }) | fold(std::plus<int>()), 2);
    BOOST_CHECK_EQUAL(from({ 1, 2 }) | fold(std::minus<int>()), -1);    // 1 - (2); 1 is the init
    BOOST_CHECK_EQUAL(from({ 1 }) | fold(std::plus<int>()), 1);
    BOOST_CHECK_THROW(empty<int>() | fold(std::plus<int>()), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(fold_id_init) {
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | fold_id(std::plus<int>(), [](int i) { return 2 * i; }, 1), 8);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | fold_id([](std::pair<int, int> p, int i) {
        p.first = std::min(p.first, i); // p is the min/max
        p.second = std::max(p.second, i);
        return p;
    }, [](int i) { return std::make_pair(i, i); }, 0), std::make_pair(0, 3));   // 0 from init value, 3 is max

    BOOST_CHECK_EQUAL(empty<int>() | fold_id(std::plus<int>(), [](int i) { return 4; }, 0), 4);
}

BOOST_AUTO_TEST_CASE(fold_id_noinit) {
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | fold_id(std::plus<int>(), [](int i) { return 2 * i; }), 7);
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | fold_id([](std::pair<int, int> p, int i) {
        p.first = std::min(p.first, i); // p is the min/max
        p.second = std::max(p.second, i);
        return p;
    }, [](int i) { return std::make_pair(i, i); }), std::make_pair(1, 3));

    BOOST_CHECK_THROW(empty<int>() | fold_id(std::plus<int>(), [](int i) { return 4; }), std::out_of_range);
}
