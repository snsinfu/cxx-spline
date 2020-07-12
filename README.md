# Cubic splines for C++

![C++11][cxx-badge]
![Test status][test-badge]
[![Boost License][license-badge]](LICENSE.txt)

Header-only natural cubic spline interpolator for C++11 and above.

[cxx-badge]: https://img.shields.io/badge/C%2B%2B-11-orange.svg
[test-badge]: https://github.com/snsinfu/cxx-spline/workflows/test/badge.svg
[license-badge]: https://img.shields.io/badge/license-Boost-blue.svg

- [Usage](#usage)
- [Testing](#testing)
- [License](#license)

## Usage

Copy [spline.hpp](include/spline.hpp) into your include directory. Use
`cubic_spline` class like this:

```c++
#include <vector>
#include <spline.hpp>

int main()
{
    // Some points (t,y) on a curve y = f(t)
    std::vector<double> t = { 0, 1, 2, 3, 4, 5 };
    std::vector<double> y = { 1, 2, 3, 2, 1, 2 };

    // Spline interpolation (and extrapolation) of the points
    cubic_spline spline(t, y);

    spline(0.5); // 1.44976
    spline(1.5); // 2.65072
    spline(6.0); // 3
}
```

To interpolate a 2D (or higher dimensional) curve, just create splines for each
coordinate values. Example:

```c++
#include <iostream>
#include <vector>
#include <spline.hpp>

int main()
{
    // Samples from a circle.
    std::vector<double> t = { 0, 0.25, 0.5, 0.75, 1 };
    std::vector<double> x = { 1, 0, -1, 0, 1 };
    std::vector<double> y = { 0, 1, 0, -1, 0 };

    // Spline interpolation. Since it uses natural cubic splines, the edges are
    // extrapolated as straight lines. So, the resulting curve would look like
    // a deformed circle.
    cubic_spline spline_x(t, x);
    cubic_spline spline_y(t, y);

    for (int i = 0; i <= 100; i++) {
        double sx = spline_x(i / 100.0);
        double sy = spline_y(i / 100.0);
        std::cout << sx << '\t' << sy << '\n';
    }
}
```

## Testing

```sh
git clone https://github.com/snsinfu/cxx-spline.git
cd cxx-spline/tests
make
```

## License

Boost Software License, Version 1.0.
