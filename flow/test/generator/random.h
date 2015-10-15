
#include "../test.h"

#define DO_CHECK(engine, name)  \
    engine name;                \
    BOOST_CHECK(random_engine(name) | check(name)); \
    BOOST_CHECK(random_engine(engine()) | check(name))
BOOST_AUTO_TEST_CASE(random_engine_t) {
    auto check = [](auto& rng) { return limit(1000) | all([&rng](std::remove_reference_t<decltype(rng)>::result_type i) { return i >= rng.min() && i <= rng.max(); }); };

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

#undef DO_CHECK
#define DO_CHECK(distrib) BOOST_CHECK(random_distribution(distrib()) | check(distrib()))

BOOST_AUTO_TEST_CASE(random_distribution_t) {
    auto check = [](auto& d) { return limit(10) | all([&d](std::remove_reference_t<decltype(d)>::result_type i) { return i >= d.min() && i <= d.max(); }); };

    DO_CHECK(std::uniform_int_distribution<>);
    DO_CHECK(std::uniform_real_distribution<>);
    DO_CHECK(std::bernoulli_distribution);
    DO_CHECK(std::binomial_distribution<>);
    DO_CHECK(std::geometric_distribution<>);
    DO_CHECK(std::negative_binomial_distribution<>);
    DO_CHECK(std::poisson_distribution<>);
    DO_CHECK(std::exponential_distribution<>);
    DO_CHECK(std::gamma_distribution<>);
    DO_CHECK(std::weibull_distribution<>);
    DO_CHECK(std::lognormal_distribution<>);
    DO_CHECK(std::chi_squared_distribution<>);
    DO_CHECK(std::cauchy_distribution<>);
    DO_CHECK(std::fisher_f_distribution<>);
    DO_CHECK(std::student_t_distribution<>);
    DO_CHECK(std::discrete_distribution<>);
    DO_CHECK(std::piecewise_constant_distribution<>);
}

#undef DO_CHECK
#define DO_CHECK(min, max) BOOST_CHECK(random_ints(min, max) | limit(1000) | all([=](auto i) { return i >= min && i <= max; }))
BOOST_AUTO_TEST_CASE(random_ints_t) {
    DO_CHECK(0, 5);
    DO_CHECK(-100, 100);
    DO_CHECK(1, 1);
    DO_CHECK(0, 1);
}


#undef DO_CHECK
#define DO_CHECK(min, max) BOOST_CHECK(random_reals(min, max) | limit(1000) | all([=](auto i) { return i >= min && i <= max; }))
BOOST_AUTO_TEST_CASE(random_reals_t) {
    DO_CHECK(0.0, 1.0);
    DO_CHECK(-100.0, 100.0);
    DO_CHECK(-1000000.0, -5000.0);
}

BOOST_AUTO_TEST_CASE(random_bools_t) {
    BOOST_CHECK(random_bools() | limit(1000) | all([](auto b) { return b || !b; }));
    BOOST_CHECK(random_bools() | limit(1000) | filter() | all());
}
