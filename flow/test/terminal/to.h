
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

    std::unordered_multiset<int> con;
    std::copy(init_list.begin(), init_list.end(), std::inserter(con, con.end()));
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

    std::unordered_set<int> con;
    std::copy(init_list.begin(), init_list.end(), std::inserter(con, con.end()));
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

BOOST_AUTO_TEST_CASE(to_map_t) {
    std::map<int, std::size_t> em;
    auto tem = empty<int>() | to_map();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());
    
    std::vector<int> vec = { 1, 2, 3 };
    std::map<int, std::size_t> ex = { {1, 1}, {2, 1}, {3, 1} };
    auto s = vec | to_map();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
    
    vec = { 1, 2, 2, 3, 3, 3 };
    ex = { {1, 1}, {2, 2}, {3, 3} };
    s = vec | to_map();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
    
    s = closed_range(1, 3) | flat_map([](int i) { return repeat(i, i); }) | to_map();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
    
    std::map<int, std::size_t, bool(*)(int, int)> ex2(square_less);
    ex2 = { {1, 1}, {-2, 1} };
    vec = { -2, 1 };
    auto s2 = vec | to_map(square_less);
    BOOST_CHECK_EQUAL_COLLECTIONS(s2.begin(), s2.end(), ex2.begin(), ex2.end());
    
    std::map<int, std::size_t, bool(*)(int, int), std::allocator<std::pair<const int, std::size_t>>> ex3(square_less, std::allocator<std::pair<const int, std::size_t>>());
    ex3 = { {1, 1}, {-2, 1} };
    auto s3 = vec | to_map(square_less, std::allocator<std::pair<const int, std::size_t>>());
    BOOST_CHECK_EQUAL_COLLECTIONS(s3.begin(), s3.end(), ex3.begin(), ex3.end());
}

BOOST_AUTO_TEST_CASE(to_unordered_map_t) {
    std::unordered_map<int, std::size_t> em;
    auto tem = empty<int>() | to_unordered_map();
    BOOST_CHECK_EQUAL_COLLECTIONS(em.begin(), em.end(), tem.begin(), tem.end());
    
    std::initializer_list<std::pair<const int, std::size_t>> list = { {1, 1}, {2, 2}, {3, 1}, {4, 3} };
    std::vector<int> f = { 1, 2, 2, 3, 4, 4, 4 };

    std::unordered_map<int, std::size_t> con = list;
    auto res = from(f) | to_unordered_map();
    for (auto& p : con) {
        BOOST_CHECK_EQUAL(p, *res.find(p.first));
    }

    std::unordered_map<int, std::size_t, std::hash<int>> de(16, std::hash<int>());
    de = list;
    auto de2 = from(f) | to_unordered_map(std::hash<int>());
    for (auto& p : de) {
        BOOST_CHECK_EQUAL(p, *de2.find(p.first));
    }

    std::unordered_map<int, std::size_t, std::hash<int>, std::equal_to<int>> de3(16, std::hash<int>(), std::equal_to<int>());
    de3 = list;
    auto de4 = from(f) | to_unordered_map(std::hash<int>(), std::equal_to<int>());
    for (auto& p : de3) {
        BOOST_CHECK_EQUAL(p, *de4.find(p.first));
    }

    std::unordered_map<int, std::size_t, std::hash<int>, std::equal_to<int>, std::allocator<std::pair<const int, std::size_t>>> de5(16, std::hash<int>(), std::equal_to<int>(), std::allocator<std::pair<const int, std::size_t>>());
    de5 = list;
    auto de6 = from(f) | to_unordered_map(std::hash<int>(), std::equal_to<int>(), std::allocator<std::pair<const int, std::size_t>>());
    for (auto& p : de5) {
        BOOST_CHECK_EQUAL(p, *de6.find(p.first));
    }
}

BOOST_AUTO_TEST_CASE(to_group_t) {
    std::vector<Widget> w = { Widget(1), Widget(2), Widget(3), Widget(4) };

    std::map<bool, std::vector<Widget>> ex = { {false, {Widget(1), Widget(3)}}, {true, {Widget(2), Widget(4)}} };
    auto s = w | to_group([](Widget& w) { return w.is_even(); });
    for (auto& p : s) {
        BOOST_CHECK_EQUAL_COLLECTIONS(p.second.begin(), p.second.end(), ex[p.first].begin(), ex[p.first].end());
    }

    auto s2 = empty<int>() | to_group(is_even);
    BOOST_CHECK(s2.empty());

    std::map<int, std::vector<Widget>> ex3 = { {1, {Widget(1)}}, {2, {Widget(2)}}, {3, {Widget(3)}}, {4, {Widget(4)}} };
    auto s3 = w | to_group([](Widget& w) { return w._value; });
    for (auto& p : s3) {
        BOOST_CHECK_EQUAL_COLLECTIONS(p.second.begin(), p.second.end(), ex3[p.first].begin(), ex3[p.first].end());
    }

    std::map<int, std::vector<int>> ex4 = { {true, {2,4,6,8}}, {false, {1,3,5,7}} };
    auto s4 = closed_range(1, 8) | to_group(is_even);
    for (auto& p : s4) {
        BOOST_CHECK_EQUAL_COLLECTIONS(p.second.begin(), p.second.end(), ex4[p.first].begin(), ex4[p.first].end());
    }
}
