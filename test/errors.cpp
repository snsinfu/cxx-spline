// Tests for cubic_spline.
#include <catch.hpp>

#include <cstddef>
#include <limits>
#include <vector>

#include <cxx-spline.hpp>


// ERRORS --------------------------------------------------------------------

TEST_CASE("cubic_spline - rejects empty input")
{
    std::vector<double> const knots = { };
    std::vector<double> const values = { };
    CHECK_THROWS(cubic_spline(knots, values));
}

TEST_CASE("cubic_spline - rejects single-knot input")
{
    std::vector<double> const knots = { 1 };
    std::vector<double> const values = { 1 };
    CHECK_THROWS(cubic_spline(knots, values));
}

TEST_CASE("cubic_spline - rejects mismatched input")
{
    std::vector<double> const knots = { 1, 2, 3, 4 };
    std::vector<double> const values = { 1, 2 };
    CHECK_THROWS(cubic_spline(knots, values));
}

TEST_CASE("cubic_spline - rejects unordered knots")
{
    std::vector<double> const knots = { 3, 2, 1, 0 };
    std::vector<double> const values = { 1, 2, 1, 2 };
    CHECK_THROWS(cubic_spline(knots, values));
}

TEST_CASE("cubic_spline - rejects overlapping knots")
{
    std::vector<double> const knots = { 1, 2, 2, 3 };
    std::vector<double> const values = { 1, 2, 1, 2 };
    CHECK_THROWS(cubic_spline(knots, values));
}
