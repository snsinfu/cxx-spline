// Tests for cubic_spline.
#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <cstddef>
#include <limits>
#include <vector>

#include <cxx-spline.hpp>

// DEFAULT BEHAVIOR ----------------------------------------------------------

TEST_CASE("cubic_spline - is natural by default")
{
    std::vector<double> const knots = { 0, 1, 2, 3, 4, 5 };
    std::vector<double> const values = { 1, 2, 1, 0, 1, 2 };

    cubic_spline default_spline(knots, values);
    cubic_spline natural_spline(knots, values, cubic_spline::natural);

    // Check extrapolated points.
    double const lower_point = -1;
    double const upper_point = 6;

    CHECK(default_spline(lower_point) == natural_spline(lower_point));
    CHECK(default_spline(upper_point) == natural_spline(upper_point));
}
