#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <cstddef>
#include <limits>
#include <vector>
#include <thread>

#include <cxx-spline.hpp>


std::vector<double> const knots = { 0, 1, 2, 3, 4, 5 };
std::vector<double> const values = { 1, 2, 1, 0, 1, 2 };
cubic_spline spline;

void manycalc() {
	for(int i = 0; i < 100000; i++) {
		spline.calc(knots, values, cubic_spline::natural);
	}
}


TEST_CASE("Thread safety")
{
	spline.calc(knots, values, cubic_spline::natural);
	std::thread t1(manycalc);
	for(int j = 0; j < 100000; j++) {
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
			0.31339713, 1.68660287, 1.69019139,
			0.30263158, 0.34928230,
			1.55023923, 2.44976077
		};
		
		for (std::size_t i = 0; i < queries.size(); i++) {
			auto const t = queries[i];
			auto const x = expects[i];
			CHECK(spline(t) == Approx(x));
		}
		CHECK(spline.getLowerBound() == Approx(0));
		CHECK(spline.getUpperBound() == Approx(5));
	}
	t1.join();
}
