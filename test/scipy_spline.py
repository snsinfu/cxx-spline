import sys
import scipy.interpolate


def input_numbers(name):
    print(f"{name}:")
    return [float(s.strip()) for s in input().split(",")]

def output_numbers(xs):
    print(", ".join(f"{x:g}" for x in xs))


bc_type = sys.argv[1]

ts_in = input_numbers("t")
xs_in = input_numbers("x")
spline = scipy.interpolate.CubicSpline(ts_in, xs_in, bc_type=bc_type)

ts_out = input_numbers("interp. t")
xs_out = spline(ts_out)

print("Interp. x:")
output_numbers(xs_out)
