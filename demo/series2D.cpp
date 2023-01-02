#include <vector>
#include <cxx-spline.h>
#include <iostream>


int main()
{
    // Samples from a circle.
    std::vector<double> t = { 0, 0.25, 0.5, 0.75, 1 };
    std::vector<double> x = { 1, 0, -1, 0, 1 };
    std::vector<double> y = { 0, 1, 0, -1, 0 };

    // Spline interpolation of each coordinate.
    cubic_spline spline_x(t, x);
    cubic_spline spline_y(t, y);

    for (int i = 0; i <= 100; i++) {
        double sx = spline_x(i / 100.0);
        double sy = spline_y(i / 100.0);
        std::cout << sx << '\t' << sy << '\n';
    }
}
