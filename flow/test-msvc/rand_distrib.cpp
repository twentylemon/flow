      
#include "stdafx.h"

#define DO_CHECK(distrib) BOOST_CHECK(random_distribution(distrib()) | check(distrib()))

BOOST_AUTO_TEST_CASE( rand_distrib )  
{
    using namespace flow;

    auto check = [](auto&& d) { return limit(10) | all([&d](auto i) { return i >= d.min() && i <= d.max(); }); };

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

