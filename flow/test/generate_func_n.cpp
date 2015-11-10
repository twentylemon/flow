      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( generate_func_n )  
{
    using namespace flow;

    std::vector<int> vec = { 1, 2, 3 };
    std::vector<int> ex = vec;
    std::size_t i = 0;

    auto s = generate([&i, &vec]() { return vec[i++]; }, vec.size()) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());

    ex = { 4, 4, 4, 4 };
    s = generate([]() { return 4; }, 4) | to_vector();
    BOOST_CHECK_EQUAL_COLLECTIONS(s.begin(), s.end(), ex.begin(), ex.end());
}

