// Tests for cubic_spline.
#define CATCH_CONFIG_MAIN
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
    cubic_spline s;
    CHECK_THROWS(s.calc(knots, values));
}

TEST_CASE("cubic_spline - rejects single-knot input")
{
    std::vector<double> const knots = { 1 };
    std::vector<double> const values = { 1 };
    cubic_spline s;
    CHECK_THROWS(s.calc(knots, values));
}

TEST_CASE("cubic_spline - rejects mismatched input")
{
    std::vector<double> const knots = { 1, 2, 3, 4 };
    std::vector<double> const values = { 1, 2 };
    cubic_spline s;
    CHECK_THROWS(s.calc(knots, values));
}

TEST_CASE("cubic_spline - rejects unordered knots")
{
    std::vector<double> const knots = { 3, 2, 1, 0 };
    std::vector<double> const values = { 1, 2, 1, 2 };
    cubic_spline s;
    CHECK_THROWS(s.calc(knots, values));
}

TEST_CASE("cubic_spline - rejects overlapping knots")
{
    std::vector<double> const knots = { 1, 2, 2, 3 };
    std::vector<double> const values = { 1, 2, 1, 2 };
    cubic_spline s;
    CHECK_THROWS(s.calc(knots, values));
}
