
#include "../test.h"

BOOST_AUTO_TEST_SUITE(flow_terminal)

BOOST_AUTO_TEST_CASE(to_deque_test) {
    std::deque<int> em;
    auto tem = empty<int>() | to_deque();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());

    std::deque<int> con = init_list;
    auto res = from(init_list) | to_deque();
    BOOST_CHECK_EQUAL_COLLECTIONS(con.begin(), con.end(), res.begin(), res.end());
}

BOOST_AUTO_TEST_CASE(to_forward_list_test) {
    std::forward_list<int> em;
    auto tem = empty<int>() | to_forward_list();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());

    std::forward_list<int> con = init_list;
    con.reverse();  // to_forward_list is reversed
    auto res = from(init_list) | to_forward_list();
    BOOST_CHECK_EQUAL_COLLECTIONS(con.begin(), con.end(), res.begin(), res.end());
}

BOOST_AUTO_TEST_CASE(to_list_test) {
    std::list<int> em;
    auto tem = empty<int>() | to_list();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());

    std::list<int> con = init_list;
    auto res = from(init_list) | to_list();
    BOOST_CHECK_EQUAL_COLLECTIONS(con.begin(), con.end(), res.begin(), res.end());
}

BOOST_AUTO_TEST_CASE(to_multiset_test) {
    std::multiset<int> em;
    auto tem = empty<int>() | to_multiset();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());

    std::multiset<int> con = init_list;
    auto res = from(init_list) | to_multiset();
    BOOST_CHECK_EQUAL_COLLECTIONS(con.begin(), con.end(), res.begin(), res.end());
}

BOOST_AUTO_TEST_CASE(to_set_test) {
    std::set<int> em;
    auto tem = empty<int>() | to_set();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());

    std::set<int> con = init_list;
    auto res = from(init_list) | to_set();
    BOOST_CHECK_EQUAL_COLLECTIONS(con.begin(), con.end(), res.begin(), res.end());
}

BOOST_AUTO_TEST_CASE(to_unordered_multiset_test) {
    std::unordered_multiset<int> em;
    auto tem = empty<int>() | to_unordered_multiset();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());

    std::unordered_multiset<int> con = init_list;
    auto res = from(init_list) | to_unordered_multiset();
    BOOST_CHECK_EQUAL_COLLECTIONS(con.begin(), con.end(), res.begin(), res.end());
}

BOOST_AUTO_TEST_CASE(to_unordered_set_test) {
    std::unordered_set<int> em;
    auto tem = empty<int>() | to_unordered_set();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());

    std::unordered_set<int> con = init_list;
    auto res = from(init_list) | to_unordered_set();
    BOOST_CHECK_EQUAL_COLLECTIONS(con.begin(), con.end(), res.begin(), res.end());
}

BOOST_AUTO_TEST_CASE(to_vector_test) {
    std::vector<int> em;
    auto tem = empty<int>() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());

    std::vector<int> con = init_list;
    auto res = from(init_list) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(con.begin(), con.end(), res.begin(), res.end());
}

BOOST_AUTO_TEST_SUITE_END()
