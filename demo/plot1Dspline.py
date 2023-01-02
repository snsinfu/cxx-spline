#!/usr/bin/python3

import matplotlib.pyplot as plt
import scipy
import numpy as np

t = np.array([0, 1, 2, 3, 4, 5 ]);
y = np.array([1, 2, 3, 2, 1, 2 ]);


sp = np.loadtxt("1Dspline.dat")

tp = sp[:,0]
yp = sp[:,1]

plt.plot(t,y,"x")
plt.plot(tp,yp)
plt.show()
