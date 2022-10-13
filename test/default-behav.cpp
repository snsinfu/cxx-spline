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

    cubic_spline default_spline;
    default_spline.calc(knots, values);
    cubic_spline natural_spline;
    natural_spline.calc(knots, values, cubic_spline::natural);

    // Check extrapolated points.
    double const lower_point = -1;
    double const upper_point = 6;

    CHECK(default_spline(lower_point) == natural_spline(lower_point));
    CHECK(default_spline(upper_point) == natural_spline(upper_point));
}

TEST_CASE("Same instance repeated interpolation.")
{
    std::vector<double> const knots1 = { 1, 2 };
    std::vector<double> const values1 = { 10, 20 };

    cubic_spline spline;
    spline.calc(knots1, values1, cubic_spline::natural);

    CHECK(spline(0.5) == Approx(5));
    CHECK(spline(1) == Approx(10));
    CHECK(spline(1.5) == Approx(15));
    CHECK(spline(2) == Approx(20));
    CHECK(spline(2.5) == Approx(25));

    ////

    std::vector<double> const knots2 = {
        0.68016615, 1.2452488 , 1.63345679, 1.63976631, 2.07816546,
        2.47003112, 2.97258795, 3.17093706, 4.0599178 , 5.03705159
    };
    std::vector<double> const values2 = {
        0.2194959 ,  0.82918707, -0.21144624, -0.3236201 , -0.76156805,
        0.15871603, -0.40323101, -0.23905208,  0.75523286, -0.38302665
    };

    spline.calc(knots2, values2, cubic_spline::not_a_knot);

    // The splines reproduce knots.
    for (std::size_t i = 0; i < knots2.size(); i++) {
        auto const t = knots2[i];
        auto const x = values2[i];
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
        11.11032978,  5.56934967,  9.09078556, -0.99668101, -1.24124094,
        -0.66299763,  1.51254895,  0.44112204,  0.02763017, -0.25445675,
        -0.30035785, -0.27082759, -1.73528076, -0.94472597, -0.81484783,
        -0.58790497, -0.71946131,  0.15137141, -0.33741879, -0.37899863,
        -0.40249175, -0.28873437, -0.35972527, -0.29316007, -0.10203592,
         0.48749327, -0.07243857, -0.20824398,  0.63972506,  0.73506356,
        -1.43720490, -4.70489319, -2.46064086
    };

    for (std::size_t i = 0; i < queries.size(); i++) {
        auto const t = queries[i];
        auto const x = expects[i];
        CHECK(spline(t) == Approx(x));
    }

}

