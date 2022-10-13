#include <vector>
#include <cxx-spline.hpp>
#include <iostream>

int main()
{
    // Some points (t,y) on a curve y = f(t)
    std::vector<double> t = { 0, 1, 2, 3, 4, 5 };
    std::vector<double> y = { 1, 2, 3, 2, 1, 2 };

    // Spline interpolation (and extrapolation) of the points
    cubic_spline spline;
    spline.calc(t, y);

    std::cout << spline(0.5) << ", "; // 1.44976
    std::cout << spline(1.5) << ", "; // 2.65072
    std::cout << spline(6.0) << std::endl; // 3
}
