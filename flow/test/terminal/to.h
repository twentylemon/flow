
#include "../test.h"

BOOST_AUTO_TEST_CASE(to_deque_t) {
    std::deque<int> em;
    auto tem = empty<int>() | to_deque();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());

    std::deque<int> con = init_list;
    auto res = from(init_list) | to_deque();
    BOOST_CHECK_EQUAL_COLLECTIONS(con.begin(), con.end(), res.begin(), res.end());

    auto tem2 = empty<int>() | to_deque(std::allocator<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem2.begin(), tem2.end());

    std::deque<int, std::allocator<int>> de = init_list;
    auto de2 = from(init_list) | to_deque(std::allocator<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(de.begin(), de.end(), de2.begin(), de2.end());
}

BOOST_AUTO_TEST_CASE(to_forward_list_t) {
    std::forward_list<int> em;
    auto tem = empty<int>() | to_forward_list();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());

    std::forward_list<int> con = init_list;
    con.reverse();  // to_forward_list is reversed
    auto res = from(init_list) | to_forward_list();
    BOOST_CHECK_EQUAL_COLLECTIONS(con.begin(), con.end(), res.begin(), res.end());

    auto tem2 = empty<int>() | to_forward_list(std::allocator<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem2.begin(), tem2.end());

    std::forward_list<int, std::allocator<int>> de = init_list;
    de.reverse();
    auto de2 = from(init_list) | to_forward_list(std::allocator<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(de.begin(), de.end(), de2.begin(), de2.end());
}

BOOST_AUTO_TEST_CASE(to_list_t) {
    std::list<int> em;
    auto tem = empty<int>() | to_list();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());

    std::list<int> con = init_list;
    auto res = from(init_list) | to_list();
    BOOST_CHECK_EQUAL_COLLECTIONS(con.begin(), con.end(), res.begin(), res.end());

    auto tem2 = empty<int>() | to_list(std::allocator<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem2.begin(), tem2.end());

    std::list<int, std::allocator<int>> de = init_list;
    auto de2 = from(init_list) | to_list(std::allocator<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(de.begin(), de.end(), de2.begin(), de2.end());
}

BOOST_AUTO_TEST_CASE(to_multiset_t) {
    std::multiset<int> em;
    auto tem = empty<int>() | to_multiset();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());

    std::multiset<int> con = init_list;
    auto res = from(init_list) | to_multiset();
    BOOST_CHECK_EQUAL_COLLECTIONS(con.begin(), con.end(), res.begin(), res.end());

    std::multiset<int, bool(*)(int,int)> de(square_less);   // ctor by init_list changes order
    std::copy(init_list.begin(), init_list.end(), std::inserter(de, de.end()));
    auto de2 = from(init_list) | to_multiset(square_less);
    BOOST_CHECK_EQUAL_COLLECTIONS(de.begin(), de.end(), de2.begin(), de2.end());

    std::multiset<int, bool(*)(int, int), std::allocator<int>> de3(square_less, std::allocator<int>());
    std::copy(init_list.begin(), init_list.end(), std::inserter(de3, de3.end()));
    auto de4 = from(init_list) | to_multiset(square_less, std::allocator<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(de3.begin(), de3.end(), de4.begin(), de4.end());
}

BOOST_AUTO_TEST_CASE(to_set_t) {
    std::set<int> em;
    auto tem = empty<int>() | to_set();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());

    std::set<int> con = init_list;
    auto res = from(init_list) | to_set();
    BOOST_CHECK_EQUAL_COLLECTIONS(con.begin(), con.end(), res.begin(), res.end());

    std::set<int, bool(*)(int, int)> de(square_less);
    std::copy(init_list.begin(), init_list.end(), std::inserter(de, de.end()));
    auto de2 = from(init_list) | to_set(square_less);
    BOOST_CHECK_EQUAL_COLLECTIONS(de.begin(), de.end(), de2.begin(), de2.end());

    std::set<int, bool(*)(int, int), std::allocator<int>> de3(square_less, std::allocator<int>());
    std::copy(init_list.begin(), init_list.end(), std::inserter(de3, de3.end()));
    auto de4 = from(init_list) | to_set(square_less, std::allocator<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(de3.begin(), de3.end(), de4.begin(), de4.end());
}

