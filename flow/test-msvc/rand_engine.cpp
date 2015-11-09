      
#include "stdafx.h"

#define DO_CHECK(engine, name)  \
    engine name;                \
    BOOST_CHECK(random_engine(name) | check(name)); \
    BOOST_CHECK(random_engine(engine()) | check(name))

BOOST_AUTO_TEST_CASE( rand_engine )  
{
    using namespace flow;

    auto check = [](auto&& rng) { return limit(1000) | all([&rng](auto i) { return i >= rng.min() && i <= rng.max(); }); };

    std::default_random_engine rng;
    BOOST_CHECK(random_engine() | check(rng));

    DO_CHECK(std::default_random_engine, r1);
    DO_CHECK(std::minstd_rand, r2);
    DO_CHECK(std::minstd_rand0, r3);
    DO_CHECK(std::mt19937, r4);
    DO_CHECK(std::mt19937_64, r5);
    DO_CHECK(std::ranlux24_base, r6);
    DO_CHECK(std::ranlux48_base, r7);
    DO_CHECK(std::ranlux24, r8);
    DO_CHECK(std::ranlux48, r9);
    DO_CHECK(std::knuth_b, r0);
}

