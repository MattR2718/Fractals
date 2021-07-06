import numpy as np
import matplotlib.pyplot as plt

#function to find number of iterations for complex point c to diverge
def mandel(c, maxiter):
    z = complex(0, 0)
    for iteration in range(maxiter):
        z = (z * z) + c
        if abs(z) > 4:
            break
    return iteration

#horizontal side from -2 to 4
x_list = np.linspace(-2.0, 4.0, 13)
#print(x_list)
#vertical side from -2 to 2
y_list = np.linspace(-2.0, 2.0, 5)
#print(y_list)

#set the location and size of the complex plane rectangle
xvalues = np.linspace(-2.25, 0.75, 1000)
yvalues = np.linspace(-1.5, 1.5, 1000)
#size of these lists of x and y values
xlen = len(xvalues)
ylen = len(yvalues)
atlas = np.empty((xlen,ylen))

#set colour values of atlas based off of mandel function output
for ix in range(xlen):
    for iy in range(ylen):
        cx = xvalues[ix]
        cy = yvalues[iy]
        c = complex(cx, cy)
        
        atlas[ix, iy] = mandel(c, 40)

plt.figsize=(18, 18)
plt.imshow(atlas.T, interpolation="nearest")
plt.show()
plt.imsave("mandelbrot.png", atlas.T)
