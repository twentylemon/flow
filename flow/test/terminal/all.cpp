
#include "../test.h"

BOOST_AUTO_TEST_SUITE(flow_terminal)

BOOST_AUTO_TEST_CASE(all_func) {
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | all(is_even), false);
    BOOST_CHECK_EQUAL(from({ 2, 4, 6 }) | all(is_even), true);
    BOOST_CHECK_EQUAL(empty<int>() | all(is_even), true);
}

BOOST_AUTO_TEST_CASE(all_bool) {
    BOOST_CHECK_EQUAL(from({ true, false }) | all(), false);
    BOOST_CHECK_EQUAL(from({ true, true, true }) | all(), true);
}

BOOST_AUTO_TEST_CASE(all_member) {
    BOOST_CHECK_EQUAL(from({ Member(1), Member(2) }) | all(&Member::is_even), false);
    BOOST_CHECK_EQUAL(from({ Member(2), Member(4) }) | all(&Member::is_even), true);
}

BOOST_AUTO_TEST_CASE(all_member_const) {
    const std::vector<Member> vec1 = { Member(1), Member(2) };
    const std::vector<Member> vec2 = { Member(2), Member(2) };
    BOOST_CHECK_EQUAL(vec1 | all(&Member::is_even), false);
    BOOST_CHECK_EQUAL(vec2 | all(&Member::is_even), true);
}

BOOST_AUTO_TEST_SUITE_END()