BOOST_AUTO_TEST_CASE(to_unordered_multiset_t) {
    std::unordered_multiset<int> em;
    auto tem = empty<int>() | to_unordered_multiset();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());

    std::unordered_multiset<int> con = init_list;
    auto res = from(init_list) | to_unordered_multiset();
    BOOST_CHECK_EQUAL_COLLECTIONS(con.begin(), con.end(), res.begin(), res.end());

    std::unordered_multiset<int, std::hash<int>> de(16, std::hash<int>());
    std::copy(init_list.begin(), init_list.end(), std::inserter(de, de.end()));
    auto de2 = from(init_list) | to_unordered_multiset(std::hash<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(de.begin(), de.end(), de2.begin(), de2.end());

    std::unordered_multiset<int, std::hash<int>, std::equal_to<int>> de3(16, std::hash<int>(), std::equal_to<int>());
    std::copy(init_list.begin(), init_list.end(), std::inserter(de3, de3.end()));
    auto de4 = from(init_list) | to_unordered_multiset(std::hash<int>(), std::equal_to<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(de3.begin(), de3.end(), de4.begin(), de4.end());

    std::unordered_multiset<int, std::hash<int>, std::equal_to<int>, std::allocator<int>> de5(16, std::hash<int>(), std::equal_to<int>(), std::allocator<int>());
    std::copy(init_list.begin(), init_list.end(), std::inserter(de5, de5.end()));
    auto de6 = from(init_list) | to_unordered_multiset(std::hash<int>(), std::equal_to<int>(), std::allocator<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(de5.begin(), de5.end(), de6.begin(), de6.end());
}

BOOST_AUTO_TEST_CASE(to_unordered_set_t) {
    std::unordered_set<int> em;
    auto tem = empty<int>() | to_unordered_set();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());

    std::unordered_set<int> con = init_list;
    auto res = from(init_list) | to_unordered_set();
    BOOST_CHECK_EQUAL_COLLECTIONS(con.begin(), con.end(), res.begin(), res.end());

    std::unordered_set<int, std::hash<int>> de(16, std::hash<int>());
    std::copy(init_list.begin(), init_list.end(), std::inserter(de, de.end()));
    auto de2 = from(init_list) | to_unordered_set(std::hash<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(de.begin(), de.end(), de2.begin(), de2.end());

    std::unordered_set<int, std::hash<int>, std::equal_to<int>> de3(16, std::hash<int>(), std::equal_to<int>());
    std::copy(init_list.begin(), init_list.end(), std::inserter(de3, de3.end()));
    auto de4 = from(init_list) | to_unordered_set(std::hash<int>(), std::equal_to<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(de3.begin(), de3.end(), de4.begin(), de4.end());

    std::unordered_set<int, std::hash<int>, std::equal_to<int>, std::allocator<int>> de5(16, std::hash<int>(), std::equal_to<int>(), std::allocator<int>());
    std::copy(init_list.begin(), init_list.end(), std::inserter(de5, de5.end()));
    auto de6 = from(init_list) | to_unordered_set(std::hash<int>(), std::equal_to<int>(), std::allocator<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(de5.begin(), de5.end(), de6.begin(), de6.end());
}

BOOST_AUTO_TEST_CASE(to_vector_t) {
    std::vector<int> em;
    auto tem = empty<int>() | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());

    std::vector<int> con = init_list;
    auto res = from(init_list) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(con.begin(), con.end(), res.begin(), res.end());

    auto tem2 = empty<int>() | to_vector(std::allocator<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem2.begin(), tem2.end());

    std::vector<int, std::allocator<int>> de = init_list;
    auto de2 = from(init_list) | to_vector(std::allocator<int>());
    BOOST_CHECK_EQUAL_COLLECTIONS(con.begin(), con.end(), res.begin(), res.end());
}
