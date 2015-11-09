
#include "../test.h"

BOOST_AUTO_TEST_CASE(all_func) {
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | all(is_even), false);
    BOOST_CHECK_EQUAL(from({ 2, 4, 6 }) | all(is_even), true);
    BOOST_CHECK_EQUAL(empty<int>() | all(is_even), true);

    auto s = from({ 1, 2, 3 }) | to_vector();
    BOOST_CHECK_EQUAL(s | all(is_even), false);
}

BOOST_AUTO_TEST_CASE(all_bool) {
    BOOST_CHECK_EQUAL(from({ true, false }) | all(), false);
    BOOST_CHECK_EQUAL(from({ true, true, true }) | all(), true);
    BOOST_CHECK_EQUAL(from({ true, false, true }) | all(), false);
    BOOST_CHECK_EQUAL(from({ false, false }) | all(), false);
    BOOST_CHECK_EQUAL(empty<bool>() | all(), true);
}

BOOST_AUTO_TEST_CASE(all_member) {
    BOOST_CHECK_EQUAL(from({ Widget(1), Widget(2) }) | all(&Widget::is_even), false);
    BOOST_CHECK_EQUAL(from({ Widget(2), Widget(4) }) | all(&Widget::is_even), true);
}

BOOST_AUTO_TEST_CASE(all_member_const) {
    const std::vector<Widget> vec1 = { Widget(1), Widget(2) };
    const std::vector<Widget> vec2 = { Widget(2), Widget(2) };
    BOOST_CHECK_EQUAL(vec1 | all(&Widget::is_even), false);
    BOOST_CHECK_EQUAL(vec2 | all(&Widget::is_even), true);
}
