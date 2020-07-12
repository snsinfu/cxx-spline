// Tests for cubic_spline.
//
// Test data can be generated with scipy.interpolate.CubicSpline with
// bc_type="natural". Do not use interp1d or splprep; these functions use a
// B-spline algorithm.

#include <catch.hpp>

#include <cstddef>
#include <limits>
#include <vector>

#include <spline.hpp>



TEST_CASE("cubic_spline - edge case - two points")
{
    std::vector<double> const knots = { 1, 2 };
    std::vector<double> const values = { 10, 20 };

    cubic_spline spline(knots, values);

    CHECK(spline(0.5) == Approx(5));
    CHECK(spline(1) == Approx(10));
    CHECK(spline(1.5) == Approx(15));
    CHECK(spline(2) == Approx(20));
    CHECK(spline(2.5) == Approx(25));
}

TEST_CASE("cubic_spline - uniform knots")
{
    std::vector<double> const knots = { 0, 1, 2, 3, 4, 5 };
    std::vector<double> const values = { 1, 2, 1, 0, 1, 2 };

    cubic_spline spline(knots, values);

    // Knots
    for (std::size_t i = 0; i < knots.size(); i++) {
        auto const t = knots[i];
        auto const x = values[i];
        CHECK(spline(t) == Approx(x));
    }

    // Example points (reference: scipy.interpolate.CubicSpline)
    std::vector<double> const queries = {
        -0.5, 0.5, 1.5, 2.5, 3.5, 4.5, 5.5
    };
    std::vector<double> const expects = {
        0.31339713, 1.68660287, 1.69019139, 0.30263158, 0.3492823,
        1.55023923, 2.44976077
    };

    for (std::size_t i = 0; i < queries.size(); i++) {
        auto const t = queries[i];
        auto const x = expects[i];
        CHECK(spline(t) == Approx(x));
    }
}

TEST_CASE("cubic_spline - non-uniform knots")
{
    std::vector<double> const knots = {
        0.68016615, 1.2452488 , 1.63345679, 1.63976631, 2.07816546,
        2.47003112, 2.97258795, 3.17093706, 4.0599178 , 5.03705159
    };
    std::vector<double> const values = {
        0.2194959 ,  0.82918707, -0.21144624, -0.3236201 , -0.76156805,
        0.15871603, -0.40323101, -0.23905208,  0.75523286, -0.38302665
    };

    cubic_spline spline(knots, values);

    // Knots
    for (std::size_t i = 0; i < knots.size(); i++) {
        auto const t = knots[i];
        auto const x = values[i];
        CHECK(spline(t) == Approx(x));
    }

    // Example points (reference: scipy.interpolate.CubicSpline)
    std::vector<double> const queries = {
        0.37328437, 0.4864476,  0.40997924, 0.98807018, 0.91956613,
        1.04514971, 1.41512365, 1.5914422,  1.61935038, 1.63587612,
        1.63845219, 1.63679386, 1.88879656, 2.04554709, 1.67090846,
        2.11230844, 2.08608836, 2.40444059, 2.86109911, 2.90726167,
        2.96184245, 3.13110034, 3.06412197, 3.12740522, 3.27608075,
        3.73981452, 3.29837537, 4.98298572, 4.56983343, 4.46509799,
        5.291805,   5.78259869, 5.47630083
    };
    std::vector<double> const expects = {
         0.15438036,  0.22064008,  0.18419257,  0.28557332,  0.23631715,
         0.3517909,   1.33378981,  0.42657731,  0.02554367, -0.2544149,
        -0.30033622, -0.27078753, -1.73629023, -0.94486074, -0.81531716,
        -0.58781348, -0.71943554,  0.15129612, -0.33635245, -0.37823334,
        -0.40233556, -0.28988097, -0.3610655,  -0.29436728, -0.09444519,
         0.54095606, -0.06255987, -0.28505556,  0.39519042,  0.52731802,
        -0.83392274, -1.45373784, -1.12222909
    };

    for (std::size_t i = 0; i < queries.size(); i++) {
        auto const t = queries[i];
        auto const x = expects[i];
        CHECK(spline(t) == Approx(x));
    }
}

TEST_CASE("cubic_spline - error - no knots")
{
    std::vector<double> const knots = { };
    std::vector<double> const values = { };
    CHECK_THROWS(cubic_spline(knots, values));
}

TEST_CASE("cubic_spline - error - insufficient knots")
{
    std::vector<double> const knots = { 1 };
    std::vector<double> const values = { 1 };
    CHECK_THROWS(cubic_spline(knots, values));
}

TEST_CASE("cubic_spline - error - lengths mismatch")
{
    std::vector<double> const knots = { 1, 2, 3, 4 };
    std::vector<double> const values = { 1, 2 };
    CHECK_THROWS(cubic_spline(knots, values));
}

TEST_CASE("cubic_spline - error - unordered knots")
{
    std::vector<double> const knots = { 3, 2, 1, 0 };
    std::vector<double> const values = { 1, 2, 1, 2 };
    CHECK_THROWS(cubic_spline(knots, values));
}
