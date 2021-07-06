import numpy as np
import matplotlib.pyplot as plt

xvalues = np.linspace(-2, 2, 2000)
yvalues = np.linspace(-2, 2, 2000)

xlen = len(xvalues)
ylen = len(yvalues)

#Change values in c to explore different julia sets
c = complex(-0.4, -0.59)

def julia(z, c, maxiter):
    for iteration in range(maxiter):
        z = (z * z) + c
        if abs(z) > 4:
            break
    return iteration

atlas = np.empty((xlen, ylen))

for ix in range(xlen):
    for iy in range(ylen):
        zx = xvalues[ix]
        zy = yvalues[iy]
        z = complex(zx, zy)
        atlas[ix, iy] = julia(z, c, 80)

plt.figsize=(18, 18)
plt.imshow(atlas.T, interpolation="nearest")
plt.show()
plt.imsave("juliaff.png", atlas.T)
