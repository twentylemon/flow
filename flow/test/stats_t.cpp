      
#include "stdafx.h"

BOOST_AUTO_TEST_CASE( stats_t )  
{
    using namespace flow;

    BOOST_CHECK_THROW(empty<int>() | stats(), std::out_of_range);

    double epsilon = 1.192092896e-07;   // float epsilon

    auto s = from({ 1 }) | stats();
    BOOST_CHECK_EQUAL(s.n(), 1);
    BOOST_CHECK_CLOSE(s.mean(), 1, epsilon);
    BOOST_CHECK_CLOSE(s.stddev(), 0, epsilon);
    BOOST_CHECK_CLOSE(s.variance(), 0, epsilon);
    BOOST_CHECK_EQUAL(s.sum(), 1);
    BOOST_CHECK_EQUAL(s.sum_squares(), 1);
    BOOST_CHECK(!s.has_minmax());
    BOOST_CHECK(!s.has_medianmode());

    s = from({ 1, 1, 1 }) | stats();
    BOOST_CHECK_EQUAL(s.n(), 3);
    BOOST_CHECK_CLOSE(s.mean(), 1, epsilon);
    BOOST_CHECK_CLOSE(s.stddev(), 0, epsilon);
    BOOST_CHECK_CLOSE(s.variance(), 0, epsilon);
    BOOST_CHECK_EQUAL(s.sum(), 3);
    BOOST_CHECK_EQUAL(s.sum_squares(), 3);
    BOOST_CHECK(!s.has_minmax());
    BOOST_CHECK(!s.has_medianmode());

    s = from({ 1, 2, 3 }) | stats();
    BOOST_CHECK_EQUAL(s.n(), 3);
    BOOST_CHECK_CLOSE(s.mean(), 2, epsilon);
    BOOST_CHECK_CLOSE(s.stddev(), std::sqrt(2.0 / 3.0), epsilon);
    BOOST_CHECK_CLOSE(s.variance(), 2.0 / 3.0, epsilon);
    BOOST_CHECK_EQUAL(s.sum(), 6);
    BOOST_CHECK_EQUAL(s.sum_squares(), 14);
    BOOST_CHECK(!s.has_minmax());
    BOOST_CHECK(!s.has_medianmode());

    std::vector<int> modes = { 1, 2, 3 };
    auto s2 = from({ 1, 2, 3 }) | stats<double, true, true>();
    BOOST_CHECK_EQUAL(s2.min(), 1);
    BOOST_CHECK_EQUAL(s2.max(), 3);
    BOOST_CHECK_CLOSE(s2.median(), 2, epsilon);
    BOOST_CHECK_EQUAL(s2.mode(), 1);
    BOOST_CHECK_EQUAL_COLLECTIONS(s2.modes().begin(), s2.modes().end(), modes.begin(), modes.end());
    BOOST_CHECK(s2.has_minmax());
    BOOST_CHECK(s2.has_medianmode());

    modes = { 1 };
    s2 = from({ 1, 1, 1, 2, 2 }) | stats<double, true, true>();
    BOOST_CHECK_EQUAL(s2.min(), 1);
    BOOST_CHECK_EQUAL(s2.max(), 2);
    BOOST_CHECK_CLOSE(s2.median(), 1, epsilon);
    BOOST_CHECK_EQUAL(s2.mode(), 1);
    BOOST_CHECK_EQUAL_COLLECTIONS(s2.modes().begin(), s2.modes().end(), modes.begin(), modes.end());
    BOOST_CHECK(s2.has_minmax());
    BOOST_CHECK(s2.has_medianmode());

    modes = { 2 };
    s2 = from({ 2, 1, 2, 1, 2, -100, 100 }) | stats<double, true, true>();
    BOOST_CHECK_EQUAL(s2.min(), -100);
    BOOST_CHECK_EQUAL(s2.max(), 100);
    BOOST_CHECK_CLOSE(s2.median(), 2, epsilon);
    BOOST_CHECK_EQUAL(s2.mode(), 2);
    BOOST_CHECK_EQUAL_COLLECTIONS(s2.modes().begin(), s2.modes().end(), modes.begin(), modes.end());
    BOOST_CHECK(s2.has_minmax());
    BOOST_CHECK(s2.has_medianmode());

    modes = { 1 };
    s2 = repeat(1, 100) | stats<double, true, true>();
    BOOST_CHECK_EQUAL(s2.n(), 100);
    BOOST_CHECK_CLOSE(s2.mean(), 1, epsilon);
    BOOST_CHECK_CLOSE(s2.stddev(), 0, epsilon);
    BOOST_CHECK_CLOSE(s2.variance(), 0, epsilon);
    BOOST_CHECK_EQUAL(s2.sum(), 100);
    BOOST_CHECK_EQUAL(s2.sum_squares(), 100);
    BOOST_CHECK_EQUAL(s2.min(), 1);
    BOOST_CHECK_EQUAL(s2.max(), 1);
    BOOST_CHECK_CLOSE(s2.median(), 1, epsilon);
    BOOST_CHECK_EQUAL(s2.mode(), 1);
    BOOST_CHECK_EQUAL_COLLECTIONS(s2.modes().begin(), s2.modes().end(), modes.begin(), modes.end());
    BOOST_CHECK(s2.has_minmax());
    BOOST_CHECK(s2.has_medianmode());

    modes = { 1 };
    s2 = cycle({ 1, 2, 1, 3, 4, 5 }, 100) | stats<double, true, true>();
    BOOST_CHECK_EQUAL(s2.n(), 600);
    BOOST_CHECK_CLOSE(s2.mean(), 16.0 / 6.0, epsilon);
    BOOST_CHECK_CLOSE(s2.stddev(), std::sqrt(20.0 / 9.0), epsilon);
    BOOST_CHECK_CLOSE(s2.variance(), 20.0 / 9.0, epsilon);
    BOOST_CHECK_EQUAL(s2.sum(), 1600);
    BOOST_CHECK_EQUAL(s2.sum_squares(), 5600);
    BOOST_CHECK_EQUAL(s2.min(), 1);
    BOOST_CHECK_EQUAL(s2.max(), 5);
    BOOST_CHECK_CLOSE(s2.median(), 2.5, epsilon);
    BOOST_CHECK_EQUAL(s2.mode(), 1);
    BOOST_CHECK_EQUAL_COLLECTIONS(s2.modes().begin(), s2.modes().end(), modes.begin(), modes.end());
    BOOST_CHECK(s2.has_minmax());
    BOOST_CHECK(s2.has_medianmode());

    auto s3 = from({ 1 }) | stats<double, true, false>();
    BOOST_CHECK(s3.has_minmax());
    BOOST_CHECK(!s3.has_medianmode());

    auto s4 = from({ 1 }) | stats<double, false, true>();
    BOOST_CHECK(!s4.has_minmax());
    BOOST_CHECK(s4.has_medianmode());
}

