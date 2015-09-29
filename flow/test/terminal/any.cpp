
#include "../test.h"

BOOST_AUTO_TEST_SUITE(flow_terminal)

BOOST_AUTO_TEST_CASE(any_func) {
    BOOST_CHECK_EQUAL(from({ 1, 2, 3 }) | any(is_even), true);
    BOOST_CHECK_EQUAL(from({ 1, 3, 5 }) | any(is_even), false);
    BOOST_CHECK_EQUAL(empty<int>() | any(is_even), false);
}

BOOST_AUTO_TEST_CASE(any_bool) {
    BOOST_CHECK_EQUAL(from({ true, false }) | any(), true);
    BOOST_CHECK_EQUAL(from({ false, false, false }) | any(), false);
}

BOOST_AUTO_TEST_CASE(any_member) {
    BOOST_CHECK_EQUAL(from({ Member(1), Member(2) }) | any(&Member::is_even), true);
    BOOST_CHECK_EQUAL(from({ Member(1), Member(3) }) | any(&Member::is_even), false);
}

BOOST_AUTO_TEST_CASE(any_member_const) {
    const std::vector<Member> vec1 = { Member(1), Member(2) };
    const std::vector<Member> vec2 = { Member(1), Member(1) };
    BOOST_CHECK_EQUAL(vec1 | any(&Member::is_even), true);
    BOOST_CHECK_EQUAL(vec2 | any(&Member::is_even), false);
}

BOOST_AUTO_TEST_SUITE_END()
