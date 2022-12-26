#include <vector>
#include <cxx-spline.h>
#include <cstdio>

int main()
{
    // Some points (t,y) on a curve y = f(t)
    const std::vector<double> t = { 0, 1, 2, 3, 4, 5 };
    const std::vector<double> y = { 1, 2, 3, 2, 1, 2 };

    // Spline interpolation (and extrapolation) of the points
    cubic_spline spline(t, y);

    FILE* f=fopen("1Dspline.dat","wt");
    for(double tp=-0.5;tp<6;tp+=0.1) {
	    const double yp = spline(tp);
	    printf("f(%f)=%f\n",tp,yp);
	    fprintf(f,"%f %f\n",tp,yp);
    }
    fclose(f);

    printf("Lower bound = %f, Upper bound = %f\n",
	   spline.lower_bound(), spline.upper_bound()
	    );
}
