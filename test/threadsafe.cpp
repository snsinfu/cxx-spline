#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <cstddef>
#include <limits>
#include <vector>
#include <thread>
#include <chrono>

#include <cxx-spline.hpp>


std::vector<double> const knots = { 1, 2 };
std::vector<double> const values = { 10, 20 };
cubic_spline spline;

void manycalc() {
	for(int i = 0; i < 1000; i++) {
		spline.calc(knots, values, cubic_spline::natural);
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}


TEST_CASE("Thread safety")
{
	spline.calc(knots, values, cubic_spline::natural);
	std::thread t1(manycalc);
	for(int i = 0; i < 1000; i++) {
		CHECK(spline(0.5) == Approx(5));
		CHECK(spline(1) == Approx(10));
		CHECK(spline(1.5) == Approx(15));
		CHECK(spline(2) == Approx(20));
		CHECK(spline(2.5) == Approx(25));
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	t1.join();
}
